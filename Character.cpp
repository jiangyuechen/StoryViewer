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

bool Character::ContainAKA(const String& _aka)
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

Link<Character, Character> CharacterLinker::_MakeLink(Character& _sub, LINKTYPE _type) const
{
	return Link<Character, Character>(&_sub, this->main, this->description, _type);
}
Link<Character, Character> CharacterLinker::operator>>(Character& _main) const
{
	return _MakeLink(_main, ORDERED);
}

Link<Character, Character> StoryViewer::CharacterLinker::operator>(Character& _main) const
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

Nullable<Character> MultiCharacter::Getter(int _code) const
{
	if (_code == 0)
		return (*this);
	else if (_code > 0 && _code <= sub_characters.size())
		return sub_characters[_code - 1];
	else return nullptr;
}

Nullable<Character> StoryViewer::MultiCharacter::operator[](int _code) const
{
	return Getter(_code);
}

int MultiCharacter::Count() const
{
	return sub_characters.size() + 1;
}
