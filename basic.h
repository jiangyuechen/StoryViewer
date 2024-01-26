#pragma once


#ifndef STORY_VIEWER
#define STORY_VIEWER
#endif

#ifndef _INLINE
#define _INLINE
#endif

#ifndef _MUTABLE
#define _MUTABLE
#endif

#ifndef _CONST
#define _CONST const
#endif

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <functional>

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

constexpr size_t SIZE_T_MIN = 0;

// typedef std::vector<std::pair<std::wstring, std::wstring>> AttributeList;

typedef std::vector<std::wstring> StringList;
typedef std::wstring String;
