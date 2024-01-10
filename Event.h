#pragma once
#include "basic.h"
#include "Object.h"
#include "Character.h"
#include "DateTime.h"
#include "Issue.h"

#ifndef _EVENT
#define _EVENT
#endif

typedef std::vector<StoryViewer::Character*> CharacterCollection;

namespace StoryViewer
{
	class Event : public Object
	{
	protected:
		String description;
		String name;
		CharacterCollection* related_characters;
		Issue* related_issue;
		DateTime* date_time;
	public:
		Event();
		Event(String _name = L"<NO-NAME>", String _description = L"<NO-DESCRIPTION>", CharacterCollection* _p_related_characters = nullptr, Issue* _p_issue = nullptr, DateTime* _p_date_time = nullptr);
		~Event();

		String& Description();
		String& Name();
		CharacterCollection*& RelatedCharacters();
		Issue*& RelatedIssue();
		DateTime*& Date_Time();

		void AddCharacter(Character* _char);
		bool ContainCharacter(const String& _name) const;
	};
}