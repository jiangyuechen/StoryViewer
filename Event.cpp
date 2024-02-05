#include "Event.h"

using namespace StoryViewer;
Event::Event() : Object()
{
	description = L"<NO-DESCRIPTION>";
	name = L"<NO-NAME>";
	related_characters = CharacterCollection();
	date_time = nullptr;
}

Event::Event(const String& _name,const String& _description, Nullable<CharacterCollection> _p_related_characters, Nullable<DateTime> _p_date_time) : Object()
{
	description = _description;
	name = _name;
	related_characters = !_p_related_characters.IsNull() ? _p_related_characters.Val() : CharacterCollection();
	date_time = _p_date_time;
}

Event::~Event()
{
}

String& Event::Description()
{
	return description;
}

String& Event::Name()
{
	return name;
}

CharacterCollection& Event::RelatedCharacters()
{
	return related_characters;
}


Nullable<DateTime>& Event::Date_Time()
{
	return date_time;
}

void Event::AddCharacter(Character& _char)
{
	if (!ContainCharacter(_char.Name()))
		related_characters.push_back(&_char);
}

bool Event::ContainCharacter(const String& _name) const
{
	for (auto _iter = related_characters.begin(); _iter != related_characters.end(); ++_iter)
	{
		if ((*_iter)->Name() == _name)
			return true;
	}
	return false;
}

String Event::ToString(bool _detailed) const
{
	String _ret{};
	_ret += L"<ÊÂ¼þ>[";
	_ret += this->name;
	if (!this->date_time.IsNull())
	{
		_ret += L" (";
		_ret += date_time.ValPtr()->ToString();
		_ret += L")";
	}
	_ret += L" : ";
	_ret += this->description;
	_ret += L"]";
	return _ret;
}
