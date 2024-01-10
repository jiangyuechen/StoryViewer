#include "Issue.h"
#include "Event.h"

using namespace StoryViewer;

Issue::Issue() : Object()
{
	description = L"<NO-DESCRIPTION>";
}

Issue::Issue(const String& _desc) : Object()
{
	description = _desc;
}

Issue::~Issue()
{
	
}

String& Issue::Description()
{
	return description;
}
