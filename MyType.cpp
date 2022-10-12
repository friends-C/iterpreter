#include "MyType.h"

void swap(MyType& first, MyType& second)
{
	using std::swap;

	swap(first.my_type, second.my_type);
	swap(first.number, second.number);
	swap(first.floate_number, second.floate_number);
	swap(first.value, second.value);
	swap(first.str, second.str);
}

MyType::MyType(MyType&& other)
{
	swap(*this, other);
}

MyType&	MyType::operator=(const MyType& other)
{
	if (this == &other)
	{
		return (*this);
	}
	MyType	tmp(other);
	swap(*this, tmp);
	return (*this);
}

MyType&	MyType::operator=(MyType&& other)
{
	MyType	tmp(std::move(other));
	swap(*this, tmp);
	return (*this);
}

MyType operator+(const MyType& lhs, const MyType& rhs)
{
	MyType	tmp;
	if (lhs.my_type == Utils::INTEGER && rhs.my_type == Utils::INTEGER)
	{
		tmp.my_type = Utils::INTEGER;
		tmp.number = lhs.number + rhs.number;
	}
	else if (lhs.my_type == Utils::DOUBLE && rhs.my_type == Utils::DOUBLE)
	{
		tmp.my_type = Utils::DOUBLE;
		tmp.floate_number = lhs.floate_number + rhs.floate_number;
	}
	else if (lhs.my_type == Utils::STRING && rhs.my_type == Utils::STRING)
	{
		tmp.my_type = Utils::STRING;
		tmp.str = lhs.str + rhs.str;
	}
	else
	{
		throw "cannot be added";
	}
	return (tmp);
}

MyType operator-(const MyType& lhs, const MyType& rhs)
{
	MyType tmp;
	if(lhs.my_type == Utils::INTEGER && rhs.my_type == Utils::INTEGER)
	{
		tmp.my_type = Utils::INTEGER;
		tmp.number = lhs.number - rhs.number;
	}
	else if (lhs.my_type == Utils::DOUBLE && rhs.my_type == Utils::DOUBLE)
	{
		tmp.my_type = Utils::DOUBLE;
		tmp.floate_number = lhs.floate_number - rhs.floate_number;
	}
	else
	{
		throw "cannot be subtraction";
	}
	return (tmp);
}

MyType operator*(const MyType& lhs, const MyType& rhs)
{
	MyType tmp;
	if(lhs.my_type == Utils::INTEGER && rhs.my_type == Utils::INTEGER)
	{
		tmp.my_type = Utils::INTEGER;
		tmp.number = lhs.number * rhs.number;
	}
	else if (lhs.my_type == Utils::DOUBLE && rhs.my_type == Utils::DOUBLE)
	{
		tmp.my_type = Utils::DOUBLE;
		tmp.floate_number = lhs.floate_number * rhs.floate_number;
	}
	else
	{
		throw "cannot be multiplication";
	}
	return (tmp);
}

MyType operator/(const MyType& lhs, const MyType& rhs)
{
	MyType tmp;
	if(lhs.my_type == Utils::INTEGER && rhs.my_type == Utils::INTEGER)
	{
		if (rhs.number == 0)
		{
			throw "divided by 0";
		}
		tmp.my_type = Utils::INTEGER;
		tmp.number = lhs.number / rhs.number;
	}
	else if (lhs.my_type == Utils::DOUBLE && rhs.my_type == Utils::DOUBLE)
	{
		if (rhs.floate_number == 0)
		{
			throw "divided by 0";
		}
		tmp.my_type = Utils::DOUBLE;
		tmp.floate_number = lhs.floate_number / rhs.floate_number;
	}
	else
	{
		throw "cannot be divided";
	}
	return (tmp);
}

bool	operator==(const MyType& lhs, const MyType& rhs)
{
	if (lhs.my_type != rhs.my_type)
		throw "variables have different types";
	else if (lhs.my_type == Utils::INTEGER)
	   return (lhs.number == rhs.number);
	else if (lhs.my_type == Utils::DOUBLE)
	   return (lhs.floate_number == rhs.floate_number);	
	else if (lhs.my_type == Utils::STRING)
	   return (lhs.str == rhs.str);	
	else
	   return (lhs.value == rhs.value);	
}

bool operator!=(const MyType& lhs, const MyType& rhs)
{
	return (!(lhs == rhs));
}

bool operator<(const MyType& lhs, const MyType& rhs)
{
	if (lhs.my_type != rhs.my_type)
		throw "variables have different types";
	else if (lhs.my_type == Utils::INTEGER)
	   return (lhs.number < rhs.number);
	else if (lhs.my_type == Utils::DOUBLE)
	   return (lhs.floate_number < rhs.floate_number);	
	else if (lhs.my_type == Utils::STRING)
	   return (lhs.str < rhs.str);	
	else
	   return (lhs.value < rhs.value);
}

bool operator>(const MyType& lhs, const MyType& rhs)
{
	return (!(lhs == rhs || lhs < rhs));
}

bool operator<=(const MyType& lhs, const MyType& rhs)
{
	return (lhs == rhs || lhs < rhs);
}

bool operator>=(const MyType& lhs, const MyType& rhs)
{
	return (!(lhs < rhs));
}

