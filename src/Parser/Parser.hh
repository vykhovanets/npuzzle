#pragma once

#include "log.hh"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <cctype>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

constexpr uint8_t max_heuristics{3};

using std::vector, std::string;
using std::regex, std::regex_replace;
using std::stringstream;

struct point {
  uint8_t x, y;
};

class Parser {
public:
  Parser(int ac, char **av);

  auto get_first_state() -> vector<vector<int>>;
  auto get_final_state() -> vector<point>;
  auto get_heuristics_index() -> int;

private:
  auto parse_file(string filename) -> void;
  auto parse_heuristics(string h) -> void;
  auto check_correctness() -> bool;
  auto check_solvability() -> bool;
  
  auto is_unique(vector<bool>& check, int n) -> bool;
  
  string file_data;
  int heuristics{0};
  int size{0};
  vector<vector<int>> first_state;
  
};
