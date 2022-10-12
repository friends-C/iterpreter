#ifndef	INTERPRETER_H
# define INTERPRETER_H

# include <exception>
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
# include <map>
# include <functional>
# include "MyType.h"
# include "utils.h"

//tiv		-> int
//ketikov	-> double
//tox		-> string
//logic		-> bool
//if		-> ete
//else		-> ete_voch
//cikl		-> while
//tpel		-> cout

class Interpreter
{
	public:
		//constructors
		Interpreter() = default;
		Interpreter(const std::string& path);
	private:
		//private section for member functions
		void Interpret();
		void Tokens();

		//function for creating a variable
		void declaredVariable(const std::vector<std::string>& tmpTokens);

		//function to initialize the value
		void setValue(const std::vector<std::string>& tmpTokens);

		//function to outputthe value
		void printVariable(const std::vector<std::string>& tmpTokens);
	
		//function for assigment and mathematical operations
		void assigning_and_math(const std::vector<std::string>& tmpTokens);
		void mathematical_op(const std::vector<std::string>& tmpTokens);
	
		//condition functions
		bool if_function(const std::vector<std::string>& line);
		void else_function(size_t& index);

		void Opcode(size_t& index);
	private:
		//private section for member data

		std::ifstream myFilePath;
		std::map<int, std::string> file;
		std::map<std::string, MyType> myElements;
};

#endif