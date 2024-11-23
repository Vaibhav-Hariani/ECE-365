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
    adj_list.push_back(final_vertex);
    num_elements++;
}

std::vector<std::string> graph::djikstra(std::string starting_node){
    std::vector<std::string> ret;
    heap Pqueue = heap(num_elements);
    

}