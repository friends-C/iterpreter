#include "MyType.h"


MyType::enumType MyType::getType(const std::string& str)
{
	try
	{
		if (str == "tiv")
		{
			return (INTEGER);
		}
		else if (str == "ketikov")
		{
			return (DOUBLE);
		}
		else if (str == "tox")
		{
			return (STRING);
		}
		else if (str == "logic")
		{
			return (BOOLEAN);
		}
		else
		{
			throw std::exception();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "no such type exists" << std::endl;
		exit(1);
	}
	return (INTEGER);
}

MyType::enumType MyType::_Get_type(const std::string& str)
{
	if (str == "TRUE" || str == "FALSE")
	{
		return BOOLEAN;
	}
    std::size_t found = str.find('.');
    if (found != std::string::npos)
    {
          return DOUBLE;
    }
    found = str.find('"');
    if(found != std::string::npos)
    {
        return STRING;
    }
    return INTEGER;
}

void	swap(MyType& first, MyType& second) noexcept
{
	using std::swap;

	swap(first.val_type, second.val_type);
	swap(first.val, second.val);
	swap(first.nbr, second.nbr);
	swap(first.d_nbr, second.d_nbr);
	swap(first.str, second.str);

}

MyType::MyType(MyType&& other)
{
	swap(*this, other);
}

MyType&	MyType::operator=(const MyType& type)
{
	if (this == &type)
	{
		return *this;
	}
	MyType tmp(type);
	swap(*this, tmp);
	return (*this);
}

MyType& MyType::operator=(MyType&& type)
{
	MyType tmp(std::move(type));
	swap(*this, tmp);
	return *this;
}

MyType operator+(const MyType& lhs, const MyType& rhs)
{
	MyType tmp;
	try{
		if(lhs.val_type == 0 &&  rhs.val_type == 0)
		{
			tmp.val_type = MyType::enumType::INTEGER;
			tmp.nbr = lhs.nbr + rhs.nbr;
		}
		else if (lhs.val_type == 1 &&  rhs.val_type == 1)
		{
			tmp.val_type = MyType::enumType::DOUBLE;
			tmp.d_nbr = lhs.d_nbr + rhs.d_nbr;
		}
		else if (lhs.val_type == 3 &&  rhs.val_type == 3)
		{
			tmp.val_type = MyType::enumType::STRING;
			tmp.str = lhs.str + rhs.str;
		}
		else
		{
			throw std::exception();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "ERROR" << std::endl;
		exit(1);
	}
	return (tmp);
}

MyType operator-(const MyType& lhs, const MyType& rhs)
{
	MyType tmp;
	try
	{
		if(lhs.val_type == 0 &&  rhs.val_type == 0)
		{
			tmp.val_type = MyType::enumType::INTEGER;
			tmp.nbr = lhs.nbr - rhs.nbr;
		}
		else if (lhs.val_type == 1 &&  rhs.val_type == 1)
		{
			tmp.val_type = MyType::enumType::DOUBLE;
			tmp.d_nbr = lhs.d_nbr - rhs.d_nbr;
		}
		else
		{
			throw std::exception();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "ERROR" << std::endl;
		exit(1);
	}
	
	
	return (tmp);
}

MyType operator*(const MyType& lhs, const MyType& rhs)
{
	MyType tmp;
	try
	{
		if(lhs.val_type == 0 &&  rhs.val_type == 0)
		{
			tmp.val_type = MyType::enumType::INTEGER;
			tmp.nbr = lhs.nbr * rhs.nbr;
		}
		else if (lhs.val_type == 1 &&  rhs.val_type == 1)
		{
			tmp.val_type = MyType::enumType::DOUBLE;
			tmp.d_nbr = lhs.d_nbr * rhs.d_nbr;
		}
		else
		{
			throw std::exception();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "ERROR" << std::endl;
		exit(1);
	}
	return (tmp);
}

MyType operator/(const MyType& lhs, const MyType& rhs)
{
	MyType tmp;
	try
	{
		if(lhs.val_type == 0 &&  rhs.val_type == 0)
		{
			if (rhs.nbr == 0)
			{
				throw std::exception();
			}
			tmp.val_type = MyType::enumType::INTEGER;
			tmp.nbr = lhs.nbr / rhs.nbr;
		}
		else if (lhs.val_type == 1 &&  rhs.val_type == 1)
		{
			if (rhs.d_nbr == 0)
			{
				throw std::exception();
			}
			tmp.val_type = MyType::enumType::DOUBLE;
			tmp.d_nbr = lhs.d_nbr / rhs.d_nbr;
		}
		else
		{
			throw std::exception();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "ERROR" << std::endl;
		exit(1);
	}
	return (tmp);
}

bool	operator==(const MyType& lhs, const MyType& rhs)
{
	if (lhs.val_type != rhs.val_type)
		throw "variables have different types";
	else if (lhs.val_type == MyType::INTEGER)
	   return (lhs.nbr == rhs.nbr);
	else if (lhs.val_type == MyType::DOUBLE)
	   return (lhs.d_nbr == rhs.d_nbr);	
	else if (lhs.val_type == MyType::STRING)
	   return (lhs.str == rhs.str);	
	else
	   return (lhs.val == rhs.val);	
}

bool	operator!=(const MyType& lhs, const MyType& rhs)
{
	return (!(lhs == rhs));
}

bool	operator<(const MyType& lhs, const MyType& rhs)
{
	if (lhs.val_type != rhs.val_type)
		throw "variables have different types";
	else if (lhs.val_type == MyType::INTEGER)
	   return (lhs.nbr < rhs.nbr);
	else if (lhs.val_type == MyType::DOUBLE)
	   return (lhs.d_nbr < rhs.d_nbr);	
	else if (lhs.val_type == MyType::STRING)
	   return (lhs.str < rhs.str);	
	else
	   return (lhs.val < rhs.val);
}


bool	operator>(const MyType& lhs, const MyType& rhs)
{
	return (!(lhs == rhs || lhs < rhs));
}

bool	operator<=(const MyType& lhs, const MyType& rhs)
{
	return (lhs == rhs || lhs < rhs);
}

bool	operator>=(const MyType& lhs, const MyType& rhs)
{
	return (!(lhs < rhs));
}

