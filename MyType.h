#ifndef MYTYPE_H
# define MYTYPE_H

# include "utils.h"
# include <iostream>
# include <exception>

class MyType
{
public:
	//constructors
	MyType() = default;
	MyType(const MyType& other) = default;
	MyType(MyType&& other);
	MyType(bool val) : my_type(Utils::BOOLEAN), value(val) {}
	MyType(const std::string& s) : my_type(Utils::STRING), str(s) {}
	MyType(const int nbr) : my_type(Utils::INTEGER), number(nbr) {}
	MyType(const double float_n) : my_type(Utils::DOUBLE), floate_number(float_n) {}

	// assignment and move operators
	//-----------------------------------------------
	MyType&	operator=(const MyType& other);
	MyType&	operator=(MyType&& other);
	//-----------------------------------------------

	// private section for member function
	friend void	swap(MyType& first, MyType& second);

	//binary operators +, -, *, /
	//-----------------------------------------------
	friend	MyType operator+(const MyType& lhs, const MyType& rhs);
	friend	MyType operator-(const MyType& lhs, const MyType& rhs);
	friend	MyType operator*(const MyType& lhs, const MyType& rhs);
	friend	MyType operator/(const MyType& lhs, const MyType& rhs);
	//-----------------------------------------------

	//		Binary comparison operators
	//----------------------------------------------------------------------
	friend bool operator==(const MyType& lhs, const MyType& rhs);
	friend bool operator!=(const MyType& lhs, const MyType& rhs);
	friend bool operator>(const MyType& lhs, const MyType& rhs);
	friend bool operator<(const MyType& lhs, const MyType& rhs);
	friend bool operator<=(const MyType& lhs, const MyType& rhs);
	friend bool operator>=(const MyType& lhs, const MyType& rhs);
	//----------------------------------------------------------------------

	//seter-geter functions
	//-----------------------------------------------
		void set_type(const Utils::Type& type) { this->my_type = type; }
		Utils::Type get_type() const	{ return (my_type); }

		void set_int(int n) { this->number = n; }
		int get_int() const { return number; }

		void set_double(double d) { this->floate_number = d;}
		double get_double() const { return floate_number; }

		void set_string(const std::string& s) { this->str = s; }
		std::string get_string() const { return str; }

		void set_bool(bool val) { this->value = val; }
		bool get_bool() const { return value; }
	//-----------------------------------------------
private:
	// private section for member data
	Utils::Type	my_type;
	bool value;
	int number;
	double floate_number;
	std::string str;
};

#endif