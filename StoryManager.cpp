#include "StoryManager.h"

using namespace StoryViewer;

StoryManager::StoryManager()
	: Object(), st(nullptr), actlist() {}

StoryManager::StoryManager(Story* _st)
	: Object(), st(_st), actlist() {}

StoryManager::StoryManager(Story* _st, const ActionList& _acl)
	: Object(), st(_st), actlist(_acl) {}

StoryManager::~StoryManager()
{
	st = nullptr;
	Clear();
}

void StoryManager::PushAction(Action* _act, bool _do_once)
{
	actlist.push(_act);
	if (_do_once)
		_act->Do();
}

void StoryManager::PopAction(bool _undo_once)
{
	if (actlist.empty())
		return;

	if (_undo_once)
		actlist.top()->Undo();
	
	actlist.pop();

}

Action* StoryManager::LastAction() const
{
	return actlist.top();
}

size_t StoryManager::Count() const
{
	return actlist.size();
}

void StoryManager::Clear()
{
	while (!actlist.empty())
	{
		actlist.pop();
	}
}

String StoryManager::ToString(DETAIL_TYPE _style) const
{
	String _ret{};
	_ret += L"<操作者>";
	if (_style != LEAST_DETAILED)
	{
		if (!st)
			_ret += L"[未绑定故事]";
		else
		{
			// TOSTRING_APPEND(_ret, 3, L"[绑定的故事:", st->ToString(LEAST_DETAILED), L"]");

			_ret += L"[绑定的故事:";
			_ret += st->ToString(LEAST_DETAILED);
			_ret += L"]";
		}
	}
	return _ret;
}

