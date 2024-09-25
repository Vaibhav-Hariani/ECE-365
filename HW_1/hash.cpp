#include <string>
#include <vector>

using namespace std;
class hashTable {
    public:
    //Hash Table constructor 
    hashTable(int size = 0) {
        int len = getPrime(size);
        this->v.reserve(len);
        this->num_elements = 0;
    }

    //if pointer is provided, associate pointer with key
    //0 if success, 1 if key already exists, 2 if rehash fails.
    int insert(const string &key, void *pv = nullptr){
        //Load factor of 75%
        if(num_elements >= (3 * v.size() / 4)){
            if(!rehash()) {
                return 2;
            }
        }
        unsigned int index = hash(key) % v.size();
        while(v[index]->isOccupied){
            if(v[index]->key == key){
                return 1;
            }
            index++;
            if(index == v.size()){
                index = 0;
            }
        }
        hashItem* element = new hashItem;
        element -> key = key;
        element -> isOccupied = true;
        return 0;
    }

    //true if key in hash
    //false otherwise
    bool contains(const string &key){
        if (this -> findPos(key) >= 0){
            return true;
        }
        return false;
    }

    //return nullptr if no key
    //if pointer to bool is provided, set bool to true if pointer is provided
    //set bool to false otherwise
    void *getPointer(const string &key, bool *b = nullptr){
        unsigned int index = this -> findPos(key);
        if(index < 0){
            if(b != nullptr){
                *b = false;
            }
            return nullptr;
        }
        if(b!= nullptr){
            *b = true;
        }
        return (v[index]->pv);
    }

    //True if deletion is successful, False if key is not there
    bool remove(const string &key){
        unsigned int index = this -> findPos(key);
        if(index < 0){
            return false;
        }
        v[index]->isDeleted = true;
        return true;
    }

    private:
        //Supports up to 2^32, integer maximum in cpp
        static const int OFFSET = 2166136261;
        static const int FNV_PRIME = 16777619;
        class hashItem {
            public:
                string key {""};
                bool isOccupied {false};
                bool isDeleted {false};
                void *pv {nullptr};
        };

        vector<hashItem*> v;
        int num_elements;

        //Hash generator for a given key
        //Using FNV hasing, does not need any adjustment
        int hash(const string &key){
            int hashVal = OFFSET;
            for (char ch: key){
                hashVal = hashVal * FNV_PRIME;
                hashVal = hashVal ^ ch;
            }
            return hashVal;
        }

        
        //Searches for an item with a given key
        //Return position if found, otherwise -1
        int findPos(const string &key){
            unsigned int index = hash(key) % v.size();
            while(v[index] != nullptr && v[index]->isOccupied) {
                if(v[index]->key == key){
                    return index;
                }
                index++;
                index = index % v.size();
            }
            return -1;            
        }

        //True on success, False if memory allocation fails
        bool rehash(){
            //Resize based on current vector size
            int new_size = getPrime(this -> v.size());
            vector<hashItem *> tmp = v;
            v.resize(new_size);
            for(hashItem* item : tmp) {
                if(item != nullptr && !(item->isDeleted)) {
                    this -> insert(item->key, item->pv);
                }
            }
        }


        //Return a prime number with lower bound size
        //Can use a precomputed list of selected prime numbers.
        static unsigned int getPrime(int size){
            int good_primes[19] = {1543,6151,24593,49157,98317,
            196613,393241,786433,
            1572869,3145739,6291469
            ,12582917,25165843,50331653
            ,100663319,201326611,402653189,805306457,1610612741};
            int c = 0;
            while (good_primes[c] < size){
                c++;
            }
            return c;            
        }
};
