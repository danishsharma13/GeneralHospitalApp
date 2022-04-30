/* Citation and Sources...
Final Project Milestone 5
Module: Triage Patient
Filename: TriagePatient.h
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
#include "TriagePatient.h"
#include <string>
#include <cstring>
#include "utils.h"
namespace sdds {
   int nextTriageTicket = 1;

   TriagePatient::TriagePatient() : Patient(nextTriageTicket), m_symptoms{}
   {
	   nextTriageTicket++;
   }

   char TriagePatient::type() const
   {
	   return 'T';
   }

   TriagePatient::~TriagePatient()
   {
	   delete[] m_symptoms;
   }

   std::ostream& TriagePatient::csvWrite(std::ostream& ostr) const
   {
	   Patient::csvWrite(ostr);
	   ostr << "," << m_symptoms;
	   return ostr;
   }

   std::istream& TriagePatient::csvRead(std::istream& istr)
   {
	   std::string input;
	   if (m_symptoms != nullptr) delete[] m_symptoms;
	   Patient::csvRead(istr);
	   istr.ignore();
	   std::getline(istr, input, '\n');
	   m_symptoms = new char[(input.length()) + 1];
	   strcpy(m_symptoms, input.c_str());
	   m_symptoms[input.length()] = '\0';
	   nextTriageTicket = Patient::number() + 1;
	   return istr;
   }

   std::ostream& TriagePatient::write(std::ostream& ostr) const
   {
	   if (Patient::fileIO()) {
		   csvWrite(ostr);
	   }
	   else {
		   ostr << "TRIAGE" << std::endl;
		   Patient::write(ostr);
		   ostr << std::endl << "Symptoms: " << m_symptoms << std::endl;
	   }
	   return ostr;
   }

   std::istream& TriagePatient::read(std::istream& istr)
   {
	   std::string input;
	   if (Patient::fileIO()) {
		   csvRead(istr);
	   }
	   else {
		   if (m_symptoms != nullptr) delete[] m_symptoms;
		   Patient::read(istr);
		   std::cout << "Symptoms: ";
		   std::string input;
		   m_symptoms = getcstr(nullptr, istr);
		   m_symptoms[strlen(m_symptoms)] = '\0';
	   }
	   return istr;
   }

}