#pragma once
#include "basic.h"

#ifndef _OBJECT
#define _OBJECT
#endif

namespace StoryViewer
{
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
		Object() {}
		virtual ~Object() {}
	};
}