/* Citation and Sources...
Final Project Milestone 5
Module: IOAble
Filename: IOAble.cpp
Version 1.0
Author: Danish Sharma
-----------------------------------------------------------
Date: 2021 July 28
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "IOAble.h"

namespace sdds {
	IOAble::~IOAble()
	{
		// empty destructor
	}
	std::ostream& operator<<(std::ostream& ostr, const IOAble& ioable)
	{
		ioable.write(ostr);
		return ostr;
	}
	std::istream& operator>>(std::istream& istr, IOAble& ioable)
	{
		ioable.read(istr);
		return istr;
	}
}