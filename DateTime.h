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
		BEFORE_DAWN = 0, // 凌晨
		EARLY_MORNING, // 清晨
		MORNING, // 上午
		NOON, // 中午
		AFTERNOON, // 下午
		EVENING, // 傍晚
		NIGHT, // 夜晚
		LATE_NIGHT // 深夜
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
		EARLY_PERIOD, // 上旬
		MID_PERIOD, // 中旬
		LATE_PERIOD // 下旬
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