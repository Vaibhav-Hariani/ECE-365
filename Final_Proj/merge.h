#ifndef MERGE_H_
#define MERGE_H_
#include <string>
#include <vector>
// int merge[1000][1000];

std::string validate_merge(std::string str1, std::string str2,
                           std::string merge,
                           std::vector<std::vector<bool>> table);

std::string iterate_table(std::string str1, std::string str2, std::string merge,
                          std::vector<std::vector<bool>> table);

#endif
