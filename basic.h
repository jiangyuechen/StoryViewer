#pragma once


#ifndef STORY_VIEWER
#define STORY_VIEWER
#endif

// 输入输出
#include <iostream>
#include <fstream>
#include <io.h>

// 系统操作
#include <Windows.h>
#include <commdlg.h>
#include <iomanip>

// STL
#include <vector>
#include <string>
#include <map>
#include <list>
#include <functional>
#include <stack>

// 异常
#include <exception>

// 其他
#include <stdarg.h>

// 宏
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

#ifndef _INLINE
#define _INLINE
#endif

#ifndef _MUTABLE
#define _MUTABLE
#endif

#ifndef _CONST
#define _CONST const
#endif


// 有用的 typedef
typedef std::wstring String;
typedef std::vector<std::wstring> StringList;
typedef int DETAIL_TYPE;

// 预定义值
constexpr size_t SIZE_T_MIN = 0;
#define LEAST_DETAILED 0
#define NORMAL_DETAILED 1
#define MOST_DETAILED 2

#define TOSTRING_START(_ret) String _ret{}
#define TOSTRING_END(_ret) return _ret

