#pragma once
#include "basic.h"
#include "Object.h"
#include "ValueType.h"
#include "Event.h"

namespace StoryViewer
{
	typedef std::vector<Event*> EventLine;

	class LifeCycle : public Object
	{
	protected:
		EventLine ev;
	public:
		LifeCycle();
	};
}