#pragma once
#include "basic.h"
#include "Object.h"

namespace StoryViewer
{
	template <typename T>
	class Nullable
	{
	private:
		T value;
		bool is_null;

	public:
		// static const Nullable<T> NULL_VALUE;
		Nullable() noexcept
		{
			value = T();
			is_null = true;
		}
		Nullable(T _value) noexcept
		{
			value = _value;
			is_null = false;
		}
		Nullable(Nullable<T>& _ref) = default;
		bool IsNull() const { return this->is_null; }

		void operator=(T _value)
		{
			this->value = _value;
			is_null = false;
		}
		// void operator=(T& _ref_value);

		bool operator!() const
		{
			return this->is_null;
		}

		T Val() const
		{
			return this->value;
		}
		T operator*() const
		{
			return this->value;
		}

		void operator==(Nullable<T> _right) const
		{
			return (!(this->is_null)) && (this->value == *_right);
		}

		void Reset()
		{
			this->value = T();
			is_null = true;
		}
	};
}