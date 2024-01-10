#include "DateTime.h"
#define MAX(a, b) ((a) > (b) ? (a) : (b))

using namespace StoryViewer;

const int day_count_of_month_even[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int day_count_of_month_odd[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int DateTime::last_year = MINIMUM_DATETIME;
int DateTime::last_month = MINIMUM_DATETIME;
int DateTime::last_day = MINIMUM_DATETIME;
int DateTime::last_hour = MINIMUM_DATETIME;
int DateTime::last_minute = MINIMUM_DATETIME;
int DateTime::last_second = MINIMUM_DATETIME;
bool DateTime::use_typical_calendar = true;

DAY_PERIOD DateTime::last_day_period = DAY_PERIOD::BEFORE_DAWN;

bool DTYearMonthDay::operator<(const DTYearMonthDay& _dt)
{
	if (this->year == _dt.year)
	{
		if (this->month == _dt.month)
		{
			if (this->day == _dt.day)
			{
				return this->day_period < _dt.day_period;
			}
			else
				return this->day < _dt.day;
		}
		else
			return this->month < _dt.month;
	}
	else
		return this->year < _dt.year;
}

int& DTYearMonthDay::Year()
{
	return this->year;
}
int& DTYearMonthDay::Month()
{
	return this->month;
}
int& DTYearMonthDay::Day()
{
	return this->day;
}
DAY_PERIOD& DTYearMonthDay::DayPeriod()
{
	return this->day_period;
}

bool DTYearMonthDay::operator==(const DTYearMonthDay& _dt)
{
	return this->year == _dt.year
		&& this->month == _dt.month
		&& this->day == _dt.day
		&& this->day_period == _dt.day_period;
}

bool DTYearMonthDay::operator<=(const DTYearMonthDay& _dt)
{
	return (*this) < _dt || (*this) == _dt;
}


DTYearMonthDay::DTYearMonthDay()
{
	year = DateTime::last_year;
	month = DateTime::last_month;
	day = DateTime::last_month;
	day_period = DateTime::last_day_period;
	this->Refresh();
}

bool DTYearMonthDay::operator>(const DTYearMonthDay& _dt)
{
	return !((*this) <= _dt);
}

DTYearMonthDay::DTYearMonthDay(int _year, int _month, int _day, DAY_PERIOD _day_period, bool _use_typical_calendar)
{
	year = _year;
	month = _month;
	day = _day;
	day_period = _day_period;
	DateTime::use_typical_calendar = _use_typical_calendar;
	this->Refresh();
}

bool DTYearMonthDay::operator>=(const DTYearMonthDay& _dt)
{
	return !((*this) < _dt);
}

bool DTYearMonthDay::operator!=(const DTYearMonthDay& _dt)
{
	return !((*this) == _dt);
}


void DTYearMonthDay::Refresh()
{
	DateTime::last_year = MAX(DateTime::last_year, year);
	DateTime::last_month = MAX(DateTime::last_month, month);
	DateTime::last_day = MAX(DateTime::last_day, day);
	DateTime::last_day_period = MAX(DateTime::last_day_period, day_period);
}

DTYearMonthDay DTYearMonthDay::NextDay(int _multiple)
{
	DTYearMonthDay _ret = (*this);
	for (int _i = 0; _i < _multiple; ++_i)
	{
		++_ret.Day();
		if (
			(IsOddYear(_ret.Year())
			&& day_count_of_month_odd[_ret.Month()] < _ret.Day())
			||
			((!IsOddYear(_ret.Year()))
			&& 
			day_count_of_month_even[_ret.Month()] < _ret.Day())
		)
		{
			++_ret.Month();
			_ret.Day() = 1;
			if (_ret.Month() > 12)
			{
				_ret.Month() = 1;
				++_ret.Year();
			}
		}
	}
	return _ret;
}


DTYearMonthDay DTYearMonthDay::PrevDay(int _multiple)
{
	DTYearMonthDay _ret = (*this);
	for (int _i = 0; _i < _multiple; ++_i)
	{
		--_ret.Day();
		if (_ret.Day() <= 0)
		{
			--_ret.Month();
			if (_ret.Month() < 0)
			{
				--_ret.Year();
				_ret.Month() = 12;
			}
			_ret.Day() =
				IsOddYear(_ret.Year()) ?
				day_count_of_month_odd[_ret.Month()] :
				day_count_of_month_even[_ret.Month()];
		}
	}
	return _ret;
}

bool DateTime::IsOddYear(int _year)
{
	if (_year % 100 == 0)
		return (_year % 400 == 0);
	else
		return (_year % 4 == 0);
}

void DateTime::Refresh()
{

}