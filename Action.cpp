#include "Action.h"

using namespace StoryViewer;

void Action::Do() { /*Do Nothing*/ }

void Action::Undo() { /*Do Nothing*/ }

String Action::ToString(DETAIL_TYPE _style) const
{
	String _ret{};
	_ret += L"<运行时操作>";
	return _ret;
}

void AddCharacterAction::Do()
{
	main_story->AddCharacter(char_added);
}

void AddCharacterAction::Undo()
{
	// TODO: 增加 Undo 函数定义。
}

String AddCharacterAction::ToString(DETAIL_TYPE _style) const
{
	String _ret{};
	_ret += L"<运行时操作: 增加角色>";
	if (!main_story)
	{
		_ret += L"[未绑定故事]";
	}
	else
	{
		_ret += L"[绑定的故事:";
		_ret += main_story->ToString(LEAST_DETAILED);
		_ret += L"]";
	}
	if (!char_added)
	{
		_ret += L"[未绑定角色]";
	}
	else
	{
		_ret += L"[绑定的角色:";
		_ret += char_added->ToString(LEAST_DETAILED);
		_ret += L"]";
	}
	return _ret;
}

void AddLinkAction::Do()
{
	main_story->AddCharacterLink(link_added);
}

void AddLinkAction::Undo()
{
	// TODO: 增加 Undo 函数定义。
}

void AddAkaAction::Do()
{
	main_char->AddAKA(aka_added);
}

void AddAkaAction::Undo()
{
	main_char->RemoveAKA(aka_added);
}