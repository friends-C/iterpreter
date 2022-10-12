#include <iostream>
#include <regex>
#include "MyType.h"
#include "Interpreter.h"

bool check_path(const std::string& path)
{
	std::cmatch result;
	std::regex regular("(.txt)");

	if (!std::regex_search(path.c_str(), result, regular))
	{
		return 0;
	}
	return 1;
}

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2 || !check_path(argv[1]))
		{
			throw "Could not open the file!";
		}
		else
		{
			Interpreter Interpret(argv[1]);
		}
	}
	catch(const char* msg)
	{
		std::cerr << msg << std::endl;
		exit(1);
	}
	return 0;
}