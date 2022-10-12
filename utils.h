#ifndef UTILS_H
# define UTILS_H

# include <string>

namespace Utils
{
	enum Type
	{
		INTEGER	= 0,
		DOUBLE	= 1,
		BOOLEAN	= 2,
		STRING	= 3
	};
	bool is_bool(const std::string& str);
	bool is_number(const std::string& str);
	bool is_double(const std::string& str);

	//funcions that determine literal and variable types
	//-----------------------------------------------
	Type Get_variable_type(const std::string& str);
	Type Get_literal_type(const std::string& str);
};

#endif