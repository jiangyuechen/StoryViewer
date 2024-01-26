#pragma once
#include "basic.h"
#include "Event.h"
#include "Character.h"
#include "Link.h"
#include "Story.h"
#include "ValueType.h"

namespace StoryViewer
{
	//template<typename OutputteeType, typename OutputterType = std::wostream>
	//class View
	//{
	//public:
	//	static OutputterType& Outputter = std::wcout;
	//	static void SetOutputter(OutputterType& _outputter)
	//	{
	//		_wcout = _outputter;
	//	}
	//	static void (*EventOutput)(OutputterType& _wcout, Event& _ev)
	//		= [&](OutputterType& _wcout, Event& _ev)
	//		{
	//			_wcout << L"<事件>[" << _event.Name() << L" : " << _event.Description() << L"]";
	//		};
	//	static void (*CharacterOutput)(OutputterType& _wcout, Character& _ch)
	//		= [&](OutputterType& _wcout, Character& _ch)
	//		{
	//			_wcout << L"<角色>" << _char.Name() << L"\n";
	//			if (_char.Aka().size() != 0)
	//			{
	//				_wcout << L" ( 又名 ";
	//				for (size_t _i = 0; _i < _char.Aka().size(); ++_i)
	//				{
	//					_wcout << _char.Aka().operator[](_i);
	//					if (_i != _char.Aka().size() - 1)
	//					{
	//						_wcout << " , ";
	//					}
	//				}
	//				_wcout << L" )\n ";
	//			}
	//			_wcout << L"---------------- " << _char.Name() << L" 的属性 ----------------\n";
	//			_wcout << (_char.Attributes());
	//		};
	//	template <typename T, typename U>
	//	static void (*LinkOutput)(OutputterType& _wcout, Link<T, U>& _li)
	//		= [&](OutputterType& _wcout, Link<T, U>& _li)
	//		{
	//			if (_link.LinkType() == UNORDERED)
	//				_wcout << L"<双向关系>";
	//			else
	//				_wcout << L"<单向关系>";
	//			_wcout << L"[" << *(_link.GetFrontPtr()) << (_link.LinkType() == ORDERED ? L"---(" : L"<--(") << _link.Description() << L")-->" << *(_link.GetBackPtr()) << L"]";
	//		};
	//	static void (*StoryOutput)(OutputterType& _wcout, Story& _st)
	//		= [&](OutputterType& _wcout, Story& _st)
	//		{
	//			_wcout << L"<故事>" << _story.StoryName() << L"\n角色:\n";
	//			for (auto _iter = _story.StoryCharacters().begin(); _iter != _story.StoryCharacters().end(); ++_iter)
	//			{
	//				_wcout << L"	" << *(*_iter) << L"\n";
	//			}
	//			_wcout << L"\n角色关系:\n";
	//			for (auto _iter = _story.StoryCharacterLinks().begin(); _iter != _story.StoryCharacterLinks().end(); ++_iter)
	//			{
	//				_wcout << L"	" << *(*_iter) << L"\n";
	//			}
	//			_wcout << L"\n故事线:\n";
	//			for (auto _iter = _story.StoryLine().begin(); _iter != _story.StoryLine().end(); ++_iter)
	//			{
	//				_wcout << L"	" << *(*_iter) << L"\n";
	//			}
	//		};

	//	friend static void Embody(OutputteeType& _tar)
	//	{
	//		switch (typeid(_tar)) {
	//			
	//		}
	//	}

	//};
}