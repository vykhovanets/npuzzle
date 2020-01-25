#pragma once

#include "log.hh"
#include "common.hh"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <cctype>
#include <cstdint>
#include <sstream>
#include <string>

#include <regex>

constexpr uint8_t max_heuristics{3};

using std::string;
using std::regex, std::regex_replace;
using std::stringstream;

class Parser {
public:
  Parser(int ac, char **av);

  auto get_first_state() -> vector<vector<int>>;
  auto get_final_state() -> vector<point>;
  auto get_heuristics_index() -> int;
  auto get_size() -> int;

private:
  auto parse_file(string filename) -> void;
  auto parse_heuristics(string h) -> void;
  auto check_correctness() -> bool;
  auto check_solvability() -> bool;
  
  // solvability helpers
  auto first_to_snail() -> vector<int>;

  // correctness helper
  auto is_unique(vector<bool>& check, int n) -> bool;
  
  auto construct_final_state() -> void;
  
  string file_data;
  int heuristics{0};
  int size{0};
  vector<vector<int>> first_state;
  vector<point> final_state;
};
