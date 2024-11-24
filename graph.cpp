#include "graph.h"

graph::graph() : vertex_lookup(500) { num_elements = 0; }

int graph::insert(std::string initial, std::string final, int weight) {
    vertex* initial_vertex;
    vertex* final_vertex;

    bool exists;
    void* raw_pointer = vertex_lookup.getPointer(initial, &exists);

    if (exists) {
        initial_vertex = (vertex*)raw_pointer;
    } else {
        int status = 0;
        initial_vertex = insert_new(initial, status);
        if (status > 0) {
            return status;
        }
    }
    raw_pointer = vertex_lookup.getPointer(final, &exists);
    if (exists) {
        final_vertex = (vertex*)raw_pointer;
    } else {
        int status = 0;
        final_vertex = insert_new(final, status);
        if (status > 0) {
            return status;
        }
    }
    edge* newedge = new edge();
    newedge->final = final_vertex;
    newedge->weight = weight;
    initial_vertex->paths.push_back(newedge);
    return 0;
}

graph::vertex* graph::insert_new(std::string name, int& status) {
    vertex* final_vertex = new vertex();
    status = vertex_lookup.insert(name, final_vertex);
    
    if (status > 0) {
        return nullptr;
    }
    final_vertex->name = name;
    final_vertex->position = num_elements;
    adj_list.push_back(final_vertex);
    num_elements++;
}

std::vector<std::string> graph::djikstra(std::string starting_node){
    //Quick lookups for each element: This allows for the final ordering to be proper
    std::vector<std::string> ret;

    ret.resize(num_elements);

    heap Pqueue = heap(num_elements);
    // hashTable return_table = hashTable(num_elements * 2);
    bool exists = true;
    void * raw_node = vertex_lookup.getPointer(starting_node, &exists);
    if (!exists) {
        return ret;
    }
    vertex* initial_node = (vertex*) raw_node;    
    Pqueue.insert(initial_node->name, 0, raw_node);

    int weight; 
    while(Pqueue.deleteMin(nullptr, &weight, raw_node) < 1) {
        vertex* current = (vertex *) raw_node;
        ret[current->position] = current -> name + "\t"  + std::to_string(weight); 
        for(edge* cur_edge: current->paths){
            vertex* next_vertex = cur_edge->final;
            //2 if element exists
            if(Pqueue.insert(next_vertex->name, weight + cur_edge ->weight, next_vertex) == 2){
                int existing_weight;
                Pqueue.get_node(next_vertex->name,&existing_weight);
                if(existing_weight > weight + cur_edge ->weight) {
                    Pqueue.setKey(next_vertex->name, weight + cur_edge->weight);
                }
            }
        }
    }
}