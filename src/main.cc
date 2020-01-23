
#include "Parser.hh"
#include "UI.hh"
#include "NPuzzleSolver.hh"

void dump_state(const Snapshot& snap) {
    for (int i = 0; i < snap.size(); ++i) {
        for (int j = 0; j < snap[i].size(); ++j) {
            std::cout << snap[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int	main(int ac, char **av)
{
	Parser parser{ac, av};
	
	// algorithm -> visual_data
    auto first_state = parser.get_first_state();
    /*
	visual_data data {
		1234567891, 0, 4, parser.get_size(), parser.get_first_state() 
	};
    */

    State::set_final_state(parser.get_final_state());
    NPuzzleSolver::set_size(parser.get_size());
    auto res = NPuzzleSolver::a_star_solver(parser.get_first_state());
	
    std::cout << "---------Result----------" << std::endl;
    std::cout << "Time complexity: " << res.sum_opened_elems << std::endl;
    std::cout << "Space complexity: " << res.max_active_elems << std::endl;
    auto sol = res.state;
    std::cout << "Size: " << sol.size() << std::endl;
    for (auto el : sol) {
        dump_state(el);
        std::cout << std::endl;
    }

	//UI ui(res);
	//ui.start();

	return 0;
}
