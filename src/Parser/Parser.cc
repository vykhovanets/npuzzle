
#include "Parser.hh"

Parser::Parser(int ac, char **av) {
  if (ac != 3) {
    print_usage();
    exit(1);
  }

  parse_file(av[1]);
  if (file_data.empty()) {
    println("Parser: filename is wrong or file is empty.");
    exit(1);
  }

  parse_heuristics(av[2]);
  if (!heuristics or heuristics > max_heuristics) {
    println("Parser: heuristics fun number is wrong.");
    print_usage();
    exit(1);
  }

  if (!check_correctness()) {
    println("Parser: n-puzzle data format is incorrect.");
    print_format();
    exit(1);
  }

  if (!check_solvability()) {
    println("Parser: this n-puzzle is unsolvable.");
    exit(1);
  }
}

auto Parser::get_first_state() -> vector<vector<int>> {
  return first_state;
}

// auto get_final_state() -> vector<point> {

// }

auto Parser::get_heuristics_index() -> int {
  return heuristics;
}

// .:: private

auto Parser::parse_file(string filename) -> void {
  int fd = open(filename.c_str(), O_RDONLY);
  if (fd < 0)
    return;

  struct stat sb;
  fstat(fd, &sb);

  file_data.resize(sb.st_size);

  read(fd, const_cast<char *>(file_data.data()), sb.st_size);
  close(fd);
}

auto Parser::parse_heuristics(string h) -> void {
  if (isdigit(h.at(0)))
    heuristics = stoi(h);
  else {
    println("Parser: use digits for heuristics fun number.");
    print_usage();
    exit(1);
  }
}

auto Parser::check_correctness() -> bool {
  file_data = regex_replace(file_data, regex("#.*\n"), "\n");

  stringstream numbers{file_data};
  int n{0};

  if (numbers >> n)
    size = n;
  else {
    println("Parser: can't determine the puzzle size.");
    return false;
  }

  vector<bool> check(size * size, false);
  vector<vector<int>> state(size, vector<int>(size, 0));

  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      if (numbers >> n and is_unique(check, n)) {
        state.at(y).at(x) = n;
      } else {
        return false;
      }
    }
  }

  first_state = state;

  print_2D(state);

  return true;
}

auto Parser::check_solvability() -> bool {
  return true;
}

auto Parser::is_unique(vector<bool> &check, int n) -> bool {
  if (n < check.size() and not check.at(n)) {
    check.at(n) = true;
    return true;
  } else
    return false;
}