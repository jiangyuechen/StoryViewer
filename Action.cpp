#include "Action.h"

using namespace StoryViewer;

void Action::Do() { /*Do Nothing*/ }

void Action::Undo() { /*Do Nothing*/ }

String Action::ToString(DETAIL_TYPE _style) const
{
	String _ret{};
	_ret += L"<����ʱ����>";
	return _ret;
}

void AddCharacterAction::Do()
{
	main_story->AddCharacter(char_added);
}

void AddCharacterAction::Undo()
{
	// TODO: ���� Undo �������塣
}

String AddCharacterAction::ToString(DETAIL_TYPE _style) const
{
	String _ret{};
	_ret += L"<����ʱ����: ���ӽ�ɫ>";
	if (!main_story)
	{
		_ret += L"[δ�󶨹���]";
	}
	else
	{
		_ret += L"[�󶨵Ĺ���:";
		_ret += main_story->ToString(LEAST_DETAILED);
		_ret += L"]";
	}
	if (!char_added)
	{
		_ret += L"[δ�󶨽�ɫ]";
	}
	else
	{
		_ret += L"[�󶨵Ľ�ɫ:";
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
	// TODO: ���� Undo �������塣
}

void AddAkaAction::Do()
{
	main_char->AddAKA(aka_added);
}

void AddAkaAction::Undo()
{
	main_char->RemoveAKA(aka_added);
}