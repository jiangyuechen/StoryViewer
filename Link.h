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

	// Link <Object> OK!
	// Link <Object*> NO!
	// Link <Object&> NO!
	
	template<typename T, typename U> // Type T and U must contain the method ToString().
	class Link : public Object
	{
		static_assert(std::is_base_of<Object, T>::value, "T must be a derived class of BaseClass");
	
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

		String& Description() _MUTABLE
		{
			return description;
		}
		LINKTYPE& LinkType() _MUTABLE
		{
			return link_type;
		}

		void AlterFront(T* _p_new_front) _MUTABLE
		{
			p_front = _p_new_front;
		}
		void AlterBack(U* _p_new_back) _MUTABLE
		{
			p_back = _p_new_back;
		}
		T* GetFrontPtr() _CONST
		{
			return p_front;
		}
		U* GetBackPtr() _CONST
		{
			return p_back;
		}
		T GetFront() _CONST
		{
			return *p_front;
		}
		U GetBack() _CONST
		{
			return *p_back;
		}
		T& GetFrontRef() _MUTABLE
		{
			return *p_front;
		}
		U& GetBackRef() _MUTABLE
		{
			return *p_back;
		}
		T*& GetFrontPtrRef() _MUTABLE
		{
			return p_front;
		}
		U*& GetBackPtrRef() _MUTABLE
		{
			return p_back;
		}
		virtual String ToString() _CONST override
		{
			String _ret{};
			if (this->link_type == UNORDERED)
				_ret += L"<关系(双向)>";
			else
				_ret += L"<关系(单向)>";
			_ret += L"[";
			_ret += this->GetFront().ToString();
			_ret += link_type == ORDERED ? L"---(" : L"<--(";
			_ret += this->description;
			_ret += L")-->";
			_ret += this->GetBack().ToString();
			_ret += L"]";
			return _ret;
		}
	};
}
