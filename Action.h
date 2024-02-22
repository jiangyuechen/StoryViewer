#pragma once
#include "basic.h"
#include "Object.h"
#include "Story.h"
#include "Event.h"
#include "Capture.h"

namespace StoryViewer
{
	class Action : public Object
	{
	protected:
		// Object* binding_object;
		// Capture* capt;
	public:
		Action()/* : binding_object(nullptr) */{}
		// Action(Object* _binding_object) : binding_object(_binding_object) {}
		virtual ~Action() { /*binding_object = nullptr;*/ }

		virtual void Do();
		virtual void Undo();
		virtual String ToString(DETAIL_TYPE _style = 0) const override;
	};

	class AddCharacterAction : public Action
	{
	protected:
		Story* main_story;
		Character* char_added;
	public:
		AddCharacterAction() : Action(), main_story(nullptr), char_added(nullptr) {}
		// AddCharacterAction() : Action() , main_story(nullptr), char_added(nullptr) {}

		AddCharacterAction(Story* _ms, Character* _ca) : Action(), main_story(_ms), char_added(_ca) {}

		virtual void Do() override;
		virtual void Undo() override;

		virtual String ToString(DETAIL_TYPE _style = 0) const override;
	};

	class AddLinkAction : public Action
	{
	protected:
		Story* main_story;
		Link* link_added;
	public:
		AddLinkAction() : Action(), main_story(nullptr), link_added(nullptr) {}
		AddLinkAction(Story* _ms, Link* _la) : Action(), main_story(_ms), link_added(_la) {}

		virtual void Do() override;
		virtual void Undo() override;

		// virtual String ToString(DETAIL_TYPE _style = 0) const override;
	};

	class AddAkaAction : public Action
	{
	protected:
		Character* main_char;
		String aka_added;
	public:
		AddAkaAction() : Action(), main_char(nullptr), aka_added() {}
		AddAkaAction(Character* _mc, const String& _aa) : Action(), main_char(_mc), aka_added(_aa) {}
		virtual void Do() override;
		virtual void Undo() override;
		// virtual String ToString(DETAIL_TYPE _style = 0) const override;
	};


}