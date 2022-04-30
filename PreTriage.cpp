/* Citation and Sources...
Final Project Milestone 5
Module: PreTriage
Filename: PreTriage.h
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
#include "PreTriage.h"
#include "utils.h"
#include "CovidPatient.h"
#include "TriagePatient.h"
#include <cstring>
#include <fstream>
namespace sdds {
	PreTriage::PreTriage(const char* dataFilename): m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2), m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2) 
	{
		m_dataFilename = new char[strlen(dataFilename) + 1];
		strcpy(m_dataFilename, dataFilename);
		m_averCovidWait = 15;
		m_averTriageWait = 5;
		load();
	}

	PreTriage::~PreTriage()
	{
		std::ofstream csvOutFile;
		int i;
		if (m_dataFilename != nullptr) {
			std::cout << "Saving Average Wait Times," << std::endl;
			std::cout << "   COVID Test: " << m_averCovidWait << std::endl;
			std::cout << "   Triage: " << m_averTriageWait << std::endl;
			std::cout << "Saving m_lineup..." << std::endl;
			std::ofstream csvOutFile(m_dataFilename);

			csvOutFile << m_averCovidWait << "," << m_averTriageWait << std::endl;

			for (i = 0; m_lineup[i] != nullptr && i < m_lineupSize; i++) {
				std::cout << i + 1 << "- ";
				
				m_lineup[i]->csvWrite(std::cout);
				std::cout << std::endl;
				m_lineup[i]->csvWrite(csvOutFile);
				csvOutFile << std::endl;
			}
			for (i = 0; i < m_lineupSize && m_lineup[i] != nullptr; i++) {
				delete m_lineup[i];
			}
			delete[] m_dataFilename;
			csvOutFile.close();
			std::cout << "done!" << std::endl;
		}
	}

	const Time PreTriage::getWaitTime(const Patient& p) const
	{
		int counter = 0, i;
		Time waitTime{};
		for (i = 0; m_lineup[i] != nullptr && i < m_lineupSize; i++) {
			if (p.type() == m_lineup[i]->type()) {
				counter++;
			}
		}
		if (p.type() == 'C') {
			waitTime = int(m_averCovidWait) * counter;
		}
		else if (p.type() == 'T') {
			waitTime = int(m_averTriageWait) * counter;
		}
		return waitTime;
	}

	void PreTriage::setAverageWaitTime(const Patient& p)
	{
		Time currentTime;
		currentTime.setToNow();
		if (p.type() == 'T') {
			m_averTriageWait = (unsigned int)((int(currentTime - p) + (int(m_averTriageWait) * (p.number() - 1))) / p.number());
		}
		else if (p.type() == 'C') {
			m_averCovidWait = (unsigned int)((int(currentTime - p) + (int(m_averCovidWait) * (p.number() - 1))) / p.number());
		}
	}

	void PreTriage::removePatientFromLineup(int index)
	{
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}

	int PreTriage::indexOfFirstInLine(char type) const
	{
		int i, index = -1;
		for (i = 0; i < m_lineupSize && m_lineup[i] != nullptr; i++) {
			if (m_lineup[i]->type() == type) {
				index = i;
				i = m_lineupSize;
			}
		}
		return index;
	}

	void PreTriage::load()
	{
		int i;
		char type;
		std::ifstream csvInFile(m_dataFilename);
		Patient* patient{};
		std::cout << "Loading data..." << std::endl;
		if (csvInFile.is_open()) {
			csvInFile >> m_averCovidWait;
			csvInFile.ignore();
			csvInFile >> m_averTriageWait;
			csvInFile.ignore(10, '\n');
			for (i = 0; i < maxNoOfPatients && csvInFile.peek() != EOF; i++) {
				csvInFile >> type;
				csvInFile.ignore();
				if (type == 'C') {
					patient = new CovidPatient();
				}
				else  if (type == 'T') {
					patient = new TriagePatient();
				}

				if (patient != nullptr) {
					patient->fileIO(true);
					patient->read(csvInFile);
					patient->fileIO(false);

				}
				m_lineup[i] = patient;
				m_lineupSize++;
			}
		}
		if (csvInFile.peek() != EOF) {
			std::cout << "Warning: number of records exceeded " << maxNoOfPatients << std::endl;

		}
		if (m_lineup[0] == nullptr || m_lineupSize == 0) {
			std::cout << "No data or bad data file!" << std::endl << std::endl;
		}
		else {
			std::cout << m_lineupSize << " Records imported..." << std::endl << std::endl;
		}

	}

	void PreTriage::reg() 
	{
		int sel;
		if (m_lineupSize < maxNoOfPatients) {
			m_pMenu >> sel;
			if (sel != 0) {
				if (sel == 1) {
					m_lineup[m_lineupSize] = new CovidPatient();
					
				}
				else if (sel == 2) {
					m_lineup[m_lineupSize] = new TriagePatient();
				}

				m_lineup[m_lineupSize]->setArrivalTime();
				std::cout << "Please enter patient information: " << std::endl;
				m_lineup[m_lineupSize]->fileIO(false);
				m_lineup[m_lineupSize]->read(std::cin);
				std::cout << std::endl;
				std::cout << "******************************************" << std::endl;
				m_lineup[m_lineupSize]->write(std::cout);
				// std::cout << *m_lineup[m_lineupSize]; can use this as well
				std::cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[m_lineupSize]) << std::endl;
				m_lineupSize++;
				std::cout << "******************************************" << std::endl << std::endl;
			}
		}
		else {
			std::cout << "Line up full!" << std::endl;
		}
	}

	void PreTriage::admit()
	{
		int sel, index;
		char type = 'x';
		m_pMenu >> sel;
		if (sel != 0) {
			if (sel == 1) {
				type = 'C';
			}
			else if (sel == 2) {
				type = 'T';
			}
			index = indexOfFirstInLine(type);
			std::cout << std::endl;
			if (index != -1) {
				std::cout << "******************************************" << std::endl;
				m_lineup[index]->fileIO(false);
				std::cout << "Calling for " << *m_lineup[index];
				std::cout << "******************************************" << std::endl << std::endl;
				setAverageWaitTime(*m_lineup[index]);
				removePatientFromLineup(index);
			}
		} 
	}

	void PreTriage::run(void) 
	{
		int sel;
		bool run = true;
		while (run) {
			m_appMenu >> sel;
			if (sel == 1) {
				reg();
			}
			else if (sel == 2) {
				admit();
			}
			else if (sel == 0) {
				run = false;
			}
		}
	}
}