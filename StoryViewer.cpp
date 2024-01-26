#include "pch.h"

#ifndef _STORYVIEWER
#define _STORYVIEWER
#endif

#define MAKE_PTR(_Class,_Obj) _Class * _ptr_##_Obj = &_Obj
#define PTR(_Obj) _ptr_##_Obj

#define _Instance_
#define _String_
#define _Safe_Instance_(_Obj) _Obj&&

using namespace StoryViewer;
typedef Link<Character, Character> CharacterLink;

#ifdef __USE_BASIC_WOSTREAM
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
				_wcout << L" , ";
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
	size_t count = _m_char.Count();
	for (size_t _i = 0; _i < count; ++_i)
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
#endif // __USE_BASIC_WOSTREAM

void Initialize()
{
	setlocale(LC_ALL, "");
	std::wcout.imbue(std::locale(""));
	// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
}

int main()
{
	Initialize();

	_Safe_Instance_(Character) Ivy = Character(L"艾薇", nullptr,
		AttributeList{ 
			{ L"性别", L"女"},
			{ L"类型", L"建造者" }
		}
	);

	_Safe_Instance_(Character) Vanessa = Character(L"凡妮莎", nullptr,
		AttributeList{ 
			{ L"性别", L"女" },
			{ L"类型", L"建造者" },
			{ L"瞳孔颜色", L"蓝"}
		}
	);

	MultiCharacter _m_Vanessa = _Instance_ Vanessa;

	_Safe_Instance_(Character) VanessaB = Character(L"凡妮莎-恨意", nullptr,
		new AttributeList{
			{ L"性别", L"女" },
			{ L"类型", L"建造者" },
			{ L"瞳孔颜色", L"红"}
		}
	);

	_m_Vanessa.SetAsSubCharacter(_Instance_ VanessaB);

	_Safe_Instance_(Character) Paff = Character(L"Paff", nullptr,
		new AttributeList{
			{ L"性别",  L"女" },
			{ L"类型", L"人类" },
			{ L"身份", 2 }
		});

	_Safe_Instance_(Character) Aroma = Character(L"Aroma", nullptr,
		new AttributeList {
			{ L"性别", L"女" },
			{ L"类型", L"人类" },
			{ L"身份", L"歌手"}
		}
	);

	MultiCharacter _m_Paff = _Instance_ Paff;
	_m_Paff.SetAsSubCharacter(_Instance_ Aroma);

	Ivy << L"AEsir" << L"IV";

	Vanessa << L"V";

	std::wcout << Vanessa.ToString();
	Link<Character, Character> cl(&Ivy, &Vanessa, L"朋友", UNORDERED);
	std::wcout << cl.ToString();

	Story CYTUSII(L"Cytus II");

	CYTUSII << Ivy << Vanessa << VanessaB << Paff; // 天才！

	std::wcout << CYTUSII.ToString();
	
	CYTUSII.DeleteCharacterByFilter([](Character c) { return c.ContainAKA(L"AEsir"); });

	std::wcout << CYTUSII.ToString();

	DateTime* date = new DTYearMonthDay(2023, 12, 8);

	return 0;
}


int _main()
{
	OPENFILENAME ofn;       // 结构体用于存储文件对话框的信息
	TCHAR szFile[MAX_PATH]; // 存储文件路径的缓冲区

	// 初始化 OPENFILENAME 结构体
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
	ofn.lpstrFilter = L"JPEG Files (*.jpg)\0*.jpg\0All Files (*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrTitle = L"选择一个 JPG 图片";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// 打开文件对话框
	if (GetOpenFileName(&ofn) == TRUE) {
		// 用户选择了一个文件
		std::wcout << L"选择的文件路径: " << ofn.lpstrFile << std::endl;

		// 使用 ShellExecute 打开默认的图片查看器
		HINSTANCE result = ShellExecute(nullptr, L"open", ofn.lpstrFile, nullptr, nullptr, SW_SHOWNORMAL);

		// 检查执行结果
		if ((intptr_t)result > 32) {
			std::wcout << L"成功打开图片!\n";
		}
		else {
			std::wcout << L"无法打开图片。\n";
		}
	}
	else {
		// 用户取消选择文件
		std::wcout << L"用户取消选择文件。\n";
	}

	return 0;
}
