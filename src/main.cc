
#include "Parser.hh"
#include "UI.hh"
#include "NPuzzleSolver.hh"

int	main(int ac, char **av)
{
	Parser parser{ac, av};
	
	// algorithm -> visual_data
    auto first_state = parser.get_first_state();
	visual_data data {
		1234567891, 0, 1, parser.get_size(), parser.get_first_state() 
	};

    State::set_final_state(parser.get_final_state());
    NPuzzleSolver::set_size(parser.get_size());
    NPuzzleSolver::a_star_solver(first_state);
	
	UI ui(data);
	ui.start();

	return 0;
}
