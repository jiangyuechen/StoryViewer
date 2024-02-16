#pragma once

#include "basic.h"
#include "Object.h"

#ifndef _INFORMATION
#define _INFORMATION
#endif

namespace StoryViewer
{
	class Information;

	enum FILE_TYPE
	{
		ANY = 0,
		TEXT,
		IMAGE,
		AUDIO,
		VIDEO
	};

	class Information : public Object
	{
	protected:
		FILE_TYPE file_type;
		String file_dir;
		bool _Valid(String);
	public:
		static bool use_inline; // Open .txt file in the console instead of notepad.
		
		Information();
		Information(String);

		String GetFileDir() const;
		void SetFileDir(String) _MUTABLE;

		bool Open();

		virtual String ToString(int _style = 0) const override;

	};
}