#include "pch.h"

#ifndef _STORYVIEWER
#define _STORYVIEWER
#endif

#define MAKE_PTR(_Class,_Obj) _Class * _ptr_##_Obj = &_Obj
#define PTR(_Obj) _ptr_##_Obj

#define _Instance_
#define _String_

using namespace StoryViewer;
typedef Link<Character, Character> CharacterLink;
std::wostream& operator<<(std::wostream& _wcout, const AttributeList& _attr_list);
std::wostream& operator<<(std::wostream& _wcout, Link<Character, Character>& _link);
std::wostream& operator<<(std::wostream& _wcout, Event& _event);
std::wostream& operator<<(std::wostream& _wcout, Event&& _event);
std::wostream& operator<<(std::wostream& _wcout, Story& _story);
std::wostream& operator<<(std::wostream& _wcout, Story&& _story);
std::wostream& operator<<(std::wostream& _wcout, WeakValueType _wvt);
std::wostream& operator<<(std::wostream& _wcout, AttributeList& _attr_list);
std::wostream& operator<<(std::wostream& _wcout, MultiCharacter& _m_char);

std::wostream& operator<<(std::wostream& _wcout, Character& _char)
{
	_wcout << L"<角色>" << _char.Name() << L"\n";
	if (_char.Aka().size() != 0)
	{
		_wcout << L" ( 又名 ";
		for (size_t _i = 0; _i < _char.Aka().size(); ++_i)
		{
			_wcout << _char.Aka().operator[](_i);
			if (_i != _char.Aka().size() - 1)
			{
				_wcout << " , ";
			}
		}
		_wcout << L" )\n ";
	}
	_wcout << L"---------------- " << _char.Name() << L" 的属性 ----------------\n";
	_wcout << (_char.Attributes());
	return _wcout;
}

std::wostream& operator<<(std::wostream& _wcout, Link<Character, Character>& _link)
{
	if (_link.LinkType() == UNORDERED)
		_wcout << L"<双向关系>";
	else
		_wcout << L"<单向关系>";
	_wcout << L"[" << *(_link.GetFrontPtr()) << (_link.LinkType() == ORDERED ? L"---(" : L"<--(") << _link.Description() << L")-->" << *(_link.GetBackPtr()) << L"]";
	return _wcout;
}
std::wostream& operator<<(std::wostream& _wcout, Event& _event)
{
	_wcout << L"<事件>[" << _event.Name() << L" : " << _event.Description() << L"]";
	return _wcout;
}

std::wostream& operator<<(std::wostream& _wcout, Event&& _event)
{
	_wcout << L"<事件>[" << _event.Name() << L" : " << _event.Description() << L"]";
	return _wcout;
}
std::wostream& operator<<(std::wostream& _wcout, Story& _story)
{
	_wcout << L"<故事>" << _story.StoryName() << L"\n角色:\n";
	for (auto _iter = _story.StoryCharacters().begin(); _iter != _story.StoryCharacters().end(); ++_iter)
	{
		_wcout << L"	" << *(*_iter) << L"\n";
	}
	_wcout << L"\n角色关系:\n";
	for (auto _iter = _story.StoryCharacterLinks().begin(); _iter != _story.StoryCharacterLinks().end(); ++_iter)
	{
		_wcout << L"	" << *(*_iter) << L"\n";
	}
	_wcout << L"\n故事线:\n";
	for (auto _iter = _story.StoryLine().begin(); _iter != _story.StoryLine().end(); ++_iter)
	{
		_wcout << L"	" << *(*_iter) << L"\n";
	}
	return _wcout;
}
std::wostream& operator<<(std::wostream& _wcout, Story&& _story)
{
	_wcout << L"<故事>" << _story.StoryName() << L"\n角色:\n";
	for (auto _iter = _story.StoryCharacters().begin(); _iter != _story.StoryCharacters().end(); ++_iter)
	{
		_wcout << L"	" << *(*_iter) << L"\n";
	}
	_wcout << L"\n角色关系:\n";
	for (auto _iter = _story.StoryCharacterLinks().begin(); _iter != _story.StoryCharacterLinks().end(); ++_iter)
	{
		_wcout << L"	" << *(*_iter) << L"\n";
	}
	_wcout << L"\n故事线:\n";
	for (auto _iter = _story.StoryLine().begin(); _iter != _story.StoryLine().end(); ++_iter)
	{
		_wcout << L"	" << *(*_iter) << L"\n";
	}
	return _wcout;
}

std::wostream& operator<<(std::wostream& _wcout, DTYearMonthDay& _dt)
{
	_wcout << L"<日期>" << _dt.Year() << L"." << _dt.Month() << L"." << _dt.Day();
	return _wcout;
}
std::wostream& operator<<(std::wostream& _wcout, DTYearMonthDay&& _dt)
{
	_wcout << L"<日期>" << _dt.Year() << L"." << _dt.Month() << L"." << _dt.Day();
	return _wcout;
}
#ifdef USE_DISCRETE
std::wostream& operator<<(std::wostream& _wcout, Discrete& _disc)
{
	_wcout << L"<离散值>" << static_cast<String>(_disc);
	return _wcout;
}
#endif

std::wostream& operator<<(std::wostream& _wcout, WeakValueType _wvt)
{
	switch (_wvt.Type())
	{
	case VALUE_TYPE::UNKNOWN:
		_wcout << "<未定义变量>";
		break;
	case VALUE_TYPE::INTEGER:
		_wcout << static_cast<int>(_wvt);
		break;
	case VALUE_TYPE::DOUBLE:
		_wcout << static_cast<double>(_wvt);
		break;
	case VALUE_TYPE::STRING:
		_wcout << static_cast<String>(_wvt);
		break;
	}
	return _wcout;
}
#ifdef USE_DISCRETE
std::wostream& operator<<(std::wostream& _wcout, Discrete&& _disc)
{
	_wcout << L"<离散值>" << static_cast<String>(_disc);
	return _wcout;
}
std::wostream& operator<<(std::wostream& _wcout, const Discrete& _disc)
{
	_wcout << L"<离散值>" << static_cast<String>(_disc);
	return _wcout;
}
#endif
std::wostream& operator<<(std::wostream& _wcout, AttributeList& _attr_list)
{
	_wcout << std::left << std::setw(8) << L"键" << std::right << std::setw(8) << L"值\n";
	_wcout << L"--------------------------------\n";
	for (const auto& _iter : _attr_list)
	{
		_wcout << L"|" << std::left << std::setw(8) << _iter.first << std::right << std::setw(8) << _iter.second << L"|\n";
	}
	return _wcout;
}
std::wostream& operator<<(std::wostream& _wcout, MultiCharacter& _m_char)
{
	_wcout << L"<多元角色>" << _m_char.Name() << L"\n";
	int count = _m_char.Count();
	for (int _i = 0; _i < count; ++_i)
	{
		_wcout << L"---------------------------------------------\n";
		_wcout << L"|           第 " << _i + 1 << L" 个定义（共" << count << L"个）            |\n";
		_wcout << L"---------------------------------------------\n";
		auto _temp = _m_char[_i].Val();
		_wcout << _temp;
		_wcout << L"\n";
	}
	return _wcout;
}

void Initialize()
{
	setlocale(LC_ALL, "");
	std::wcout.imbue(std::locale(""));
	// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
}

int main()
{
	Initialize();
	//Discrete Gender({ L"男", L"女" });
	
	Character Ivy = Character(L"艾薇", nullptr,
		AttributeList{
			{ L"性别", L"女"},
			{ L"类型", L"建造者" }
		}
	);
	Character Vanessa = Character(L"凡妮莎", nullptr,
		AttributeList{
			{ L"性别", L"女" },
			{ L"类型", L"建造者" },
			{ L"瞳孔颜色", L"蓝"}
		}
	);
	MultiCharacter _m_Vanessa = _Instance_ Vanessa;

	//Character VanessaB = Character(L"凡妮莎-恨意", nullptr,
	//	new AttributeList{
	//		{ L"性别", L"女" },
	//		{ L"类型", L"建造者" },
	//		{ L"瞳孔颜色", L"红"}
	//	}
	//);

	Character VanessaB = Character(L"凡妮莎-恨意");
	_m_Vanessa.SetAsSubCharacter(_Instance_ VanessaB);
	// VanessaB >> Vanessa;
	Character Paff(L"Paff", nullptr,
		new AttributeList{
			{ L"性别",  L"女" },
			{ L"类型", L"人类" },
			{ L"身份", 2 }
		}), * _ptr_Paff = &Paff;
	//Character Aroma = Character(L"Aroma", nullptr,
	//	new AttributeList {
	//		{ L"性别", L"女" },
	//		{ L"类型", L"人类" },
	//		{ L"身份", L"歌手"}
	//	}
	//);
	Ivy << L"AEsir" << L"IV";

	Vanessa << L"V";

	Vanessa[L"实际身份"] = L"我女朋友";

	std::wcout << _m_Vanessa;

	std::wcout << Ivy;

	std::wcout << Paff;

	// auto u = Aroma[L"前世"] >> Paff;

	Story CYTUSII(L"Cytus II");

	CYTUSII << Ivy << Vanessa << VanessaB << Paff; // 天才！
	// CYTUSII << u << x << fr;

	Story HONKAI_IMPACT_3 = Story(L"崩坏3");

	Character Bronya = Character(L"布洛妮娅");
	// SubCharacter Silverwing_Ex = SubCharacter(L"次生银翼", &Bronya, false);
	
	// std::wcout << HONKAI_IMPACT_3;
	// understand?

	//WeakValueType w = 1;
	//std::wcout << static_cast<int>(w);
	//std::wcout << int(w);
	//w = 1.2f;
	//std::wcout << static_cast<double>(w);
	//w = L"Fuck you";
	//std::wcout << static_cast<String>(w);
	//Discrete gender = std::vector<String> { L"Male", L"Female" };
	//gender = L"Male";

	//w = gender;
	//std::wcout << w;

	//std::wcout << CYTUSII << std::endl;

	// SwapPtr<Character>(&Ivy, &Vanessa);

	/*std::wcout << L"交换后：" << std::endl;*/

	//std::wcout << CYTUSII << std::endl;

	//Story Xianghuo = Story(L"香火");

	//Character Suge = Character(L"苏格");

	//Character Wuma = Character(L"吴妈");

	//Character Nvzi = Character(L"陌生女子");

	//Character Airen = Character(L"苏格的爱人");

	//Character& Zhoujing = Airen;
	//Zhoujing << L"周静";
	//
	//Event e = Event(L"苏格被查出少精症.");

	//Character Shiyantian = Character(L"试验田");

	//CharacterLink x = Airen[L"妻子"] >> Suge;

	//Xianghuo << x;

	//Nvzi &= Airen;

	//std::wcout << Airen;

	DTYearMonthDay date = DTYearMonthDay(2023, 12, 8);

	return 0;
}