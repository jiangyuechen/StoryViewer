#pragma once
#include "basic.h"

#ifndef _OBJECT
#define _OBJECT
#endif

namespace StoryViewer
{
	static void TOSTRING_APPEND(String& _ret, size_t _num, ...)
	{
		va_list _appender;
		va_start(_appender, _num);

		for (size_t _i = 0; _i < _num; ++_i)
		{
			String _nxt_arg = va_arg(_appender, String);
			_ret.append(_nxt_arg);
		}

		va_end(_appender);
	}

	class Object
	{
	public:
		template<typename T>
		static bool _In(std::vector<T>& _tester, T _target)
		{
			for (auto _iter = _tester.begin(); _iter != _tester.end(); ++_iter)
			{
				if ((*_iter) == _target)
					return true;
			}
			return false;
		}
		Object() noexcept {}
		virtual ~Object() {}
		virtual String ToString(DETAIL_TYPE _style = 0) const { return L"<¸ùÀà>"; }
	};
	//template <typename T>
	//class Collection : public std::vector<T>
	//{
	//public:
	//	bool Contains(T _target)
	//	{
	//		for (auto _iter = this->begin(); _iter != this->end(); ++_iter)
	//		{
	//			if ((*_iter) == _target)
	//				return true;
	//		}
	//		return false;
	//	}
	//};
}