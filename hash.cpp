#include "hash.h"

#include <string>
#include <vector>

hashTable::hashTable(int size) {
    int len = getPrime(size);
    this->v.resize(len);
    this->num_elements = 0;
}
// if pointer is provided, associate pointer with key
// 0 if success, 1 if key already exists, 2 if rehash fails.
int hashTable::insert(const std::string &key, void *pv) {
    // Load factor of 75%
    int load_factor = (3 * (v.size()) / 4);
    if (num_elements > load_factor) {
        if (!rehash()) {
            return 2;
        }
    }
    unsigned int index = hash(key) % (v.size());

    while (v[index] != nullptr && v[index]->isOccupied && !(v[index]-> isDeleted)) {
        //This was likely the bug: I wasn't checking to see if the element was deleted
        //If it is, we can safely fill that square
        //As a result, when you keep filling up the hash table and keep removing all the elements, it will crash.
        //Hopefully this fixes things
        if (v[index]->key == key) {
            return 1;
        }
        index++;
        index = index % (v.size());
    }
    hashItem *element = new hashItem();
    element->key = key;
    element->isOccupied = true;
    element->pv = pv;
    v[index] = element;
    num_elements++;
    return 0;
}

// true if key in hash
// false otherwise
bool hashTable::contains(const std::string &key) {
    if (this->findPos(key) >= 0) {
        return true;
    }
    return false;
}

// return nullptr if no key
// if pointer to bool is provided, set bool to true if pointer is provided
// set bool to false otherwise
void *hashTable::getPointer(const std::string &key, bool *b) {
    int index = this->findPos(key);
    if (index < 0) {
        if (b != nullptr) {
            *b = false;
        }
        return nullptr;
    }
    if (b != nullptr) {
        *b = true;
    }
    return (v[index]->pv);
}

int hashTable::setPointer(const std::string &key, void *pv) {
    int index = this->findPos(key);
    if (index < 0) {
        return 1;
    }
    hashItem *element = v[index];
    element->pv = pv;
    return 0;
}

// True if deletion is successful, False if key is not there
bool hashTable::remove(const std::string &key) {
    int index = this->findPos(key);
    if (index < 0) {
        return false;
    }
    v[index]->isDeleted = true;
    return true;
}

// Hash generator for a given key
// Using FNV hasing, does not need any adjustment
int hashTable::hash(const std::string &key) {
    int hashVal = OFFSET;
    for (char ch : key) {
        hashVal = hashVal * FNV_PRIME;
        hashVal = hashVal ^ ch;
    }
    return hashVal;
}

// Searches for an item with a given key
// Return position if found, otherwise -1
int hashTable::findPos(const std::string &key) {
    unsigned int index = hash(key) % (v.size());
    while (v[index] != nullptr && v[index]->isOccupied) {
        if (!(v[index] ->isDeleted) && v[index]->key == key) {
            //If the key is the same and the element hasn't been deleted
            return index;
        }
        index++;
        index = index % v.capacity();
    }
    return -1;
}

// True on success, False if memory allocation fails
bool hashTable::rehash() {
    // Resize based on current vector size
    std::vector<hashItem *> tmp = v;
    try {
        int new_size = getPrime(this->v.size());
        v.clear();
        v.resize(new_size);
        num_elements = 0;
    } catch (...) {
        return false;
    }
    for (hashItem *item : tmp) {
        if (item != nullptr && !(item->isDeleted)) {
            this->insert(item->key, item->pv);
        }
    }
    return true;
}

// Return a prime number with lower bound size
// Can use a precomputed list of selected prime numbers.
unsigned int hashTable::getPrime(int size) {
    const unsigned int good_primes[19] = {1543,      6151,      24593,     49157,
                                 98317,     196613,    393241,    786433,
                                 1572869,   3145739,   6291469,   12582917,
                                 25165843,  50331653,  100663319, 201326611,
                                 402653189, 805306457, 1610612741};
    int c = 0;
    while (good_primes[c] <= size) {
        c++;
    }
    return good_primes[c];
}
