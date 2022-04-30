/* Citation and Sources...
Final Project Milestone 5
Module: IOAble
Filename: IOAble.h
Version 1.0
Author: Danish Sharma
-----------------------------------------------------------
Date: 2021 July 28
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#ifndef SDDS_IOABLE_H
#define SDDS_IOABLE_H
#include <iostream>
namespace sdds {
	class IOAble {
	public:
		virtual ~IOAble();
		virtual std::ostream& csvWrite(std::ostream& ostr)const = 0;
		virtual std::istream& csvRead(std::istream& istr) = 0;
		virtual std::ostream& write(std::ostream& ostr)const = 0;
		virtual std::istream& read(std::istream& istr) = 0;
	};

	std::ostream& operator<<(std::ostream& ostr, const IOAble& ioable);
	std::istream& operator>>(std::istream& istr, IOAble& ioable);
}

#endif // !SDDS_IOABLE_H