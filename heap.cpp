#include "heap.h"

heap::heap(int capacity) : mapping((5 * capacity)/2) {
    data.resize(capacity + 1);
    this->capacity = capacity;
    num_elements = 0;
}

int heap::insert(const std::string &id, int key, void *pv) {
    if (num_elements == capacity) {
        return 1;
    }

    node new_node;
    new_node.key = key;
    new_node.id = id;
    new_node.pData = pv;
    if (mapping.insert(id, &data[num_elements]) != 0) {
        return 2;
    }
    data[num_elements] = new_node;
    // This will also fail if rehashing fails

    // Element has been added to end of array: Now it needs to slide into its
    // actual place
    percolateUp(num_elements);
    num_elements++;
    return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
    if (num_elements == 0) {
        return 1;
    }
    node min = data[0];
    extract_data(min, pId, pKey, ppData);
    // Remove this element by writing it with the last node
    num_elements--;
    data[0] = data[num_elements];
    mapping.remove(min.id);
    // Slide this node down the heap into it's final position
    percolateDown(0);
    return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData) {
    if(num_elements == 0){
        return 1;
    }
    bool t;
    void *raw_pointer = mapping.getPointer(id, &t);
    if (t == false) {
        return 1;
    }
    node *element_pointer = static_cast<node *>(raw_pointer);
    int index = getPos(element_pointer);
    extract_data(data[index], nullptr, pKey, ppData);

    int prev_key = data[index].key;

    num_elements--;
    
    data[index] = data[num_elements];
    
    mapping.remove(id);
    // Slide the previously last node down the heap into a final position
    mapping.setPointer(data[index].id, &data[index]);

    if(prev_key > data[index].key) {
        percolateDown(index);        
    } else if (prev_key < data[index].key){
        percolateUp(index);
    } 
    return 0;
}
// Quick helper to get all the data out of a node, through the pointers
void heap::extract_data(node &n, std::string *pId, int *pKey, void *ppData) {
    if (pId != nullptr) {
        *pId = n.id;
    }
    if (pKey != nullptr) {
        *pKey = n.key;
    }
    if (ppData != nullptr) {
        ppData = n.pData;
    }
}

int heap::setKey(const std::string &id, int key) {
    bool t;
    void *raw_pointer = mapping.getPointer(id, &t);
    if (t == false) {
        return 1;
    }
    node *element_pointer = static_cast<node *>(raw_pointer);
    int index = getPos(element_pointer);
    int old_key = data[index].key;
    data[index].key = key;
    // If the new key is smaller, we want the element at the top of the heap
    // Otherwise, put it at the bottom
    if (old_key < key) {
        percolateDown(index);
    } else {
        percolateUp(index);
    }
    return 0;
}

// This was a clever exploitation of contiguous memory!
// Much appreciated.
int heap::getPos(node *pn) { return pn - &data[0]; }

// These functions move a node into it's resting place,
// and then update the pointer value in the hashmap
// If the pointer value isn't updated, getPos won't work
void heap::percolateUp(int posCur) {
    int parent = (posCur - 1) / 2;
    node tmp;
    // Every swap is an update to the table
    // If we hit zero, the data has percolated to the top
    while (posCur > 0 && data[posCur].key < data[parent].key) {
        tmp = data[parent];
        data[parent] = data[posCur];
        data[posCur] = tmp;
        mapping.setPointer(data[parent].id, &data[parent]);
        mapping.setPointer(data[posCur].id, &data[posCur]);
        posCur = parent;
        parent = (posCur - 1) / 2;
    }
}

void heap::percolateDown(int posCur) {
    int rchild = 2 * posCur + 2;
    int lchild = 2 * posCur + 1;
    node tmp;

    // Because of how heap is built, doesn't matter which side swap occurs.
    // Iterate until no elements below or a key is smaller than the current
    while (lchild < num_elements && (data[posCur].key > data[lchild].key ||
                                     data[posCur].key > data[rchild].key)) {
        int swap_index = rchild;
        // If it's greater than the left child
        // Swap left if the left child is the smaller of the two
        // Or there is no right child
        if (data[posCur].key > data[lchild].key && rchild >= num_elements ||
            data[lchild].key < data[rchild].key) {
            swap_index = lchild;
        }

        tmp = data[swap_index];
        data[swap_index] = data[posCur];
        data[posCur] = tmp;
        mapping.setPointer(data[swap_index].id, &data[swap_index]);
        mapping.setPointer(data[posCur].id, &data[posCur]);

        posCur = swap_index; 
        rchild = 2 * posCur + 2;
        lchild = 2 * posCur + 1;
    }
}
