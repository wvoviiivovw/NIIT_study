#include "Date.h"
#include <iostream>

Date::Date(unsigned long mmsec) :day(0), month(0), year(0), dayNumberFromDate(0)
{
	this->mmsec = mmsec;
}

Date::Date(unsigned int day, unsigned int month, unsigned int year) : mmsec(0)
{
	if (year > 0 && year < 9999)
	{
		this->year = year;
	}
	else
	{
		this->year = 1;
	}
	if (month > 0 && month <= 12)
	{
		this->month = month;
	}
	else
	{
		this->month = 1;
	}
	unsigned int* tempData = LeapDaysMonth();
	if (day > 0 && day <= tempData[month-1])
	{
		this->day = day;
	}
	else
	{
		this->day = 1;
	}
	this->DayNumberFromDate();
}

void Date::PrintMMsecDate()
{
	std::cout << mmsec << std::endl;
}

void Date::PrintInfoDate()
{
	std::cout << "**********************" << std::endl;
	if (day == 0 && month == 0 && year == 0)
	{
		if (dayNumberFromDate > 0)
			std::cout << "variable storage day = " << dayNumberFromDate << std::endl;
		else 
			std::cout << "not date"<< std::endl;
	}
	else
	{
		std::cout << "day : " << day << std::endl;
		std::cout << "month : " << month << std::endl;
		std::cout << "year : " << year << std::endl;
		if (IsLeapYear())
			std::cout << "leap yaer - YES" << std::endl;
		else
			std::cout << "leap yaer - NO" << std::endl;
	}
		
	std::cout << "**********************" << std::endl;

	/*std::cout << dayNumberFromDate << std::endl;
	ConvertToDate();
	std::cout << "day : " << day << std::endl;
	std::cout << "month : " << month << std::endl;
	std::cout << "year : " << year << std::endl;*/
}

bool Date::IsLeapYear()
{
	return year % 4 == 0 ? true : false;
}

void Date::SetDay(unsigned int day)
{
	this->day = day;
}

void Date::SetMonth(unsigned int month)
{
	this->month = month;
}

void Date::SetYear(unsigned int year)
{
	this->year = year;
}

void Date::SetDayNumberFromDate(int dayNumberForDate)
{
	this->dayNumberFromDate = dayNumberForDate;
}

int Date::GetDay()
{
	return this->day;
}

int Date::GetMonth()
{
	return this->month;
}

int Date::GetYear()
{
	return this->year;
}

int Date::GetDayNumberFromDate()
{
	return this->dayNumberFromDate;
}

bool Date::operator==(const Date& other)
{
	return this->day == other.day && this->month == other.month && this->year == other.year ? true : false;
}

bool Date::operator!=(const Date& other)
{
	return this->day != other.day && this->month != other.month && this->year != other.year ? true : false;
}

bool Date::operator<=(const Date& other)
{
	return this->dayNumberFromDate <= other.dayNumberFromDate ? true : false;
}

bool Date::operator>=(const Date& other)
{
	return this->dayNumberFromDate >= other.dayNumberFromDate ? true : false;
}

bool Date::operator>(const Date& other)
{
	return this->dayNumberFromDate > other.dayNumberFromDate ? true : false;
}

bool Date::operator<(const Date& other)
{
	return this->dayNumberFromDate < other.dayNumberFromDate ? true : false;
}

Date Date::operator+(int day)
{
	Date temp;
	int d = this->day;			//3
	int m = this->month - 1;	//4(5)
	int y = this->year;			//2020
	const int VARYEAR = 11;
	unsigned int* arrMonth = this->LeapDaysMonth();
	for (int i = 0; i < day; ++i)
	{
		++d;
		if (d == arrMonth[m])
		{
			if (m == VARYEAR)
			{
				++y;
				arrMonth = this->LeapDaysMonth();
				d = 1;
				m = 0;
			}
			else
			{
				++m;
				arrMonth = this->LeapDaysMonth();
				d = 1;
			}
		}

	}
	temp.day = d;
	temp.month = m + 1;
	temp.year = y;
	return temp;
}

Date Date::operator-(const Date& other)
{
	Date temp;
	int t1 = this-> dayNumberFromDate;
	int t2 = other.dayNumberFromDate;
	temp.dayNumberFromDate = t1 - t2;
	return temp;
}

Date Date::operator-(int day)
{
	Date temp;
	int d = this->day; 
	int m = this->month - 1; 
	int y = this->year;
	const int VARYEAR = 11;
	unsigned int* arrMonth = this->LeapDaysMonth();
	for (int i = 0; i < day; ++i)
	{
		--d;
		if (d == 0)
		{
			if (m == 0)
			{
				--y;
				arrMonth = this->LeapDaysMonth();
				d = arrMonth[VARYEAR];
				m = 11;
			}
			else
			{
				--m;
				arrMonth = this->LeapDaysMonth();
				d = arrMonth[m];
			}
		}
		
	}
	temp.day = d;
	temp.month = m+1;
	temp.year = y;
	return temp;
}

unsigned int * Date::LeapDaysMonth()
{
	if (IsLeapYear())
	{
		unsigned int temp[12] = { 30,29,31,30,31,30,31,31,30,31,30,31 };
		return temp;
	}
	else
	{
		unsigned int temp[12] = { 30,28,31,30,31,30,31,31,30,31,30,31 };
		return temp;
	}
}

void Date::DayNumberFromDate()
{
	int d = static_cast<int>(this->day);
	int m = static_cast<int>((this->month + 9) % 12);
	int y = static_cast<int>(this->year - m / 10);
	dayNumberFromDate = 365 * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + (d - 1);
}

void Date::ConvertToDate()
{
	int y = (10000 * dayNumberFromDate + 14780) / 3652425;
	int ddd = dayNumberFromDate - (365 * y + y / 4 - y / 100 + y / 400);
	if (ddd < 0)
	{
		y--;
		ddd = dayNumberFromDate - (365 * y + y / 4 - y / 100 + y / 400);
	}
	int mi = (100 * ddd + 52) / 3060;
	int mm = (mi + 2) % 12 + 1;
	y = y + (mi + 2) / 12;
	int dd = ddd - (mi * 306 + 5) / 10 + 1;
	this->year = y;
	this->month = mm;
	this->day = dd;
}
