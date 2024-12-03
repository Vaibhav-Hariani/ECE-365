#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "graph.h"
#include <filesystem>


using namespace std;

int main() {
    string filename;

    cout << "Enter name of graph file: ";
    getline(cin, filename);
    fstream infile;
    //This is an overestimate of the file size:
    //A line with simple formatting (va vb x \n) occupies at least 8 bytes and allocates at most 2 new elements
    //As such, the absolute maximum number of nodes is size / 7. 
    // Since memory management wasn't specified, this is a simple exploit to minimize reallocation.
    int size = filesystem::file_size(filename) / 14;
    graph Djikstra = graph(size);
    infile.open(filename);
    string line;
    stringstream line_buf;
    while (getline(infile, line)) {
        vector<string> pieces;
        stringstream line_buf(line);
        string word;
        while (line_buf >> word) {
            pieces.push_back(word);
        }
        Djikstra.insert(pieces[0], pieces[1], stoi(pieces[2]));
    }
    infile.close();

    string v1;
    cout << "Enter name of starting vertex: ";
    getline(cin, v1);
    while (!Djikstra.exists(v1)) {
        cout << "Invalid Vertex: Please specify an existing vertex: ";
        getline(cin, v1);
    }

    auto start = chrono::high_resolution_clock::now();
    vector<string> lines = Djikstra.djikstra(v1);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    double seconds = duration.count() / 1e6;
    cout << "Total time (in seconds) to apply Djikstra's algorithm: " << seconds
         << "\n";

    string out_filename;
    cout << "Enter name of output file: ";
    ofstream outfile;
    getline(cin, out_filename);
    outfile.open(out_filename);
    for (string line : lines) {
        outfile << line << '\n';
    }
    outfile.close();
}