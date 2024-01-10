#include "Event.h"

using namespace StoryViewer;
Event::Event()
{
	description = L"<NO-DESCRIPTION>";
	name = L"<NO-NAME>";
	related_characters = new CharacterCollection();
	related_issue = nullptr;
	date_time = nullptr;
}

Event::Event(String _name, String _description, CharacterCollection* _p_related_characters, Issue* _p_issue, DateTime* _p_date_time)
{
	description = _description;
	name = _name;
	related_characters = _p_related_characters;
	related_issue = _p_issue;
	date_time = _p_date_time;
}

Event::~Event()
{
	delete related_issue;
}

String& Event::Description()
{
	return description;
}

String& Event::Name()
{
	return name;
}

CharacterCollection*& Event::RelatedCharacters()
{
	return related_characters;
}

Issue*& Event::RelatedIssue()
{
	return related_issue;
}

DateTime*& Event::Date_Time()
{
	return date_time;
}

void Event::AddCharacter(Character* _char)
{
	if (!ContainCharacter(_char->Name()))
		related_characters->push_back(_char);
}

bool Event::ContainCharacter(const String& _name) const
{
	for (auto _iter = related_characters->begin(); _iter != related_characters->end(); ++_iter)
	{
		if ((*_iter)->Name() == _name)
			return true;
	}
	return false;
}
