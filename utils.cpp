#include	"utils.h"

bool Utils::is_bool(const std::string& str)
{
	if (str == "TRUE" || str == "FALSE"
		|| str == "true" || str == "false")
	{
		return (1);
	}
	return (0);
}

bool Utils::is_number(const std::string& str)
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (0);
		}
	}
	return (1);
}

bool Utils::is_double(const std::string& str)
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] == '.')
		{
			continue ;
		}
		if (str[i] < '0' || str[i] > '9')
		{
			return (0);
		}
	}
	return (1);
}

Utils::Type	Utils::Get_variable_type(const std::string& str)
{
	if (str == "tiv")
	{
		return (Utils::INTEGER);
	}
	else if (str == "tox")
	{
		return (Utils::STRING);
	}
	else if (str == "logic")
	{
		return (Utils::BOOLEAN);
	}
	else if (str == "ketikov")
	{
		return (Utils::DOUBLE);
	}
	else
	{
		throw "no such type exists";
	}
}

Utils::Type	Utils::Get_literal_type(const std:: string& str)
{
	if (is_bool(str))
	{
		return (Utils::BOOLEAN);
	}
	else if (is_number(str))
	{
		return (Utils::INTEGER);
	}
	else if (is_double(str))
	{
		return (Utils::DOUBLE);
	}
	else
	{
		return (Utils::STRING);
	}
}