/* Citation and Sources...
Final Project Milestone 5
Module: Menu
Filename: Menu.cpp
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
#include <cstring>
#include "Menu.h"
#include "utils.h"

namespace sdds {
	void Menu::display() const
	{
		std::cout << m_text << std::endl << "0- Exit" << std::endl;
	}
	Menu::Menu(const char* MenuContent, int NoOfSelections)
	{
		m_noOfSel = 0;
		m_text = nullptr;
		if (MenuContent != nullptr) {
			m_text = new char[strlen(MenuContent) + 1];
			strcpy(m_text, MenuContent);
			m_noOfSel = NoOfSelections;
		}
	}
	Menu::Menu(const Menu& menu)
	{
		*this = menu;
	}
	Menu& Menu::operator=(const Menu& menu)
	{
		if (menu.m_text != nullptr) {
			m_text = new char[strlen(menu.m_text) + 1];
			strcpy(m_text, menu.m_text);
			m_noOfSel = menu.m_noOfSel;
		}
		return *this;
	}
	Menu::~Menu()
	{
		delete[] m_text;
	}
	int& Menu::operator>>(int& Selection)
	{
		display();
		Selection = getInt(0, m_noOfSel, "> ", "Invalid option ", true);
		return Selection;
	}
}