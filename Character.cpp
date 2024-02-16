#include "basic.h"
#include "Character.h"
#include "Link.h"
#include "Story.h"
#include "ValueType.h"

using namespace StoryViewer;

Character::Character()
{
	name = L"<NO-NAME>";
	aka = StringList();
	attributes = AttributeList();
	// sub_characters = std::vector<SubCharacter*>();
}

Character::Character(const String& _name,
	Nullable<StringList> _p_aka,
	Nullable<AttributeList> _p_attributes)
{
	name = _name;
	aka = !_p_aka.IsNull() ? _p_aka.Val() : StringList();
	attributes = !_p_attributes.IsNull() ? _p_attributes.Val() : AttributeList();
}

Character::~Character()
{}

String& Character::Name()
{
	return name;
}

StringList& Character::Aka()
{
	return aka;
}

AttributeList& Character::Attributes()
{
	return attributes;
}


bool Character::ContainKey(const String& _key) const
{
	for (const auto& _iter : attributes)
	{
		if (_iter.first == _key)
			return true;
	}
	return false;
}

String Character::ToString(int _style) const
{
	String _ret{};
	_ret += L"<角色>";
	_ret += this->name;
	if (!_style)
		return _ret;
	if (this->aka.size() != 0)
	{
		_ret += L" ( 又名 ";
		for (size_t _i = 0; _i < this->aka.size(); ++_i)
		{
			_ret += this->aka[_i];
			if (_i != this->aka.size() - 1)
			{
				_ret += L" , ";
			}
		}
		_ret += L" )\n";
	}
	_ret += L"---------------- ";
	_ret += this->name;
	_ret += L" 的属性 ----------------\n";
	size_t _max_key_length = 0;
	const size_t _buffer = 8;
	for (const auto& _iter : this->attributes)
	{
		_max_key_length = MAX(_max_key_length, _iter.first.length());
	}
	_ret += L"键";
	_ret += String(_max_key_length + _buffer, L' ');
	_ret += L"值\n";
	_ret += L"-----------------------------------------\n";
	for (const auto& _iter : this->attributes)
	{
		_ret += _iter.first;
		_ret += String(_max_key_length + _buffer - _iter.first.length(), L' ');
		_ret += _iter.second.ToString();
		_ret += L"\n";
	}
	return _ret;
}

bool Character::ContainKeyValue(const Attribute& _attrib) const
{
	if (attributes.empty())
		return false;
	for (const auto& _iter : attributes)
	{
		WeakValueType _x = _iter.second;
		WeakValueType _y = _attrib.second;
		if (_iter.first == _attrib.first && _x == _y)
			return true;
	}
	return false;
}

void Character::AddAttribute(const Attribute& _p_attrib)
{
	if (!ContainKey(_p_attrib.first))
	{
		attributes.push_back(_p_attrib);
	}
	else
	{
		AlterAttribute(_p_attrib);
	}
}

bool Character::RemoveAttribute(const String& _key)
{
	if (attributes.empty())
		return false;
	for (auto _iter = attributes.begin(); _iter != attributes.end(); ++_iter)
	{
		if (_iter->first == _key)
		{
			attributes.erase(_iter);
			return true;
		}
	}
	return false;
}


Nullable<Attribute> Character::FindAttribute(const String& _key) const
{
	if (attributes.empty())
		return Nullable<Attribute>();
	for (const auto& _iter : attributes)
	{
		if (_iter.first == _key)
			return Nullable<Attribute>(make_pair(_iter.first, _iter.second));
	}
	return Nullable<Attribute>();
}

Nullable<WeakValueType> Character::GetValue(const String& _key) const
{
	Nullable<Attribute> _ret = FindAttribute(_key);
	if (!(_ret.IsNull()))
		return Nullable<WeakValueType>(_ret.Val().second);
	return Nullable<WeakValueType>();
}

bool Character::AlterAttribute(const Attribute& _attrib)
{
	if (RemoveAttribute(_attrib.first) == true)
	{
		AddAttribute(_attrib);
		return true;
	}
	else
	{
		return false;
	}
}

void Character::ClearAttribute()
{
	this->attributes.clear();
}

bool Character::AddAKA(const String& _aka)
{
	if (!ContainAKA(_aka))
	{
		aka.push_back(_aka);
		return true;
	}
	else
		return false;
}

bool Character::ContainAKA(const String& _aka) const
{
	for (const auto& _iter : aka)
	{
		if (_iter == _aka)
			return true;
	}
	return false;
}

#ifdef _USE_CHARACTER_LINKER_OPERATOR
CharacterLinker Character::operator[](const String& _desc)
{
	return CharacterLinker(this, _desc);
}
#endif

void Character::operator>>(Story& _tar_story)
{
	_tar_story.AddCharacter(this);
}

Character& Character::operator<<(const String& _new_aka)
{
	aka.push_back(_new_aka);
	return *this;
}

Character& Character::operator<<(const Attribute& _new_attr)
{
	AddAttribute(_new_attr);
	return *this;
}
CharacterAttributeAdder Character::operator[](const String& _new_key)
{
	return CharacterAttributeAdder(this, _new_key);
}

#ifdef _USE_CHARACTER_LINKER_OPERATOR
CharacterLinker::CharacterLinker() : Object()
{
	this->main = nullptr;
	this->description = L"NO-DESCRIPTION";
}

CharacterLinker::CharacterLinker(Character* _main, const String& _desc) : Object()
{
	this->main = _main;
	this->description = _desc;
}

CharacterLinker::~CharacterLinker()
{
	this->main = nullptr;
}

BasicLink<Character, Character> CharacterLinker::_MakeLink(Character& _sub, LINKTYPE _type) const
{
	return BasicLink<Character, Character>(&_sub, this->main, this->description, _type);
}
BasicLink<Character, Character> CharacterLinker::operator>>(Character& _main) const
{
	return _MakeLink(_main, ORDERED);
}

BasicLink<Character, Character> StoryViewer::CharacterLinker::operator>(Character& _main) const
{
	return _MakeLink(_main, UNORDERED);
}
#endif

CharacterAttributeAdder::CharacterAttributeAdder(Character* _tar_char, const String& _key) : Object()
{
	tar_char = _tar_char;
	key = _key;
}

void CharacterAttributeAdder::operator=(WeakValueType val)
{
	tar_char->AddAttribute(Attribute(this->key,val));
}

MultiCharacter::MultiCharacter() : Character() {}
MultiCharacter::MultiCharacter(
	const String& _name,
	Nullable<StringList> _p_aka,
	Nullable<AttributeList> _p_attributes,
	Nullable<CharacterCollection> _p_sub_characters)
	: Character(_name, _p_aka, _p_attributes)
{
	sub_characters = !_p_sub_characters.IsNull() ? _p_sub_characters.Val() : CharacterCollection();
}

MultiCharacter::MultiCharacter(const Character& _base_char) : Character(_base_char)
{
	sub_characters = CharacterCollection();
}

MultiCharacter::~MultiCharacter()
{}

void MultiCharacter::SetAsSubCharacter(Character& _tar_char)
{
	sub_characters.push_back(&_tar_char);
}

CharacterCollection& MultiCharacter::SubCharacters()
{
	return this->sub_characters;
}

Nullable<Character> MultiCharacter::Getter(size_t _code) const
{
	if (_code == 0)
		return (*this);
	else if (_code > 0 && _code <= sub_characters.size())
		return sub_characters[_code - 1];
	else return nullptr;
}

Nullable<Character> MultiCharacter::operator[](size_t _code) const
{
	return Getter(_code);
}

size_t MultiCharacter::Count() const
{
	return sub_characters.size() + 1;
}

void MultiCharacter::operator+=(Character& _tar_char)
{
	this->SetAsSubCharacter(_tar_char);
}

String MultiCharacter::ToString(int _style) const
{
	String _ret{};
	_ret += L"<多元角色>";
	_ret += this->name;
	_ret += L"\n";
	for (size_t _i = 0; _i < this->Count(); ++_i)
	{
		_ret += L"---------------------------------------------\n";
		_ret += L"|           第 ";
		_ret += std::to_wstring(_i + 1);
		_ret += L" 个定义（共";
		_ret += std::to_wstring(this->Count());
		_ret += L"个)";
		_ret += (*this)[_i].Val().ToString();
		_ret += L"\n";
	}
	return _ret;
}

String CharacterAttributeAdder::ToString(int _style) const
{
	String _ret{};
	_ret += L"<角色属性添加器>\n";
	_ret += L"目标角色:";
	_ret += this->tar_char->Name();
	_ret += L"\n目标属性:";
	_ret += this->key;
	return _ret;
}