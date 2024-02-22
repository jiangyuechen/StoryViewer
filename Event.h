#pragma once
#include "basic.h"
#include "Object.h"
#include "Character.h"
#include "DateTime.h"

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
		CharacterCollection related_characters;
		Nullable<DateTime> date_time;
	public:
		Event();
		Event(const String& _name = L"<NO-NAME>",const String& _description = L"<NO-DESCRIPTION>", Nullable<CharacterCollection> _p_related_characters = nullptr, Nullable<DateTime> _p_date_time = nullptr);
		~Event();

		String& Description() _MUTABLE;
		String& Name() _MUTABLE;
		CharacterCollection& RelatedCharacters() _MUTABLE;
		Nullable<DateTime>& Date_Time() _MUTABLE;

		void AddCharacter(Character& _char);
		bool ContainCharacter(const String& _name) const;

		virtual String ToString(int _style = 0) const override;
	};

}