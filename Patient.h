/* Citation and Sources...
Final Project Milestone 5
Module: Patient
Filename: Patient.h
Version 1.0
Author: Danish Sharma
-----------------------------------------------------------
Date: 2021 July 28
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#ifndef SDDS_PATIENT_H
#define SDDS_PATIENT_H
#include "Ticket.h"
namespace sdds {
	class Patient :public IOAble {
		char* m_name{};
		int m_insurance{};
		Ticket m_ticket;
		bool m_flag;
	public:
		Patient(int ticket_num = 0, bool flag = false);
		Patient(const Patient&) = delete;
		Patient& operator=(const Patient&) = delete;
		~Patient();
		virtual char type()const = 0;
		bool fileIO()const;
		void fileIO(bool flag);
		bool operator==(const char character)const;
		bool operator==(const Patient& patient)const;
		void setArrivalTime();
		operator Time()const;
		int number()const;
		std::ostream& csvWrite(std::ostream& ostr)const;
		std::istream& csvRead(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
	};
}
#endif // !SDDS_PATIENT_H