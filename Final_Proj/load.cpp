#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "merge.h"

using namespace std;

//Prealloc
vector<vector<bool>> table(1001,std::vector<bool>(1001,false));


int main() {
    string input_filename;
    cout << "\n Enter Name of input file: ";
    getline(cin, input_filename);
    fstream infile;
    infile.open(input_filename);

    string output_filename;
    cout << "\n Enter Name of output file: ";
    getline(cin, output_filename);
    ofstream outfile;
    outfile.open(output_filename);

    string line;
    while(getline(infile, line)){
        string str1 = line;
        getline(infile, line);
        string str2 = line;
        getline(infile, line);        
        string merge = line;
        outfile << validate_merge(str1, str2, merge,table) << '\n';
    }
    infile.close();
    outfile.close();
    return 0;
}