#include "heap.h"

heap::heap(int capacity) : mapping(4 * capacity / 3) {
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
    data[num_elements] = new_node;
    // This will also fail if rehashaing fails
    if (mapping.insert(id, &data[num_elements]) != 0) {
        return 2;
    }
    // Element has been added to end of array: Now it needs to slide into its
    // actual place
    percolateUp(num_elements);
    num_elements++;
    return 0;
}

int heap::deleteMin(std::string *pId, int *pKey,
                    void *ppData) {
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

int heap::remove(const std::string &id, int *pKey,
                 void *ppData) {
    bool t;
    void *raw_pointer = mapping.getPointer(id, &t);
    if (t == false) {
        return 1;
    }
    node *element_pointer = static_cast<node *>(raw_pointer);
    int index = getPos(element_pointer);
    extract_data(data[index], nullptr, pKey, ppData);

    num_elements--;
    data[index] = data[num_elements];
    mapping.remove(id);
    // Slide the previously last node down the heap into a final position
    percolateDown(index);
    return 0;
}
// Quick helper to get all the data out of a node, through the pointers
void heap::extract_data(node &n, std::string *pId,
                        int *pKey, void *ppData) {
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
        percolateUp(index);
    } else {
        percolateDown(index);
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
        mapping.setPointer(data[parent].id,&data[parent]);
        mapping.setPointer(data[posCur].id,&data[posCur]);
        posCur = parent;
        parent = (posCur - 1) / 2;
    }
}

void heap::percolateDown(int posCur) {
    int rchild = 2 * posCur + 2;
    int lchild = 2 * posCur + 1;
    node tmp;

    // Because of how heap is built, doesn't matter which side swap occurs.
    // Iterate until either bottom is hit or a key is smaller than the current
    while (rchild < num_elements && data[posCur].key > data[lchild].key &&
           data[posCur].key > data[rchild].key) {
        tmp = data[rchild];
        data[rchild] = data[posCur];
        data[posCur] = tmp;
        mapping.setPointer(data[rchild].id,&data[rchild]);
        mapping.setPointer(data[posCur].id,&data[posCur]);

        // mapping.setPointer()
        // Swap positions
        posCur = rchild;
        rchild = 2 * posCur + 2;
        lchild = 2 * posCur + 1;
    }

    // if lchild < num_elements and the 
    // data is greater than data[lchild], we know it's less than rchild
    if (lchild < num_elements && data[posCur].key > data[lchild].key) {
        tmp = data[rchild];
        data[rchild] = data[posCur];
        data[posCur] = tmp;
        mapping.setPointer(data[rchild].id,&data[rchild]);
        mapping.setPointer(data[posCur].id,&data[posCur]);
        // Swap positions

    //Opposite logic over here
    } else if (rchild < num_elements && data[posCur].key > data[rchild].key) {
        tmp = data[lchild];
        data[lchild] = data[posCur];
        data[posCur] = tmp;
        mapping.setPointer(data[lchild].id,&data[lchild]);
        mapping.setPointer(data[posCur].id,&data[posCur]);

        // mapping.setPointer()
        // Swap positions
    }
}
