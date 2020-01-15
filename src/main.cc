
#include "Parser.hh"
#include "UI.hh"

int	main(int ac, char **av)
{
	Parser parser{ac, av};
	
	// algorithm -> visual_data
	visual_data data {
		1234567891, 0, 1, parser.get_size(), parser.get_first_state() 
	};
	
	UI ui(data);
	ui.start();

	return 0;
}
