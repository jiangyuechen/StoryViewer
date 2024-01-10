#pragma once
#include "basic.h"
#include "Object.h"
#include "Link.h"

#ifndef _LINK
#define _LINK
#endif

namespace StoryViewer
{
	enum LINKTYPE
	{
		ORDERED = 0,
		UNORDERED
	};

	template<typename T, typename U>
	class Link : public Object
	{
	protected:
		T* p_front;
		U* p_back;
		String description;
		LINKTYPE link_type;
	public:

		Link() : Object()
		{
			p_front = p_back = nullptr;
			description = L"<NO-DESCRIPTION>";
			link_type = LINKTYPE::ORDERED;
		}
		Link(T* _p_front, U* _p_back, const String& _desc = L"<NO-DESCRIPTION>", LINKTYPE _link_type = ORDERED) : Object()
		{
			p_front = _p_front;
			p_back = _p_back;
			description = _desc;
			link_type = _link_type;
		}
		~Link() { p_front = p_back = nullptr; }

		String& Description()
		{
			return description;
		}
		LINKTYPE& LinkType()
		{
			return link_type;
		}

		void AlterFront(T* _p_new_front)
		{
			p_front = _p_new_front;
		}
		void AlterBack(U* _p_new_back)
		{
			p_back = _p_new_back;
		}
		T* GetFrontPtr()
		{
			return p_front;
		}
		U* GetBackPtr()
		{
			return p_back;
		}
		T GetFront()
		{
			return *p_front;
		}
		U GetBack()
		{
			return *p_back;
		}
	};
}
