#pragma once
#include "basic.h"
#include "Object.h"

#ifndef _DATETIME
#define _DATETIME
#endif

#define MINIMUM_DATETIME -2147483648;

namespace StoryViewer
{
	enum DAY_PERIOD
	{
		BEFORE_DAWN = 0, // �賿
		EARLY_MORNING, // �峿
		MORNING, // ����
		NOON, // ����
		AFTERNOON, // ����
		EVENING, // ����
		NIGHT, // ҹ��
		LATE_NIGHT // ��ҹ
	};
	enum WeekPeriod
	{
		MONDAY = 1,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY,
		SUNDAY
	};
	enum MonthPeriod
	{
		EARLY_PERIOD, // ��Ѯ
		MID_PERIOD, // ��Ѯ
		LATE_PERIOD // ��Ѯ
	};
	class DateTime : public Object // abstract
	{
	public:
		static bool IsOddYear(time_t _year);

		static time_t last_year, last_month, last_day, last_hour, last_minute, last_second;
		
		static DAY_PERIOD last_day_period;
		static bool use_typical_calendar;
		virtual void Refresh() /* = 0 */;
		
		virtual String ToString(bool _detailed = true) const override;
	};
	
	class DTYearMonthDay : public DateTime
	{
	private:
		// DayPeriod DayPeriodConverter(int _num);
		time_t year, month, day;
		DAY_PERIOD day_period;
	public:
		time_t& Year() _MUTABLE;
		time_t& Month() _MUTABLE;
		time_t& Day() _MUTABLE;
		DAY_PERIOD& DayPeriod() _MUTABLE;
		DTYearMonthDay();
		DTYearMonthDay(time_t _year, time_t _month, time_t _day, DAY_PERIOD _day_period = BEFORE_DAWN, bool _use_typical_calendar = true);
		virtual void Refresh(); // override
		bool operator<(const DTYearMonthDay& _dt) const;
		bool operator==(const DTYearMonthDay& _dt) const;
		bool operator<=(const DTYearMonthDay& _dt) const;
		bool operator>(const DTYearMonthDay& _dt) const;
		bool operator>=(const DTYearMonthDay& _dt) const;
		bool operator!=(const DTYearMonthDay& _dt) const;
		DTYearMonthDay NextDay(size_t _multiple = 1);
		DTYearMonthDay PrevDay(size_t _multiple = 1);

		virtual String ToString(bool _detailed = true) const override;
	};
}