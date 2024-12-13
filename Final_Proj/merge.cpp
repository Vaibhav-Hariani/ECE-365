#include "merge.h"

std::string validate_merge(std::string str1, std::string str2,
                           std::string merge,
                           std::vector<std::vector<bool>> table) {
    if (merge.size() != str1.size() + str2.size()) {
        return "*** NOT A MERGE ***";
    }
    // table must have dimensions str1+1, str2+1, and must be empty
    for (auto &row : table) {
        std::fill(row.begin(), row.end(), false);
    }
    // Ties are broken by str1 first
    // so move i before moving j
    table[0][0] = true;
    // table starts at -1, -1 in the strings
    for (int i = 0; i <= str1.size(); i++) {
        for (int j = 0; j <= str2.size(); j++) {
            // If the current element is already valid, no need to check. Saves
            // some cycles
            if (!table[i][j]) {
                // if this character exists in str1, set it equal to the
                // "previous" state
                if (i > 0 && table[i - 1][j] &&
                    str1[i - 1] == merge[i + j - 1]) {
                    table[i][j] = true;
                } else if (j > 0 && table[i][j - 1] &&
                           str2[j - 1] == merge[i + j - 1]) {
                    table[i][j] = true;
                }
            }
        }
    }
    if (table[str1.size()][str2.size()]) {
        return iterate_table(str1, str2, merge, table);
    }
    return "*** NOT A MERGE ***";
}
//Generates the original from the two arrays and the original
std::string iterate_table(std::string str1, std::string str2, std::string merge,
                          std::vector<std::vector<bool>> table) {
    int i = str1.size();
    int j = str2.size();
    std::string result = merge;
    while (i > 0 || j > 0) {
        if(j > 0 && table[i][j-1]){
        // result[i + j - 1] = toupper(merge[i+j-1]);
        j--;
        } else {
            result[i + j - 1] = toupper(merge[i+j-1]);
            i--;
        }
    }
    return result;
}