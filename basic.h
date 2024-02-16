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
#include <fstream>
#include <Windows.h>
#include <iomanip>
#include <commdlg.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <functional>
#include <io.h>
#include <exception>

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#define MAKE_PTR(_Class,_Obj) _Class * _ptr_##_Obj = &_Obj
#define PTR(_Obj) _ptr_##_Obj

#define _Instance_
#define _String_
#define _Safe_Instance_(_Obj) _Obj&&

#define VAR_TO_STRING(_Str) #_Str

#define PTR_VALIDATE(_Ptr) if (!_Ptr) { throw std::exception("Error : Empty Pointer!"); }

constexpr size_t SIZE_T_MIN = 0;

// typedef std::vector<std::pair<std::wstring, std::wstring>> AttributeList;

typedef std::vector<std::wstring> StringList;
typedef std::wstring String;

// #define interface struct

#define LEAST_DETAILED 0
#define NORMAL_DETAILED 1
#define MOST_DETAILED 2