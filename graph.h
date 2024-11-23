#ifndef GRAPH_H_
#define GRAPH_H_
#include <list>
#include <string>
#include <vector>

#include "hash.h"
#include "heap.h"

class graph {
   public:
    // Nothing to be passed here
    graph();

    // insert new node, path, weight
    // 0 if successful
    // hashtable code if failure
    int insert(std::string initial_node, std::string final_node,
               int path_weight);

    // Returns a representation of djikstras algorithm
    std::vector<std::string> djikstra(std::string starting_node);

   private:
    int num_elements;
    hashTable vertex_lookup;
    class vertex;
    // Using a list as specified
    //  I figure a vector would stil be faster (Based on DSA I final experience)
    // Should be hot swappable
    std::list<vertex*> adj_list;

    //Helper for insert
    //Insert new element given it does not exist
    vertex* insert_new(std::string name, int &status);

    class edge {
       public:
        // vertex* initial;
        vertex* final;
        int weight;
    };
    class vertex {
       public:
        std::string name;
        // Points to other nodes
        std::list<edge*> paths;
    };

};

#endif  // GRAPH_H_