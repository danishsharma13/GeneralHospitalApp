/* Citation and Sources...
Final Project Milestone 5
Module: Menu
Filename: Menu.h
Version 1.0
Author: Danish Sharma
-----------------------------------------------------------
Date: 2021 July 28
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#ifndef SDDS_MENU_H
#define SDDS_MENU_H
namespace sdds {
    class Menu {
        char* m_text;
        int m_noOfSel;
        void display()const;
    public:
        Menu(const char* MenuContent, int NoOfSelections);
        Menu(const Menu&);
        Menu& operator=(const Menu&);
        virtual ~Menu();
        int& operator>>(int& Selection);
    };
}
#endif // SDDS_MENU_H