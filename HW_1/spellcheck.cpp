#include "hash.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <stdexcept>

using namespace std;
//From cpp reference
string str_tolower(string s){
    transform(s.begin(), s.end(), s.begin(),
            [](unsigned char c){ return tolower(c); }
                  );
    return s;
}


hashTable* parse_dictionary(string filename) {
    ifstream inFile;
    inFile.open(filename);
    string line;
    regex regex_val = regex("^[A-Za-z] + $");
    //Error handling for a failed read
    if(!inFile.is_open()){
        throw invalid_argument("file for dictionary failed to open");
    }
    //This might be cheating but I don't believe anything was specified against it
    //Getting an upper bound for size
    int fsize = 0;
    while(getline(inFile,line)){
        fsize++;
    }
    inFile.close();

    inFile.open(filename);
    hashTable* table = new hashTable(fsize);    
    while(getline(inFile, line)){
        if(line.size() <= 20 && regex_match(line,regex_val)){
            table->insert(str_tolower(line));
        }
    }
    inFile.close();
    return table;
}

void spellcheck(string in_file, string out_file, hashTable* table){
    ifstream inFile;
    inFile.open(in_file);
    ofstream outFile;
    outFile.open(out_file);
    string read_line;

    if(!inFile.is_open() || !outFile.is_open()){
        throw invalid_argument("file for dictionary failed to open");
    }

    int line_number = 0;
    while(getline(inFile,read_line)){
        line_number++;
        int i = 0;
        string word = "";
        bool shouldCheck = true;
        for(int i = 0; i < read_line.size(); i++){
            if(isalnum(read_line[i])){
                if(isdigit(read_line[i]) || i >= 19){
                    shouldCheck == false;
                }
                word += tolower(read_line[i]);
            } else {
                if(shouldCheck){
                    table -> contains(word);
                }
                //Word is complete, processing
                shouldCheck = true;
                word = "";
            }
        }

        //Do some fancy string parsing to isolate strings
        outFile << read_line;
    }

}


int main() {
    string dict_name;
    cout << "Enter dictionary file: ";
    cin >> dict_name;
    string spellcheck_name;
    cout << "\nEnter name of file to spellcheck: ";
    cin >> spellcheck_name;
    string output;
    cout << "\nEnter output file: ";
    cin >> output;

    cout << "Parsing Dictionary.\n";
    clock_t t1 = clock();
    hashTable* table = parse_dictionary(dict_name);
    clock_t t2 = clock();
    double timeDiff = ((double)(t2 - t1)) / CLOCKS_PER_SEC;
    cout << "Hashmap Loaded. CPU time was " << timeDiff << " seconds.\n";

    t1 = clock();
    spellcheck(spellcheck_name, output, table);
    t2 = clock();
    timeDiff = ((double)(t2 - t1)) / CLOCKS_PER_SEC;
    cout << "Spellcheck Complete. CPU time was " << timeDiff << " seconds.\n";


    return 0;
}