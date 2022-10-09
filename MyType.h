#ifndef MYTYPE_H
# define MYTYPE_H

# include <string>
# include <utility>
# include <exception>
# include <iostream>

class MyType
{
	public:
		MyType() = default;
		MyType(int n) : val_type(INTEGER), nbr(n) {	}
		MyType(double d_n) : val_type(DOUBLE), d_nbr(d_n) {	}
		MyType(const std::string& s) : val_type(STRING), str(s) {	}
		MyType(const MyType& other) = default;
		MyType(MyType&& other);
		~MyType() = default;
		
		enum enumType
		{
			INTEGER	= 0,
			DOUBLE	= 1,
			BOOLEAN	= 2,
			STRING	= 3
		};


		friend void	swap(MyType& first, MyType& second) noexcept;

//		funcions that determine literal and variable types
//----------------------------------------------------------------------
		static enumType getType(const std::string& str);
		static enumType _Get_type(const std::string& str);
//----------------------------------------------------------------------

//		assignment and move assigment operators
//---------------------------------------------
		MyType&	operator=(const MyType& type);
		MyType& operator=(MyType&& type);
//---------------------------------------------

//		binary operator+, operator-, operator*, operator/,
//----------------------------------------------------------------------
		friend MyType operator+(const MyType& lhs, const MyType& rhs);
		friend MyType operator-(const MyType& lhs, const MyType& rhs);
		friend MyType operator*(const MyType& lhs, const MyType& rhs);
		friend MyType operator/(const MyType& lhs, const MyType& rhs);
//----------------------------------------------------------------------

//		Binary comparison operators
//----------------------------------------------------------------------
		friend bool operator==(const MyType& lhs, const MyType& rhs);
		friend bool operator!=(const MyType& lhs, const MyType& rhs);
		friend bool operator>(const MyType& lhs, const MyType& rhs);
		friend bool operator<(const MyType& lhs, const MyType& rhs);
		friend bool operator<=(const MyType& lhs, const MyType& rhs);
		friend bool operator>=(const MyType& lhs, const MyType& rhs);
//----------------------------------------------------------------------

//		seter-geter functions
//----------------------------------------------------------------------
		void		set_type(const enumType& type) { this->val_type = type; }
		enumType	get_type() const	{ return (val_type); }

		void		set_int(int n) { this->nbr = n; }
		int			get_int() const { return nbr; }

		void		set_double(double d) { this->d_nbr = d;}
		double		get_double() const { return d_nbr; }

		void		set_string(const std::string& s) { this->str = s; }
		std::string	get_string() const { return str; }

		void		set_bool(bool value) { val = value; }
		bool		get_bool() const { return val; }
//----------------------------------------------------------------------
	private:
		enumType	val_type;
		bool		val;
		int			nbr;
		double		d_nbr;
		std::string	str;
};


#endif
