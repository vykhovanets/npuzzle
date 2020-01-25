
#include "log.hh"

namespace {
  const string usage{
      "Usage: ./n-puzzle [filename with n-puzzle] [heuristics fun number]\n"
      "possible heuristics:\n"
      "  1. Manhattan\n"
      "  2. Hamming\n"
      "  3. Euclidean\n"
  };

  const string format{
      "Format:\n"
      "- lines, which starts with a '#' are comments and will be rejected\n"
      "- file can be composed from numbers only\n"
      "- the first digit 'n' will be interpreted as a side size\n"
      "- the next should form an unsorted sequence: [0 to n squared)\n"
  };
}

void println(std::string message) { cout << message << endl; }
void print_usage() { println(usage); }
void print_format() { println(format); }

void print_2D(vector<vector<int>> &state) {
  println("state:");
  for (auto& row : state) {
    for (auto& elem : row) {
      cout << elem << " ";
    }
    cout << endl;
  }
}

void print_1D(vector<int> &state) {
  println("state:");
    for (auto& elem : state)
      cout << elem << " ";
    cout << endl;
}
