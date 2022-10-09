#include <iostream>
#include "MyType.h"
#include "Interpreter.h"

static void	checkPath(const std::string path)
{
	int len = path.length();
	try
	{
		if (path[len - 1] != 't' || path[len - 2] != 'x'
			|| path[len - 3] != 't' || path[len - 4] != '.')
		{
			throw	std::exception();
		}

	}
	catch(const std::exception& e)
	{
		std::cerr << "file is not valid!" << std::endl;
		exit(1);
	}
	//stex porceci ashxatem std::exception het bayc chexav 
	//u chhaskaca xi dra hamar em exit ov durs galis
}


int	main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Could not open the file!" << std::endl;
		return (1);
	}
	checkPath(argv[1]);
	Interpreter file_for_compilation(argv[1]);
	file_for_compilation.compile();
	return (0);
}
