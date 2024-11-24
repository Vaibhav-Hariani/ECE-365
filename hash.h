#ifndef HASH_H_
#define HASH_H_
#include <string>
#include <vector>

class hashTable {
 public:
  // Hash Table constructor
  hashTable(int size = 0);

  // if pointer is provided, associate pointer with key
  // 0 if success, 1 if key already exists, 2 if rehash fails.
  int insert(const std::string &key, void *pv = nullptr);

  // true if key in hash
  // false otherwise
  bool contains(const std::string &key);

  int setPointer(const std::string &key, void *pv);

  // return nullptr if no key
  // if pointer to bool is provided, set bool to true if pointer is provided
  // set bool to false otherwise
  void *getPointer(const std::string &key, bool *b = nullptr);

  // True if deletion is successful, False if key is not there
  bool remove(const std::string &key);

 private:
  // Supports up to 2^32, integer maximum in cpp
  static const int OFFSET = 2166136261;
  static const int FNV_PRIME = 16777619;
  int num_elements;

  // every object in a hash table. key is the string used as a key
  // isOccupied tells you that this entry is empty
  // isDeleted tells you this element is free to be replaced,
  // and for linear probing, that searching should continue
  // pv is a pointer to the value associated with the key, null if no value.
  class hashItem {
   public:
    std::string key{""};
    bool isOccupied{false};
    bool isDeleted{false};
    void *pv{nullptr};
  };
  std::vector<hashItem *> v;

  // Hash generator for a given key
  int hash(const std::string &key);

  // Searches for an item with a given key
  // Return position if found, otherwise -1
  int findPos(const std::string &key);

  // True on success, False if memory allocation fails
  bool rehash();

  // Return a prime number with lower bound size
  // Can use a precomputed list of selected prime numbers.
  static unsigned int getPrime(int size);
};

#endif  // HASH_H_