#include "Event.h"
#include "Story.h"
#include "basic.h"
#include "Character.h"

using namespace StoryViewer;

Story::Story()
{
	this->story_name = L"<NO-NAME>";
	this->story_events = StoryLinkedList();
	this->story_characters = CharacterCollection();
	this->story_event_links = EventLinkTable();
	this->story_character_links = CharacterLinkTable();
}

Story::Story(
	const String& _story_name,
	Nullable<StoryLinkedList> _p_story_events,
	Nullable<CharacterCollection> _p_story_characters,
	Nullable<EventLinkTable> _p_story_event_links,
	Nullable<CharacterLinkTable> _p_story_character_links)
{
	this->story_name = _story_name;
	this->story_events = 
		!_p_story_events.IsNull() ?
		_p_story_events.Val() :
		StoryLinkedList();
	this->story_characters =
		!_p_story_characters.IsNull() ?
		_p_story_characters.Val() :
		CharacterCollection();
	this->story_event_links = 
		!_p_story_event_links.IsNull() ?
		_p_story_event_links.Val() :
		EventLinkTable();
	this->story_character_links =
		!_p_story_character_links.IsNull() ?
		_p_story_character_links.Val() :
		CharacterLinkTable();
}

Story::~Story()
{

}

String& Story::StoryName()
{
	return this->story_name;
}

StoryLinkedList& Story::StoryLine()
{
	return this->story_events;
}

CharacterCollection& Story::StoryCharacters()
{
	return this->story_characters;
}

EventLinkTable& Story::StoryEventLinks()
{
	return this->story_event_links;
}

CharacterLinkTable& Story::StoryCharacterLinks()
{
	return this->story_character_links;
}

void Story::AddEventLast(Event* _p_event)
{
	this->story_events.push_back(_p_event);
}

void Story::AddEventFirst(Event* _p_event)
{
	this->story_events.push_front(_p_event);
}

void Story::AddEventBefore(StoryLinkedList::iterator& _where, Event* _event)
{
	if (_where != story_events.begin())
	{
		story_events.insert(_where, _event);
	}
	else
	{
		story_events.push_front(_event);
	}
}

void Story::AddEventAfter(StoryLinkedList::iterator& _where, Event* _event)
{
	if (_where != story_events.end())
	{
		_where++;
		story_events.insert(_where, _event);
	}
	else
	{
		story_events.push_back(_event);
	}
}


Event* Story::FindEventPtrByName(const String& _name)
{
	for (const auto& _iter : story_events)
	{
		if ((_iter)->Name() == _name)
			return _iter;
	}
	return nullptr;
}

StoryLinkedList Story::FilterEvent(EventFilter _condition)
{
	StoryLinkedList _ret = StoryLinkedList();
	for (const auto& _iter : story_events)
	{
		if (_condition(*_iter) == true)
		{
			_ret.push_back(_iter);
		}
	}
	return _ret;
}

bool Story::DeleteEventByName(const String& _name)
{
	for (
		StoryLinkedList::iterator _iter = story_events.begin();
		_iter != story_events.end();
		++_iter
		)
	{
		if ((*_iter)->Name() == _name)
		{
			story_events.erase(_iter);
			return true;
		}
	}
	return false;
}

void Story::ClearEvent()
{
	story_events.clear();
}

void Story::AddCharacter(Character* _p_character)
{
	if (FindCharacterPtrByName(_p_character->Name()) == nullptr )
		story_characters.push_back(_p_character);
}


Character* Story::FindCharacterPtrByName(const String& _name, bool _include_aka)
{
	for (const auto& _iter : story_characters)
	{
		if (_iter->Name() == _name
			|| (_include_aka && Object::_In<String>(_iter->Aka(), _name)))
		{
			return _iter;
		}
	}
	return nullptr;
}

CharacterCollection StoryViewer::Story::FilterCharacter(CharacterFilter _condition)
{
	CharacterCollection _ret = CharacterCollection();
	for (const auto& _iter : story_characters)
	{
		if (_condition(*_iter) == true)
		{
			_ret.push_back(_iter);
		}
	}
	return _ret;
}

bool Story::DeleteCharacterByName(const String& _name, bool _include_aka)
{
	for (
		CharacterCollection::iterator _iter = story_characters.begin();
		_iter != story_characters.end();
		++_iter
		)
	{
		if ((*_iter)->Name() == _name
			|| (_include_aka && Object::_In<String>((*_iter)->Aka(), _name)))
		{
			story_characters.erase(_iter);
			return true;
		}
	}
	return false;
}

bool Story::DeleteCharacterByFilter(CharacterFilter _condition, bool _once)
{
	bool flag = false;
	for (
		CharacterCollection::iterator _iter = story_characters.begin();
		_iter != story_characters.end();
		++_iter
		)
	{
		if (_condition(**_iter) == true)
		{
			_iter = story_characters.erase(_iter);
			flag = true;
			if (_once)
				return true;
		}
	}
	return flag;
}

bool Story::DeleteCharacterByAttribute(const String& _key, const String& _expected_value)
{
	return DeleteCharacterByFilter([&](Character _c) { return _c.ContainKeyValue(std::make_pair(_key, _expected_value)); });
}

bool Story::DeleteCharacterByAttribute(const Attribute& _kv)
{
	return DeleteCharacterByFilter([&](Character _c) { return _c.ContainKeyValue(_kv); });
}

void Story::ClearCharacter()
{
	story_characters.clear();
}

void Story::AddCharacterLink(Link* _p_link)
{
	this->story_character_links.push_back(_p_link);
}

bool Story::DeleteCharacterLinkByFilter(CharacterLinkFilter _condition, bool _once)
{
	bool flag = false;
	for (auto _iter = story_character_links.begin(); _iter != story_character_links.end(); ++_iter)
	{
		if (_condition(**_iter) == true)
		{
			_iter = story_character_links.erase(_iter);
			flag = true;
			if (_once)
				return true;
		}
	}
	return flag;
}

CharacterLinkTable Story::FilterCharacterLink(CharacterLinkFilter _condition)
{
	CharacterLinkTable _ret = CharacterLinkTable();
	for (const auto& _iter : story_character_links)
	{

		if (_condition(*_iter) == true)
		{
			_ret.push_back(_iter);
		}
	}
	return _ret;
}

Story& Story::operator<<(Character& _tar_char)
{
	this->AddCharacter(&_tar_char);
	return *this;
}

Story& Story::operator<<(Event& _tar_event)
{
	this->AddEventLast(&_tar_event);
	return *this;
}

Story& Story::operator<<(Link& _tar_link)
{
	this->AddCharacterLink(&_tar_link);
	return *this;
}

CharacterCollection Story::AutoConfigureRelatedCharacter(Event* _tar_event)
{
	CharacterCollection _ret = CharacterCollection();
	return _ret;
}

String Story::ToString(int _style) const
{
	String _ret{};
	_ret += L"<故事>";
	if (_style == LEAST_DETAILED)
	{
		_ret += this->story_name;
		return _ret;
	}

	_ret += this->story_name;
	_ret += L"\n角色:\n";
	for (const auto& _sc_iter : this->story_characters)
	{
		_ret += L"    ";
		_ret += _sc_iter->ToString(_style);
		_ret += L"\n";
	}
	_ret += L"\n角色关系:\n";
	for (const auto& _scl_iter : this->story_character_links)
	{
		_ret += L"    ";
		_ret += _scl_iter->ToString(_style);
		_ret += L"\n";
	}
	_ret += L"\n故事线:\n";
	for (const auto& _sl_iter : this->story_events)
	{
		_ret += L"    ";
		_ret += _sl_iter->ToString(_style);
		_ret += L"\n";
	}
	return _ret;
}
