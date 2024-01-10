#pragma once
#include "basic.h"
#include "Object.h"

namespace StoryViewer
{
	class Issue : public Object
	{
	protected:
		String description;
		Object* bind_object;
	public:
		Issue();
		Issue(const String& _desc);
		~Issue();

		String& Description();
	};
}