#include "interpreter.h"

static std::vector<std::string>	splitText(const std::string& str)
{
	std::vector<std::string> tokens;
	std::stringstream check(str);
	std::string intermediate;
	while (getline(check, intermediate, ' '))
	{
		tokens.push_back(intermediate);
	}
	return (tokens);
}

void	Interpreter::declaredVariable(const std::vector<std::string>& tmpTokens)
{
	MyType tmp;
	tmp.set_type(MyType::getType(tmpTokens[0]));
	try
	{
		if (m_Elements.find(tmpTokens[1]) != m_Elements.end())
		{
			throw std::exception();
		}
		m_Elements[tmpTokens[1]] = tmp;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Double statemant!" << std::endl;
		exit(1);
	}
	if (tmpTokens.size() == 2)
	{
		return ;
	}
	setValue(tmpTokens);
}

void	Interpreter::setValue(const std::vector<std::string>& tmpTokens)
{
	try
	{
		if (m_Elements[tmpTokens[1]].get_type() == MyType::INTEGER && tmpTokens.size() == 4)
		{
			m_Elements[tmpTokens[1]].set_int(std::stoi(tmpTokens[3]));
		}
		else if (m_Elements[tmpTokens[1]].get_type() == MyType::DOUBLE && tmpTokens.size() == 4)
		{
			m_Elements[tmpTokens[1]].set_double(std::stod(tmpTokens[3]));
		}
		else if (m_Elements[tmpTokens[1]].get_type() == MyType::STRING
				&& MyType::_Get_type(tmpTokens[3]) == MyType::STRING)
		{
			size_t i = 2;
			std::string str;
			while (++i < tmpTokens.size())
			{
				str += tmpTokens[i];
				if (i != tmpTokens.size() - 1)
					str += " ";
			}
			str.pop_back();
			str.erase(str.begin());
			m_Elements[tmpTokens[1]].set_string(str);
		}
		else if (m_Elements[tmpTokens[1]].get_type() == MyType::BOOLEAN && tmpTokens.size() == 4)
		{
			if (tmpTokens[3] == "TRUE")
				m_Elements[tmpTokens[1]].set_bool(1);
			else if (tmpTokens[3] == "FALSE")
				m_Elements[tmpTokens[1]].set_bool(0);
		}
		else
		{
			throw std::exception();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "SYNTAX ERROR" << std::endl;
		exit(1);
	}
}

void	Interpreter::printVariable(const std::vector<std::string>& tmpTokens)
{
	try
	{
		if (m_Elements.find(tmpTokens[1]) == m_Elements.end())
		{
			throw std::exception();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "the given variable is not declared" << std::endl;
		exit(1);
	}
	if (m_Elements[tmpTokens[1]].get_type() == MyType::INTEGER)
	{
		std::cout << m_Elements[tmpTokens[1]].get_int() << std::endl;
	}
	else if (m_Elements[tmpTokens[1]].get_type() == MyType::DOUBLE)
	{
		std::cout << m_Elements[tmpTokens[1]].get_double()  << std::endl;
	}
	else if (m_Elements[tmpTokens[1]].get_type() == MyType::STRING)
	{
		std::cout << m_Elements[tmpTokens[1]].get_string()  << std::endl;
	}
	else
	{
		std::cout << m_Elements[tmpTokens[1]].get_bool()  << std::endl;
	}
}

void	Interpreter::mathematical_op(const std::vector<std::string>& tmpTokens)
{
	if (tmpTokens.size() == 5 && m_Elements.find(tmpTokens[2]) != m_Elements.end()
		&& m_Elements.find(tmpTokens[4]) != m_Elements.end())
	{
		if (tmpTokens[3] == "+")
			m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]] + m_Elements[tmpTokens[4]];
		else if (tmpTokens[3] == "-")
			m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]] - m_Elements[tmpTokens[4]];
		else if (tmpTokens[3] == "*")
			m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]] * m_Elements[tmpTokens[4]];
		else if (tmpTokens[3] == "/")
			m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]] / m_Elements[tmpTokens[4]];
	}
	else
	{
		if (tmpTokens[3] == "+")
		{
			if (m_Elements.find(tmpTokens[2]) != m_Elements.end()
				&& m_Elements[tmpTokens[2]].get_type() == MyType::_Get_type(tmpTokens[4]))
			{
				if (MyType::_Get_type(tmpTokens[4]) == MyType::INTEGER)
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]] + std::stoi(tmpTokens[4]);
				else
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]] + std::stod(tmpTokens[4]);
			}
			else if (m_Elements.find(tmpTokens[4]) != m_Elements.end()
				&& m_Elements[tmpTokens[4]].get_type() == MyType::_Get_type(tmpTokens[2]))
			{
				if (MyType::_Get_type(tmpTokens[2]) == MyType::INTEGER)
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[4]] + std::stoi(tmpTokens[2]);
				else
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[4]] + std::stod(tmpTokens[2]);
			}
			else if (m_Elements[tmpTokens[0]].get_type() == MyType::_Get_type(tmpTokens[2])
					&& MyType::_Get_type(tmpTokens[2]) == MyType::_Get_type(tmpTokens[4]))
			{
				if (MyType::_Get_type(tmpTokens[2]) == MyType::INTEGER)
					m_Elements[tmpTokens[0]] = std::stoi(tmpTokens[2]) + std::stoi(tmpTokens[4]);
				else
					m_Elements[tmpTokens[0]] = std::stod(tmpTokens[2]) + std::stod(tmpTokens[4]);
			}
		}
		else if (tmpTokens[3] == "-")
		{
			if (m_Elements.find(tmpTokens[2]) != m_Elements.end()
				&& m_Elements[tmpTokens[2]].get_type() == MyType::_Get_type(tmpTokens[4]))
			{
				if (MyType::_Get_type(tmpTokens[4]) == MyType::INTEGER)
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]] - std::stoi(tmpTokens[4]);
				else
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]] - std::stod(tmpTokens[4]);
			}
			else if (m_Elements.find(tmpTokens[4]) != m_Elements.end()
				&& m_Elements[tmpTokens[4]].get_type() == MyType::_Get_type(tmpTokens[2]))
			{
				if (MyType::_Get_type(tmpTokens[2]) == MyType::INTEGER)
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[4]] - std::stoi(tmpTokens[2]);
				else
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[4]] - std::stod(tmpTokens[2]);
			}
			else if (m_Elements[tmpTokens[0]].get_type() == MyType::_Get_type(tmpTokens[2])
					&& MyType::_Get_type(tmpTokens[2]) == MyType::_Get_type(tmpTokens[4]))
			{
				if (MyType::_Get_type(tmpTokens[2]) == MyType::INTEGER)
					m_Elements[tmpTokens[0]] = std::stoi(tmpTokens[2]) - std::stoi(tmpTokens[4]);
				else
					m_Elements[tmpTokens[0]] = std::stod(tmpTokens[2]) - std::stod(tmpTokens[4]);
			}
		}
		else if (tmpTokens[3] == "*")
		{
			if (m_Elements.find(tmpTokens[2]) != m_Elements.end()
				&& m_Elements[tmpTokens[2]].get_type() == MyType::_Get_type(tmpTokens[4]))
			{
				if (MyType::_Get_type(tmpTokens[4]) == MyType::INTEGER)
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]] * std::stoi(tmpTokens[4]);
				else
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]] * std::stod(tmpTokens[4]);
			}
			else if (m_Elements.find(tmpTokens[4]) != m_Elements.end()
				&& m_Elements[tmpTokens[4]].get_type() == MyType::_Get_type(tmpTokens[2]))
			{
				if (MyType::_Get_type(tmpTokens[2]) == MyType::INTEGER)
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[4]] * std::stoi(tmpTokens[2]);
				else
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[4]] * std::stod(tmpTokens[2]);
			}
			else if (m_Elements[tmpTokens[0]].get_type() == MyType::_Get_type(tmpTokens[2])
					&& MyType::_Get_type(tmpTokens[2]) == MyType::_Get_type(tmpTokens[4]))
			{
				if (MyType::_Get_type(tmpTokens[2]) == MyType::INTEGER)
					m_Elements[tmpTokens[0]] = std::stoi(tmpTokens[2]) * std::stoi(tmpTokens[4]);
				else
					m_Elements[tmpTokens[0]] = std::stod(tmpTokens[2]) * std::stod(tmpTokens[4]);
			}
		}
		else if (tmpTokens[3] == "/")
		{
			if (m_Elements.find(tmpTokens[2]) != m_Elements.end()
				&& m_Elements[tmpTokens[2]].get_type() == MyType::_Get_type(tmpTokens[4]))
			{
				if (MyType::_Get_type(tmpTokens[4]) == MyType::INTEGER)
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]] / std::stoi(tmpTokens[4]);
				else
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]] / std::stod(tmpTokens[4]);
			}
			else if (m_Elements.find(tmpTokens[4]) != m_Elements.end()
				&& m_Elements[tmpTokens[4]].get_type() == MyType::_Get_type(tmpTokens[2]))
			{
				if (MyType::_Get_type(tmpTokens[2]) == MyType::INTEGER)
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[4]] / std::stoi(tmpTokens[2]);
				else
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[4]] / std::stod(tmpTokens[2]);
			}
			else if (m_Elements[tmpTokens[0]].get_type() == MyType::_Get_type(tmpTokens[2])
					&& MyType::_Get_type(tmpTokens[2]) == MyType::_Get_type(tmpTokens[4]))
			{
				if (MyType::_Get_type(tmpTokens[2]) == MyType::INTEGER)
					m_Elements[tmpTokens[0]] = std::stoi(tmpTokens[2]) / std::stoi(tmpTokens[4]);
				else
					m_Elements[tmpTokens[0]] = std::stod(tmpTokens[2]) / std::stod(tmpTokens[4]);
			}
		}
	}
}

void	Interpreter::assigning_and_math(const std::vector<std::string>& tmpTokens)
{
	try
	{
		if (m_Elements.find(tmpTokens[0]) == m_Elements.end())
		{
			throw "this variable is not declared";
		}
		if (m_Elements[tmpTokens[0]].get_type() == MyType::BOOLEAN)
		{
			if (tmpTokens[2] == "TRUE")
				m_Elements[tmpTokens[0]].set_bool(1);
			else if (tmpTokens[2] == "FALSE")
				m_Elements[tmpTokens[0]].set_bool(0);
			else if (m_Elements.find(tmpTokens[2]) != m_Elements.end()
					&& m_Elements[tmpTokens[2]].get_type() == MyType::BOOLEAN)
				m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]];
			else
				throw "this variable is not declared";
		}
		else if (m_Elements[tmpTokens[0]].get_type() == MyType::INTEGER)
		{
			if (tmpTokens.size() == 3)
			{
				if (m_Elements.find(tmpTokens[2]) != m_Elements.end()
					&& m_Elements[tmpTokens[2]].get_type() == MyType::INTEGER)
				{
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]];
				}
				else if (MyType::_Get_type(tmpTokens[2]) == MyType::INTEGER)
				{
					m_Elements[tmpTokens[0]].set_int(std::stoi(tmpTokens[2]));
				}
				else
					throw "variables have different types";
			}
			else if (tmpTokens.size() == 5)
			{
				mathematical_op(tmpTokens);
			}
			else
				throw "ERROR";
		}
		else if (m_Elements[tmpTokens[0]].get_type() == MyType::DOUBLE)
		{
			if (tmpTokens.size() == 3)
			{
				if (m_Elements.find(tmpTokens[2]) != m_Elements.end()
					&& m_Elements[tmpTokens[2]].get_type() == MyType::DOUBLE)
				{
					m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]];
				}
				else if (MyType::_Get_type(tmpTokens[2]) == MyType::DOUBLE)
				{
					m_Elements[tmpTokens[0]].set_int(std::stoi(tmpTokens[2]));
				}
				else
					throw "variables have different types";
			}
			else if (tmpTokens.size() == 5)
			{
				mathematical_op(tmpTokens);
			}
			else
				throw "ERROR";
		}
		else
		{
			if (m_Elements.find(tmpTokens[2]) != m_Elements.end() && tmpTokens.size() == 3
				&& m_Elements[tmpTokens[2]].get_type() == MyType::STRING)
			{
				m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]];
			}
			else if (tmpTokens.size() == 5 && tmpTokens[3] == "+" && m_Elements.find(tmpTokens[2]) != m_Elements.end()
					&& m_Elements[tmpTokens[2]].get_type() == m_Elements[tmpTokens[4]].get_type()
					&& m_Elements.find(tmpTokens[4]) != m_Elements.end())
			{
				m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]] + m_Elements[tmpTokens[4]];
			}
			else if (tmpTokens[3] == "+" && m_Elements.find(tmpTokens[2]) != m_Elements.end()
					&& MyType::_Get_type(tmpTokens[4]) == MyType::STRING)
			{
				std::string str;
				size_t i = 3;
				while (++i < tmpTokens.size())
				{
					str += tmpTokens[i];
					if (i < tmpTokens.size() - 1)
						str += " ";
				}
				str.pop_back();
				str.erase(str.begin());
				m_Elements[tmpTokens[0]] = m_Elements[tmpTokens[2]] + str;
			}
			else if ( MyType::_Get_type(tmpTokens[2]) == MyType::STRING
					&& m_Elements.find(tmpTokens[tmpTokens.size() - 1]) != m_Elements.end()
					&& tmpTokens[tmpTokens.size() - 2] == "+")
			{
				
				std::string str;
				size_t i = 1;
				while (tmpTokens[++i] != "+")
				{
					str += tmpTokens[i];
					if (tmpTokens[i + 1] != "+")
						str += " ";
				}
				str.pop_back();
				str.erase(str.begin());
				m_Elements[tmpTokens[0]] = str + m_Elements[tmpTokens[2]];
			}
			else if ( MyType::_Get_type(tmpTokens[2]) == MyType::STRING
					&&  MyType::_Get_type(tmpTokens[tmpTokens.size() - 1]) == MyType::STRING)
			{
				std::string str;
				size_t i = 1;
				while (++i < tmpTokens.size())
				{
					if (tmpTokens[i] != "+")
						str += tmpTokens[i];
					if (i < tmpTokens.size() - 1 || tmpTokens[i] != "+")
						str += " ";
				}
				i = -1;
				while (str[++i])
				{
					if (str[i] == '"')
						str.erase(str.begin() + i);
				}
				m_Elements[tmpTokens[0]] = str;
			}
			else
				throw "variables have different types";
		}
	}
	catch(const char* e)
	{
		std::cerr << e << std::endl;
		exit(1);
	}
	
}

void	Interpreter::compile()
{
	bool			flag;
	std::string		line;
	std::ifstream	myFile(m_Path);
	try
	{
		if (!myFile.is_open())
		{
			throw std::exception();
		}
	}
	catch(const std::exception &e)
	{
		std::cerr << "file Couldn't found!" << std::endl;
		exit(1);
	}	
	while (getline(myFile, line))
	{
		std::vector<std::string> tokens = splitText(line);
		if (tokens[0] == "tiv" || tokens[0] == "ketikov"
			|| tokens[0] == "tox" || tokens[0] == "logic")
		{
			declaredVariable(tokens);
		}
		else if (tokens[0] == "tpel")
		{
			printVariable(tokens);
		}
		else if (tokens[0] == "ete")
		{
			if_function(tokens, flag);
			while (flag)
			{
				std::string	str{};
				int			count = 0;
				getline(myFile, str);
				if (str == '{')
				{
					++count;
				}
				else if (str == '}')
				{
					--count;
				}
				else if (count == 0)
				{
					break ;
				}
			}
//			condition(tokens);
		}
		else if (tokens[0] == "cikl")
		{
//			cycle(tokens);
		}
		else
		{
			assigning_and_math(tokens);
		}
	}
}
