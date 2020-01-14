
#include "Parser.hh"
#include "UI.hh"

int	main(int ac, char **av)
{
	Parser parser{ac, av};
	
	
	UI ui;
	ui.start();

	return 0;
}
