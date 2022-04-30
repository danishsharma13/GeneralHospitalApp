/* Citation and Sources...
Final Project Milestone 5
Module: Time
Filename: Time.cpp
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
#include "Time.h"
#include "utils.h"
#include <string>
using namespace std;
namespace sdds {
	Time& Time::setToNow() {
		m_min = getTime();
		return *this;
	}
	Time::Time(unsigned int min) {
		m_min = min;
	}

	ostream& Time::write(ostream& ostr)const {
		unsigned int hours = 0, mins = 0;
		if (m_min >= 60) {
			hours = m_min / 60;
			mins = m_min % 60;
		}
		else if (m_min >= 0 && m_min < 60) {
			mins = m_min;
		}
		ostr.fill('0');
		ostr.width(2);
		ostr << hours << ":";
		ostr.width(2);
		ostr << mins;
		return ostr;
	}

	istream& Time::read(istream& istr) {
		//change this to only take exact input and colon stuff from input
		int hours, mins;
		char colon;

		istr >> hours;
		istr >> colon;
		istr >> mins;
		// cause a failbit if any above values are 
		// not the same type as reqired as well as colon needs to be ':'
		if (istr.fail() || colon != ':') {
			istr.setstate(ios::failbit);
		}
		else {
			m_min = (hours * 60) + mins;
		}

		return istr;
	}

	Time& Time::operator-=(const Time& D) {
		if (m_min >= D.m_min) {
			m_min -= D.m_min;
		}
		else {
			do {
				m_min += 1440; // 24 * 60
			} while (m_min <= D.m_min);
			m_min -= D.m_min;
		}
		return *this;
	}

	Time Time::operator-(const Time& D)const {
		Time sub_time(m_min);
		sub_time -= D;
		return sub_time;
	}

	Time& Time::operator+=(const Time& D) {
		m_min += D.m_min;
		return *this;
	}

	Time Time::operator+(const Time& D)const {
		Time add_time;
		add_time.m_min = this->m_min + D.m_min;
		return add_time;
	}

	Time& Time::operator=(unsigned int val) {
		m_min = val;
		return *this;
	}

	Time& Time::operator*=(unsigned int val) {
		m_min = m_min * val;
		return *this;
	}

	Time Time::operator*(unsigned int val)const {
		Time multi_time;
		multi_time.m_min = this->m_min * val;
		return multi_time;
	}

	Time& Time::operator/=(unsigned int val) {
		m_min = m_min / val;
		return *this;
	}

	Time Time::operator/(unsigned int val)const {
		Time divide_time;
		divide_time.m_min = m_min / val;
		return divide_time;
	}

	Time::operator int()const {
		return int(this->m_min);
	}

	Time::operator unsigned int()const {
		return this->m_min;
	}

	ostream& operator<<(ostream& ostr, const Time& D) {
		D.write(ostr);
		return ostr;
	}

	istream& operator>>(istream& istr, Time& D) {
		D.read(istr);
		return istr;
	}
}