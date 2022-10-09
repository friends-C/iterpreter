#ifndef  INTERPRETER_H
# define INTERPRETER_H

# include	<iostream>
# include	<exception>
# include	<fstream>
# include	<sstream>
# include	<vector>
# include	<string>
# include	<map>
# include	"MyType.h"

//tiv		-> int
//ketikov	-> double
//tox		-> string
//logic		-> bool
//if		-> ete
//cikl		-> while
//tpel		-> cout

class Interpreter
{
	public:
		// constructor and destructor 
		Interpreter(const std::string& path) : m_Path(path) {	}
		Interpreter() = default;
		~Interpreter()  = default;

		// public method for compiling file
		void	compile();

		// funcions that determine literal and variable types
	private:
	//private section for member functions

		//function for creating a variable
		void		declaredVariable(const std::vector<std::string>& tmpTokens);

		//function to initialize the value
		void		setValue(const std::vector<std::string>& tmpTokens);

		//function to outputthe value
		void		printVariable(const std::vector<std::string>& tmpTokens);
	
		//function for assigment and mathematical operations
		void		assigning_and_math(const std::vector<std::string>& tmpTokens);
		void		mathematical_op(const std::vector<std::string>& tmpTokens);

		//condition functions
		void		if_function(const std::vector<std::string>& tmpTokens, flag);
		void		else_function(const std::vector<std::string>& tmpTokens, flag);
	private:
	//private section for member data
		
		std::string						m_Path;
		std::map<std::string, MyType>	m_Elements;
};

#endif
