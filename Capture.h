#pragma once
#include "basic.h"
#include "Object.h"
#include "Story.h"
#include "Character.h"
#include "Event.h"
#include "Link.h"

namespace StoryViewer
{
	struct Capture
	{

		Story* c_story = nullptr;
		std::vector<Story*> c_other_story = std::vector<Story*>();

		Character* c_character = nullptr;
		std::vector<Character*> c_other_character = std::vector<Character*>();

		Event* c_event = nullptr;
		std::vector<Event*> c_other_event = std::vector<Event*>();

		Link* c_link = nullptr;
		std::vector<Link*> c_other_link = std::vector<Link*>();

		String c_string = String();
		std::vector<String> c_other_string = std::vector<String>();

	};

}