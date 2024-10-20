#ifndef HEAP_H_
#define HEAP_H_
#include <string>
#include <vector>
#include "hash.h"

class heap {
   public:
    // Hash Table constructor
    heap(int capacity = 0);

    int insert(const std::string &key, void *pv = nullptr);

    //
    int deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);

    int setKey(std::string &id, int key);
    
    //Same return types as deletemin: pointers here are return pointers (aside from key).
    int remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr);

   private:
    // Supports up to 2^32, integer maximum in cpp
    int capacity;
    int num_elements;
    class node {
       public:
        std::string id{""};
        int key{false};
        void *pv{nullptr};
    };
    
    std::vector<node> data;
    hashTable table;
};

#endif  // HASH_H_