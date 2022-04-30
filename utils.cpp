/* Citation and Sources...
Final Project Milestone 5
Module: utils
Filename: utils.cpp
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
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds {
    bool debug = false;  // made global in utils.h
    int getTime() {
        int mins = -1;
        if (debug) {
            Time t(0);
            cout << "Enter current time: ";
            do {
                cin.clear();
                cin >> t;   // needs extraction operator overloaded for Time
                if (!cin) {
                    cout << "Invlid time, try agian (HH:MM): ";
                    cin.clear();
                }
                else {
                    mins = int(t);
                }
                cin.ignore(1000, '\n');
            } while (mins < 0);
        }
        else {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            mins = lt.tm_hour * 60 + lt.tm_min;
        }
        return mins;
    }

    int getInt(const char* prompt) {

        string int_value;
        unsigned int i = 0;
        bool run = true, bad_int = false, only_int = true;

        if (prompt != nullptr) {
            cout << prompt;
        }

        getline(cin, int_value);

        while (run) {
            bad_int = false;
            only_int = true;

            if (!isdigit(int_value[0]) && int_value[0] != '-') bad_int = true;

            if (bad_int) {
                cout << "Bad integer value, try again: ";
                getline(cin, int_value);
            }

            for (i = 0; i < int_value.length() && bad_int == false; i++) {
                if (isdigit(int_value.c_str()[i]) == false && int_value[i] != '-') {
                    only_int = false;
                    i = int_value.length();
                }
            }

            if (only_int == false && !bad_int) {
                cout << "Enter only an integer, try again: ";
                getline(cin, int_value);
            }

            if (only_int && !bad_int) {
                run = false;
            }
            else {
                cin.clear();
            }
        }

        return stoi(int_value);
    }

    int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError) {

        int int_value = getInt(prompt);
        bool run = true;

        while (run) {
            if (int_value > max || int_value < min) {

                if (errorMessage != nullptr) {
                    cout << errorMessage;
                }

                if (showRangeAtError) {
                    cout << "[" << min << " <= value <= " << max << "]: ";
                }

                int_value = getInt();
            }
            else {
                run = 0;
            }
        }

        return int_value;
    }

    char* getcstr(const char* prompt, std::istream& istr, char delimiter) {

        string char_value;
        char* cstr_value;

        if (prompt != nullptr) {
            cout << prompt;
        }

        getline(istr, char_value, delimiter);
        cstr_value = new char[char_value.length() + 1];
        strcpy(cstr_value, char_value.c_str());

        return cstr_value;
    }
}