#pragma once

#include "basic.h"
#include "Object.h"
#include "Story.h"
#include "Capture.h"
#include "Action.h"
#include "Character.h"

namespace StoryViewer
{
	class StoryManager : public Object
	{
		typedef std::stack<Action*> ActionList;

	protected:
		Story* st;
		ActionList actlist;
		
		//Character* I, * YOU, * HE, * SHE, * IT;
		//CharacterCollection* THEY;

	public:
		StoryManager();
		StoryManager(Story* _st);
		StoryManager(Story* _st, const ActionList& _acl);
		virtual ~StoryManager();

		void PushAction(Action* _act, bool _do_once = true);
		void PopAction(bool _undo_once = true);

		Action* LastAction() const;

		size_t Count() const;

		void Clear();

		virtual String ToString(DETAIL_TYPE _style = 0) const override;
	};
}