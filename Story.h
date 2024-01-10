#pragma once
#include "basic.h"
#include "Object.h"
#include "DateTime.h"
#include "Event.h"
#include "Character.h"
#include "Link.h"

#ifndef _STORY
#define _STORY
#endif

typedef std::list<StoryViewer::Event*> StoryLinkedList;
typedef std::vector<StoryViewer::Character*> CharacterCollection;
typedef std::vector<StoryViewer::Link<StoryViewer::Event, StoryViewer::Event>*> EventLinkTable;
typedef std::vector<StoryViewer::Link<StoryViewer::Character, StoryViewer::Character>*> CharacterLinkTable;
typedef std::function<bool(StoryViewer::Event)> EventFilter;
typedef std::function<bool(StoryViewer::Character)> CharacterFilter;
typedef std::function<bool(StoryViewer::Link<StoryViewer::Character, StoryViewer::Character>)> CharacterLinkFilter;

namespace StoryViewer
{
	class Character;
	class Event;
	class Story : public Object
	{
	protected:
		String story_name;
		StoryLinkedList story_events;
		CharacterCollection story_characters;
		EventLinkTable story_event_links;
		CharacterLinkTable story_character_links;

	public:
		Story();
		Story(
			const String& _story_name,
			Nullable<StoryLinkedList> _p_story_events = nullptr,
			Nullable<CharacterCollection> _p_story_characters = nullptr,
			Nullable<EventLinkTable> _p_story_event_links = nullptr,
			Nullable<CharacterLinkTable> _p_story_character_links = nullptr
		);
		~Story();

		String& StoryName();
		StoryLinkedList& StoryLine();
		CharacterCollection& StoryCharacters();
		EventLinkTable& StoryEventLinks();
		CharacterLinkTable& StoryCharacterLinks();

		void AddEventLast(Event* _p_event);
		void AddEventFirst(Event* _p_event);
		void AddEventBefore(StoryLinkedList::iterator& _where, Event* _event);
		void AddEventAfter(StoryLinkedList::iterator& _where, Event* _event);
		Event* FindEventPtrByName(const String& _name);
		StoryLinkedList FilterEvent(EventFilter _condition);
		bool DeleteEventByName(const String& _name);
		void ClearEvent();

		void AddCharacter(Character* _p_character);
		Character* FindCharacterPtrByName(const String& _name, bool _include_aka = false);
		CharacterCollection FilterCharacter(CharacterFilter _condition);
		bool DeleteCharacterByName(const String& _name, bool _include_aka = true);
		bool DeleteCharacterByFilter(CharacterFilter _condition, bool _once = true);
		bool DeleteCharacterByAttribute(const String& _key, const String& _expected_value);
		bool DeleteCharacterByAttribute(const Attribute& _kv);
		void ClearCharacter();

		void AddCharacterLink(Link<Character, Character>* _p_link);
		// bool DeleteCharacterLink(Link<Character, Character>* _p_tar_link);
		bool DeleteCharacterLinkByFilter(CharacterLinkFilter _condition, bool _once = true);
		CharacterLinkTable FilterCharacterLink(CharacterLinkFilter _condition);

		Story& operator<<(Character& _tar_char);
		Story& operator<<(Event& _tar_event);
		Story& operator<<(Link<Character, Character>& _tar_link);

		CharacterCollection AutoConfigureRelatedCharacter(Event* _tar_event);
	};
}