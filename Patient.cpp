/* Citation and Sources...
Final Project Milestone 5
Module: Patient
Filename: Patient.cpp
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
#include "Patient.h"
#include "utils.h"
#include <string>
#include <cstring>
namespace sdds {
	Patient::Patient(int ticket_num, bool flag) : m_ticket(ticket_num), m_flag(flag) {}

	Patient::~Patient()
	{
		delete[] m_name;
	}

	bool Patient::fileIO() const
	{
		return m_flag;
	}

	void Patient::fileIO(bool flag) 
	{
		m_flag = flag;
	}

	bool Patient::operator==(const char character)const
	{
		return this->type() == character;
	}

	bool Patient::operator==(const Patient& patient) const
	{
		return this->type() == patient.type();
	}

	void Patient::setArrivalTime() 
	{
		m_ticket.resetTime();
	}

	Patient::operator Time() const
	{
		return Time(m_ticket);
	}

	int Patient::number()const 
	{
		return m_ticket.number();
	}

	std::ostream& Patient::csvWrite(std::ostream& ostr) const
	{
		ostr << type() << "," << m_name << "," << m_insurance << ",";
		m_ticket.csvWrite(ostr);
		return ostr;
	}

	std::istream& Patient::csvRead(std::istream& istr)
	{
		std::string input;
		if (m_name != nullptr) delete[] m_name;

		std::getline(istr, input, ',');
		if (input != "") {
			m_name = new char[input.length() + 1];
			strcpy(m_name, input.c_str());
			m_name[input.length()] = '\0';
			std::getline(istr, input, ',');
			m_insurance = std::stoi(input);
		}
		m_ticket.csvRead(istr);

		return istr;
	}

	std::ostream& Patient::write(std::ostream& ostr) const
	{
		int i = 0;
		ostr << m_ticket << std::endl;

		for (i = 0; i < 25 && m_name[i] != '\0'; i++) 
		{
			ostr << m_name[i];
		}

		ostr << ", OHIP: " << m_insurance;
		return ostr;
	}

	std::istream& Patient::read(std::istream& istr) {
		if (m_name != nullptr) delete[] m_name;
		m_name = getcstr("Name: ", istr, '\n');
		m_insurance = getInt(100000000, 999999999,"OHIP: ", "Invalid OHIP Number, ", true);
		return istr;
	}

}
