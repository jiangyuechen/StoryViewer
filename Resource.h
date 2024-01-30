#pragma once

#include "basic.h"
#include "Object.h"

#ifndef _RESOURCE
#define _RESOURCE
#endif

namespace StoryViewer
{
	class Resource;

	enum FILE_TYPE
	{
		ANY = 0,
		TEXT,
		IMAGE,
		AUDIO,
		VIDEO
	};

	class Resource : public Object
	{
	protected:
		FILE_TYPE file_type;
		String file_dir;
		bool _Valid(String);
	public:
		static bool use_inline; // Open .txt file in the console instead of notepad.
		
		Resource();
		Resource(String);

		String GetFileDir() const;
		void SetFileDir(String) _MUTABLE;

		bool Open();

		virtual String ToString() const override;

	};
}