#pragma once
#include "basic.h"
#include "Object.h"
#include "ValueType.h"

namespace StoryViewer
{
	class Reference : public Object
	{
	protected:
		Object* ref_ptr;
		Nullable<String> description;
	public:
		Reference() noexcept : Object(), ref_ptr(nullptr), description(nullptr) {}
		Reference(Object* _ptr) noexcept : Object(), ref_ptr(_ptr), description(nullptr) {}
		Reference(Object* _ptr, const String& _desc) noexcept : Object(), ref_ptr(_ptr), description(_desc) {}
		virtual ~Reference()
		{
			// do not delete ref_ptr!
			ref_ptr = nullptr;
		}
		Object Val()
		{
			return *ref_ptr;
		}
		Object* ValPtr()
		{
			return ref_ptr;
		}
		Object& ValRef()
		{
			return *ref_ptr;
		}
		Object*& ValPtrRef()
		{
			return ref_ptr;
		}
		void Modify(Object* _new_ptr)
		{
			ref_ptr = nullptr;
			ref_ptr = _new_ptr;
		}
		virtual String ToString(int _style = 0) const
		{
			String _ret{};
			_ret += L"<ÒýÓÃ>";
			if (!ref_ptr)
			{
				_ret += L"(¿Õ)";
			}
			else
			{
				_ret += L"->";
				_ret += ref_ptr->ToString(LEAST_DETAILED);
			}
			return _ret;
		}
	};
}