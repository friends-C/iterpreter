#include "Interpreter.h"
#include "MyType.h"

static std::vector<std::string>	SplitText(const std::string& str)
{
	std::vector<std::string> tokens;
	std::stringstream check(str);
	std::string line;
	while (getline(check, line, ' '))
	{
		while (line[0] == '\t' || line[0] == ' ')
		{
			line.erase(line.begin(), line.begin() + 1);
		}
		if (line[0] != 0)
		{
			tokens.push_back(line);
		}
	}
	return tokens;
}

Interpreter::Interpreter(const std::string& path)
: myFilePath(path)
{
	Interpret();
}

void Interpreter::Interpret()
{
	if (!myFilePath.is_open())
	{
		throw "File not found";
	}
	std::string line;
	size_t index = 0;
	while (std::getline(myFilePath, line))
	{
		file[++index] = line;
		line.clear();
	}
	Tokens();
}

void Interpreter::Tokens()
{
	for (size_t index = 1; index <= file.size(); ++index)
	{
		Opcode(index);
	}
}

void Interpreter::else_function(size_t& index)
{
	if (file[++index] == "{")
	{
		while (file[++index] != "}")
			;
	}
	if (file[++index] == "ete_voch")
	{
		if (file[++index] == "{")
		{
			while (file[++index] != "}")
			{
				Opcode(index);
			}
		}
		else
		{
			Opcode(index);
		}
	}
}

void Interpreter::Opcode(size_t& index)
{
	std::vector<std::string> tokens = SplitText(file[index]);
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
			if (!if_function(tokens))
			{
				else_function(index);
			}
			else
			{
				if (file[++index] == "{")
				{
					while (file[++index] != "}")
					{
						Opcode(index);
					}
				}
				else
				{
					Opcode(index);
				}
				if (file[++index] == "ete_voch")
				{
					if (file[++index] == "{")
					{
						while (file[++index] != "}")
							;
					}
					else 
					{
						++index;
					}
				}
				else
				{
					throw "Syntax ERROR";
				}
			} 
		}
		else if (tokens[0] == "cikl")
		{
			size_t start = index, end = index + 1;
			while(if_function(tokens))
			{
				if (file[++index] == "{")
				{
					while (file[++index] != "}")
					{
						Opcode(index);
					}
					end = index;
				}
				else
				{
					Opcode(index);
				}
				index = start;
			}
			index = end;
		}
		else if (myElements.find(tokens[0]) != myElements.end())
		{
			assigning_and_math(tokens);
		}
		else
		{
			throw "Syntax ERROR";
		}
}


void Interpreter::declaredVariable(const std::vector<std::string>& tmpTokens)
{
	MyType tmp;
	tmp.set_type(Utils::Get_variable_type(tmpTokens[0]));
	if (myElements.find(tmpTokens[1]) != myElements.end())
	{
		throw "Double statemant!";
	}
	myElements[tmpTokens[1]] = tmp;
	if (tmpTokens.size() == 2)
	{
		return ;
	}
	setValue(tmpTokens);
}

void Interpreter::setValue(const std::vector<std::string>& tmpTokens)
{
	if (myElements[tmpTokens[1]].get_type() == Utils::INTEGER && tmpTokens.size() == 4)
	{
		myElements[tmpTokens[1]].set_int(std::stoi(tmpTokens[3]));
	}
	else if (myElements[tmpTokens[1]].get_type() == Utils::DOUBLE && tmpTokens.size() == 4)
	{
		myElements[tmpTokens[1]].set_double(std::stod(tmpTokens[3]));
	}
	else if (myElements[tmpTokens[1]].get_type() == Utils::STRING)
	{
		std::string str;
		for (size_t i = 3; i < tmpTokens.size(); ++i)
		{
			str += tmpTokens[i];
			if (i != tmpTokens.size() - 1)
				str += " ";
		}
		str.pop_back();
		str.erase(str.begin());
		myElements[tmpTokens[1]].set_string(str);
	}
	else if (myElements[tmpTokens[1]].get_type() == Utils::BOOLEAN && tmpTokens.size() == 4)
	{
		if (tmpTokens[3] == "TRUE")
			myElements[tmpTokens[1]].set_bool(1);
		else if (tmpTokens[3] == "FALSE")
			myElements[tmpTokens[1]].set_bool(0);
	}
	else
	{
		throw "Syntax ERROR";
	}
}

void Interpreter::printVariable(const std::vector<std::string>& tmpTokens)
{
	if (myElements.find(tmpTokens[1]) == myElements.end())
	{
		throw "the given variable is not declared";
	}
	if (myElements[tmpTokens[1]].get_type() == Utils::INTEGER)
	{
		std::cout << myElements[tmpTokens[1]].get_int() << std::endl;
	}
	else if (myElements[tmpTokens[1]].get_type() == Utils::DOUBLE)
	{
		std::cout << myElements[tmpTokens[1]].get_double()  << std::endl;
	}
	else if (myElements[tmpTokens[1]].get_type() == Utils::STRING)
	{
		std::cout << myElements[tmpTokens[1]].get_string()  << std::endl;
	}
	else
	{
		std::cout << myElements[tmpTokens[1]].get_bool()  << std::endl;
	}
}

void Interpreter::assigning_and_math(const std::vector<std::string>& tmpTokens)
{
	if (myElements.find(tmpTokens[0]) == myElements.end())
	{
		throw "this variable is not declared";
	}
	if (myElements[tmpTokens[0]].get_type() == Utils::BOOLEAN)
	{
		if (tmpTokens[2] == "TRUE")
			myElements[tmpTokens[0]].set_bool(1);
		else if (tmpTokens[2] == "FALSE")
			myElements[tmpTokens[0]].set_bool(0);
		else if (myElements.find(tmpTokens[2]) != myElements.end()
				&& myElements[tmpTokens[2]].get_type() == Utils::BOOLEAN)
			myElements[tmpTokens[0]] = myElements[tmpTokens[2]];
		else
			throw "this variable is not declared";
	}
	else if (myElements[tmpTokens[0]].get_type() == Utils::INTEGER)
	{
		if (tmpTokens.size() == 3)
		{
			if (myElements.find(tmpTokens[2]) != myElements.end()
				&& myElements[tmpTokens[2]].get_type() == Utils::INTEGER)
			{
				myElements[tmpTokens[0]] = myElements[tmpTokens[2]];
			}
			else if (Utils::Get_literal_type(tmpTokens[2]) == Utils::INTEGER)
			{
				myElements[tmpTokens[0]].set_int(std::stoi(tmpTokens[2]));
			}
			else
				throw "variables have different types";
		}
		else if (tmpTokens.size() == 5)
		{
			mathematical_op(tmpTokens);
		}
		else
			throw "Syntax ERROR";
	}
	else if (myElements[tmpTokens[0]].get_type() == Utils::DOUBLE)
	{
		if (tmpTokens.size() == 3)
		{
			if (myElements.find(tmpTokens[2]) != myElements.end()
				&& myElements[tmpTokens[2]].get_type() == Utils::DOUBLE)
			{
				myElements[tmpTokens[0]] = myElements[tmpTokens[2]];
			}
			else if (Utils::Get_literal_type(tmpTokens[2]) == Utils::DOUBLE)
			{
				myElements[tmpTokens[0]].set_int(std::stoi(tmpTokens[2]));
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
		if (myElements.find(tmpTokens[2]) != myElements.end() && tmpTokens.size() == 3
			&& myElements[tmpTokens[2]].get_type() == Utils::STRING)
		{
			myElements[tmpTokens[0]] = myElements[tmpTokens[2]];
		}
		else if (tmpTokens.size() == 5 && tmpTokens[3] == "+" && myElements.find(tmpTokens[2]) != myElements.end()
				&& myElements[tmpTokens[2]].get_type() == myElements[tmpTokens[4]].get_type()
				&& myElements.find(tmpTokens[4]) != myElements.end())
		{
			myElements[tmpTokens[0]] = myElements[tmpTokens[2]] + myElements[tmpTokens[4]];
		}
		else if (tmpTokens[3] == "+" && myElements.find(tmpTokens[2]) != myElements.end()
				&& Utils::Get_literal_type(tmpTokens[4]) == Utils::STRING)
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
			myElements[tmpTokens[0]] = myElements[tmpTokens[2]] + str;
		}
		else if ( Utils::Get_literal_type(tmpTokens[2]) == Utils::STRING
				&& myElements.find(tmpTokens[tmpTokens.size() - 1]) != myElements.end()
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
			myElements[tmpTokens[0]] = str + myElements[tmpTokens[2]];
		}
		else if ( Utils::Get_literal_type(tmpTokens[2]) == Utils::STRING
				&&  Utils::Get_literal_type(tmpTokens[tmpTokens.size() - 1]) == Utils::STRING)
		{
			std::string str;
			for (size_t i = 2; i < tmpTokens.size(); ++i)
			{
				if (tmpTokens[i] != "+")
					str += tmpTokens[i];
				if (i < tmpTokens.size() - 1 || tmpTokens[i] != "+")
					str += " ";
			}
			int i = -1;
			while (str[++i])
			{
				if (str[i] == '"')
					str.erase(str.begin() + i);
			}
			myElements[tmpTokens[0]] = str;
		}
		else
			throw "variables have different types";
	}
}

void	Interpreter::mathematical_op(const std::vector<std::string>& tmpTokens)
{
	if (tmpTokens.size() == 5 && myElements.find(tmpTokens[2]) != myElements.end()
		&& myElements.find(tmpTokens[4]) != myElements.end())
	{
		if (tmpTokens[3] == "+")
			myElements[tmpTokens[0]] = myElements[tmpTokens[2]] + myElements[tmpTokens[4]];
		else if (tmpTokens[3] == "-")
			myElements[tmpTokens[0]] = myElements[tmpTokens[2]] - myElements[tmpTokens[4]];
		else if (tmpTokens[3] == "*")
			myElements[tmpTokens[0]] = myElements[tmpTokens[2]] * myElements[tmpTokens[4]];
		else if (tmpTokens[3] == "/")
			myElements[tmpTokens[0]] = myElements[tmpTokens[2]] / myElements[tmpTokens[4]];
	}
	else
	{
		if (tmpTokens[3] == "+")
		{
			if (myElements.find(tmpTokens[2]) != myElements.end()
				&& myElements[tmpTokens[2]].get_type() == Utils::Get_literal_type(tmpTokens[4]))
			{
				if (Utils::Get_literal_type(tmpTokens[4]) == Utils::INTEGER)
					myElements[tmpTokens[0]] = myElements[tmpTokens[2]] + std::stoi(tmpTokens[4]);
				else
					myElements[tmpTokens[0]] = myElements[tmpTokens[2]] + std::stod(tmpTokens[4]);
			}
			else if (myElements.find(tmpTokens[4]) != myElements.end()
				&& myElements[tmpTokens[4]].get_type() == Utils::Get_literal_type(tmpTokens[2]))
			{
				if (Utils::Get_literal_type(tmpTokens[2]) == Utils::INTEGER)
					myElements[tmpTokens[0]] = myElements[tmpTokens[4]] + std::stoi(tmpTokens[2]);
				else
					myElements[tmpTokens[0]] = myElements[tmpTokens[4]] + std::stod(tmpTokens[2]);
			}
			else if (myElements[tmpTokens[0]].get_type() == Utils::Get_literal_type(tmpTokens[2])
					&& Utils::Get_literal_type(tmpTokens[2]) == Utils::Get_literal_type(tmpTokens[4]))
			{
				if (Utils::Get_literal_type(tmpTokens[2]) == Utils::INTEGER)
					myElements[tmpTokens[0]] = std::stoi(tmpTokens[2]) + std::stoi(tmpTokens[4]);
				else
					myElements[tmpTokens[0]] = std::stod(tmpTokens[2]) + std::stod(tmpTokens[4]);
			}
		}
		else if (tmpTokens[3] == "-")
		{
			if (myElements.find(tmpTokens[2]) != myElements.end()
				&& myElements[tmpTokens[2]].get_type() == Utils::Get_literal_type(tmpTokens[4]))
			{
				if (Utils::Get_literal_type(tmpTokens[4]) == Utils::INTEGER)
					myElements[tmpTokens[0]] = myElements[tmpTokens[2]] - std::stoi(tmpTokens[4]);
				else
					myElements[tmpTokens[0]] = myElements[tmpTokens[2]] - std::stod(tmpTokens[4]);
			}
			else if (myElements.find(tmpTokens[4]) != myElements.end()
				&& myElements[tmpTokens[4]].get_type() == Utils::Get_literal_type(tmpTokens[2]))
			{
				if (Utils::Get_literal_type(tmpTokens[2]) == Utils::INTEGER)
					myElements[tmpTokens[0]] = myElements[tmpTokens[4]] - std::stoi(tmpTokens[2]);
				else
					myElements[tmpTokens[0]] = myElements[tmpTokens[4]] - std::stod(tmpTokens[2]);
			}
			else if (myElements[tmpTokens[0]].get_type() == Utils::Get_literal_type(tmpTokens[2])
					&& Utils::Get_literal_type(tmpTokens[2]) == Utils::Get_literal_type(tmpTokens[4]))
			{
				if (Utils::Get_literal_type(tmpTokens[2]) == Utils::INTEGER)
					myElements[tmpTokens[0]] = std::stoi(tmpTokens[2]) - std::stoi(tmpTokens[4]);
				else
					myElements[tmpTokens[0]] = std::stod(tmpTokens[2]) - std::stod(tmpTokens[4]);
			}
		}
		else if (tmpTokens[3] == "*")
		{
			if (myElements.find(tmpTokens[2]) != myElements.end()
				&& myElements[tmpTokens[2]].get_type() == Utils::Get_literal_type(tmpTokens[4]))
			{
				if (Utils::Get_literal_type(tmpTokens[4]) == Utils::INTEGER)
					myElements[tmpTokens[0]] = myElements[tmpTokens[2]] * std::stoi(tmpTokens[4]);
				else
					myElements[tmpTokens[0]] = myElements[tmpTokens[2]] * std::stod(tmpTokens[4]);
			}
			else if (myElements.find(tmpTokens[4]) != myElements.end()
				&& myElements[tmpTokens[4]].get_type() == Utils::Get_literal_type(tmpTokens[2]))
			{
				if (Utils::Get_literal_type(tmpTokens[2]) == Utils::INTEGER)
					myElements[tmpTokens[0]] = myElements[tmpTokens[4]] * std::stoi(tmpTokens[2]);
				else
					myElements[tmpTokens[0]] = myElements[tmpTokens[4]] * std::stod(tmpTokens[2]);
			}
			else if (myElements[tmpTokens[0]].get_type() == Utils::Get_literal_type(tmpTokens[2])
					&& Utils::Get_literal_type(tmpTokens[2]) == Utils::Get_literal_type(tmpTokens[4]))
			{
				if (Utils::Get_literal_type(tmpTokens[2]) == Utils::INTEGER)
					myElements[tmpTokens[0]] = std::stoi(tmpTokens[2]) * std::stoi(tmpTokens[4]);
				else
					myElements[tmpTokens[0]] = std::stod(tmpTokens[2]) * std::stod(tmpTokens[4]);
			}
		}
		else if (tmpTokens[3] == "/")
		{
			if (myElements.find(tmpTokens[2]) != myElements.end()
				&& myElements[tmpTokens[2]].get_type() == Utils::Get_literal_type(tmpTokens[4]))
			{
				if (Utils::Get_literal_type(tmpTokens[4]) == Utils::INTEGER)
					myElements[tmpTokens[0]] = myElements[tmpTokens[2]] / std::stoi(tmpTokens[4]);
				else
					myElements[tmpTokens[0]] = myElements[tmpTokens[2]] / std::stod(tmpTokens[4]);
			}
			else if (myElements.find(tmpTokens[4]) != myElements.end()
				&& myElements[tmpTokens[4]].get_type() == Utils::Get_literal_type(tmpTokens[2]))
			{
				if (Utils::Get_literal_type(tmpTokens[2]) == Utils::INTEGER)
					myElements[tmpTokens[0]] = myElements[tmpTokens[4]] / std::stoi(tmpTokens[2]);
				else
					myElements[tmpTokens[0]] = myElements[tmpTokens[4]] / std::stod(tmpTokens[2]);
			}
			else if (myElements[tmpTokens[0]].get_type() == Utils::Get_literal_type(tmpTokens[2])
					&& Utils::Get_literal_type(tmpTokens[2]) == Utils::Get_literal_type(tmpTokens[4]))
			{
				if (Utils::Get_literal_type(tmpTokens[2]) == Utils::INTEGER)
					myElements[tmpTokens[0]] = std::stoi(tmpTokens[2]) / std::stoi(tmpTokens[4]);
				else
					myElements[tmpTokens[0]] = std::stod(tmpTokens[2]) / std::stod(tmpTokens[4]);
			}
		}
	}
}

bool Interpreter::if_function(const std::vector<std::string>& line)
{
	bool flag;
	if (line.size() == 2)
	{
		if (myElements.find(line[1]) != myElements.end())
		{
			if (myElements[line[1]].get_type() == Utils::BOOLEAN)
			{
				flag = myElements[line[1]].get_bool();
			}
			else if (myElements[line[1]].get_type() == Utils::INTEGER)
			{
				flag = static_cast<bool>(myElements[line[1]].get_int());
			}
			else if (myElements[line[1]].get_type() == Utils::DOUBLE)
			{
				flag = static_cast<bool>(myElements[line[1]].get_double());
			}
			else
			{
				flag = myElements[line[1]].get_string() == "" ? 0 : 1;
			}
		}
		else
		{
			if (Utils::Get_literal_type(line[1]) == Utils::BOOLEAN)
			{
				flag = (line[1] == "true" || line[1] == "TRUE") ? 1 : 0;
			}
			else if (Utils::Get_literal_type(line[1]) == Utils::INTEGER)
			{
				flag = static_cast<bool>(std::stoi(line[1]));
			}
			else if (Utils::Get_literal_type(line[1]) == Utils::DOUBLE)
			{
				flag = static_cast<bool>(std::stod(line[1]));
			}
			else if(Utils::Get_literal_type(line[1]) == Utils::STRING)
			{
				flag = (line[1] != "" ? 1 : 0);
			}
		}
	}
	else if (line.size() == 4)
	{
		if (myElements.find(line[1]) != myElements.end()
			&& myElements.find(line[3]) != myElements.end())
		{
			if (line[2] == "==")
			{
				flag = myElements[line[1]] == myElements[line[3]];
			}
			else if (line[2] == "!=")
			{
				flag = myElements[line[1]] != myElements[line[3]];
			}
			else if (line[2] == ">=")
			{
				flag = myElements[line[1]] >= myElements[line[3]];
			}
			else if (line[2] == "<=")
			{
				flag = myElements[line[1]] <= myElements[line[3]];
			}
			else if (line[2] == "<")
			{
				flag = myElements[line[1]] < myElements[line[3]];
			}
			else if (line[2] == ">")
			{
				flag = myElements[line[1]] > myElements[line[3]];
			}
		}
		else if (myElements.find(line[1]) != myElements.end()
				&& myElements.find(line[3]) == myElements.end())
		{
			if (line[2] == "==")
			{
				if (Utils::Get_literal_type(line[3]) == Utils::BOOLEAN)
					flag = myElements[line[1]] == ((line[3] == "true" || line[3] == "TRUE") ? 1 : 0);
				else if (Utils::Get_literal_type(line[3]) == Utils::INTEGER)
					flag = myElements[line[1]] == std::stoi(line[3]);
				else if (Utils::Get_literal_type(line[3]) == Utils::DOUBLE)
					flag = myElements[line[1]] == std::stod(line[3]);
			}
			else if (line[2] == "!=")
			{
				if (Utils::Get_literal_type(line[3]) == Utils::BOOLEAN)
					flag = myElements[line[1]] != ((line[3] == "true" || line[3] == "TRUE") ? 1 : 0);
				else if (Utils::Get_literal_type(line[3]) == Utils::INTEGER)
					flag = myElements[line[1]] != std::stoi(line[3]);
				else if (Utils::Get_literal_type(line[3]) == Utils::DOUBLE)
					flag = myElements[line[1]] != std::stod(line[3]);
			}
			else if (line[2] == ">=")
			{
				if (Utils::Get_literal_type(line[3]) == Utils::INTEGER)
					flag = myElements[line[1]] >= std::stoi(line[3]);
				else if (Utils::Get_literal_type(line[3]) == Utils::DOUBLE)
					flag = myElements[line[1]] >= std::stod(line[3]);
			}
			else if (line[2] == "<=")
			{
				if (Utils::Get_literal_type(line[3]) == Utils::INTEGER)
					flag = myElements[line[1]] <= std::stoi(line[3]);
				else if (Utils::Get_literal_type(line[3]) == Utils::DOUBLE)
					flag = myElements[line[1]] <= std::stod(line[3]);
			}
			else if (line[2] == "<")
			{
				if (Utils::Get_literal_type(line[3]) == Utils::INTEGER)
					flag = myElements[line[1]] < std::stoi(line[3]);
				else if (Utils::Get_literal_type(line[3]) == Utils::DOUBLE)
					flag = myElements[line[1]] < std::stod(line[3]);
			}
			else if (line[2] == ">")
			{
				if (Utils::Get_literal_type(line[3]) == Utils::INTEGER)
					flag = myElements[line[1]] > std::stoi(line[3]);
				else if (Utils::Get_literal_type(line[3]) == Utils::DOUBLE)
					flag = myElements[line[1]] > std::stod(line[3]);
			}
		}
		else if (myElements.find(line[1]) == myElements.end()
				&& myElements.find(line[3]) != myElements.end())
		{
			if (line[2] == "==")
			{
				if (Utils::Get_literal_type(line[1]) == Utils::BOOLEAN)
					flag = myElements[line[3]] == ((line[1] == "true" || line[1] == "TRUE") ? 1 : 0);
				else if (Utils::Get_literal_type(line[1]) == Utils::INTEGER)
					flag = myElements[line[3]] == std::stoi(line[1]);
				else if (Utils::Get_literal_type(line[1]) == Utils::DOUBLE)
					flag = myElements[line[3]] == std::stod(line[1]);
			}
			else if (line[2] == "!=")
			{
				if (Utils::Get_literal_type(line[1]) == Utils::BOOLEAN)
					flag = myElements[line[3]] != ((line[1] == "true" || line[1] == "TRUE") ? 1 : 0);
				else if (Utils::Get_literal_type(line[1]) == Utils::INTEGER)
					flag = myElements[line[3]] != std::stoi(line[1]);
				else if (Utils::Get_literal_type(line[1]) == Utils::DOUBLE)
					flag = myElements[line[3]] != std::stod(line[1]);
			}
			else if (line[2] == ">=")
			{
				if (Utils::Get_literal_type(line[1]) == Utils::INTEGER)
					flag = myElements[line[3]] >= std::stoi(line[1]);
				else if (Utils::Get_literal_type(line[1]) == Utils::DOUBLE)
					flag = myElements[line[3]] >= std::stod(line[1]);
			}
			else if (line[2] == "<=")
			{
				if (Utils::Get_literal_type(line[1]) == Utils::INTEGER)
					flag = myElements[line[3]] <= std::stoi(line[1]);
				else if (Utils::Get_literal_type(line[1]) == Utils::DOUBLE)
					flag = myElements[line[3]] <= std::stod(line[1]);
			}
			else if (line[2] == "<")
			{
				if (Utils::Get_literal_type(line[1]) == Utils::INTEGER)
					flag = myElements[line[3]] < std::stoi(line[1]);
				else if (Utils::Get_literal_type(line[1]) == Utils::DOUBLE)
					flag = myElements[line[3]] < std::stod(line[3]);
			}
			else if (line[2] == ">")
			{
				if (Utils::Get_literal_type(line[1]) == Utils::INTEGER)
					flag = myElements[line[3]] > std::stoi(line[1]);
				else if (Utils::Get_literal_type(line[1]) == Utils::DOUBLE)
					flag = myElements[line[3]] > std::stod(line[1]);
			}
		}
		else
		{
			throw "Syntax ERROR";
		}
	}
	return (flag);
}
