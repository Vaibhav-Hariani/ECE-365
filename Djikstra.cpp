#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include "graph.h"

using namespace std;

int main() {

    string filename;

    graph Djikstra = graph();

    cout << "Enter name of graph file: ";
    getline(cin, filename);
    fstream infile;
    infile.open(filename);
    string line;
    stringstream line_buf;
    while(getline(infile,line)){
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
    auto start = chrono::high_resolution_clock::now();
    vector<string> lines = Djikstra.djikstra(v1);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    cout << "Total time (in seconds) to apply Djikstra's algorithm:" << duration.count() << "\n";

    string out_filename;
    cout << "Enter name of output file: ";
    ofstream outfile;
    getline(cin, out_filename);
    outfile.open(out_filename);
    for(string line: lines){
        outfile << line << '\n';
    }
    outfile.close();

}