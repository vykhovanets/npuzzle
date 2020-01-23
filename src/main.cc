
#include "NPuzzleSolver.hh"
#include "Parser.hh"
#include "UI.hh"

int main(int ac, char **av) {
  Parser parser{ac, av};

  State::set_final_state(parser.get_final_state());
  NPuzzleSolver::set_size(parser.get_size());
  auto res = NPuzzleSolver::a_star_solver(parser.get_first_state());

  UI ui(res);
  ui.start();

  return 0;
}
