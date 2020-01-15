#pragma once

#include <string>
#include <vector>
#include <iostream>

using std::cout, std::endl;
using std::string, std::vector;
using std::to_string;

void println(string message);
void print_usage();
void print_format();
void print_2D(vector<vector<int>>& state);
