#pragma once

class Date
{
public:
	Date() :mmsec(0), year(0), month(0), day(0), dayNumberFromDate(0){}
	Date(unsigned long mmsec);
	Date(unsigned int day, unsigned int month, unsigned int year);

	void PrintMMsecDate();
	void PrintInfoDate();

	bool IsLeapYear();

	void SetDay(unsigned int day);
	void SetMonth(unsigned int month);
	void SetYear(unsigned int year);
	void SetDayNumberFromDate(int dayNumberForDate);
	int GetDay();
	int GetMonth();
	int GetYear();
	int GetDayNumberFromDate();

	bool operator ==(const Date& other);
	bool operator !=(const Date& other);
	bool operator <=(const Date& other);
	bool operator >=(const Date& other);
	bool operator >(const Date& other);
	bool operator <(const Date& other);

	Date operator +(int day);
	Date operator -(const Date& other);
	Date operator -(int day);

protected:
	unsigned long mmsec;
	unsigned int year;
	unsigned int month;
	unsigned int day;
	
	int dayNumberFromDate;
	
	unsigned int * LeapDaysMonth();

	void DayNumberFromDate();
	void ConvertToDate();
};

