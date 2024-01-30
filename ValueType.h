#pragma once
#include "basic.h"
#include "Object.h"

#ifndef _VALUE_TYPE
#define _VALUE_TYPE
#endif

namespace StoryViewer
{
#ifdef USE_DISCRETE
	class DiscreteBase;
	class Discrete;
#endif

	class WeakValueType;

	template <typename T>
	class Nullable;

	enum VALUE_TYPE
	{
		UNKNOWN,
		INTEGER,
		STRING,
		DOUBLE,
		DISCRETE
	};

	template <typename T>
	class Nullable : public Object
	{
	private:
		T* val_ptr;
		bool is_null;
	public:
		// static const void* NULL_VALUE = nullptr;
		Nullable() noexcept
		{
			val_ptr = nullptr;
			is_null = true;
		}
		Nullable(T _value) noexcept
		{
			val_ptr = new T(_value);
			is_null = false;
		}
		// 使用 nullptr 作为 null 值.
		Nullable(void* _val_ptr) noexcept
		{
			if (_val_ptr == nullptr)
			{
				val_ptr = nullptr;
				is_null = true;
			}
			else
			{
				val_ptr = (T*)_val_ptr;
				is_null = false;
			}
		}
		Nullable(Nullable<T>& _ref) = default;
		bool IsNull() const { return this->is_null; }

		void operator=(T _value)
		{
			delete val_ptr;
			this->val_ptr = new T(_value);
			is_null = false;
		}
		// void operator=(T& _ref_value);

		/// <summary>
		/// Returns the stored value.
		/// Tips: If T is an abstract class, or you want to implement polymorphic characteristics, use ValPtr() instead of Val().
		/// </summary>
		T Val() const
		{
			return *(this->val_ptr);
		}
		T &ValRef() _MUTABLE
		{
			return *(this->val_ptr);
		}
		/// <summary>
		/// Returns the pointer of the stored value.
		/// Tips: If T is an abstract class, or you want to implement polymorphic characteristics, use ValPtr() instead of Val().
		/// </summary>
		T *ValPtr() const
		{
			return this->val_ptr;
		}
		T *&ValPtrRef() _MUTABLE
		{
			return this->val_ptr;
		}

		T operator*() const
		{
			return *(this->val_ptr);
		}

		bool operator==(const Nullable<T>& _right) const
		{
			return (!(this->is_null)) && (this->Val() == _right.Val());
		}
		bool operator!=(const Nullable<T>& _right) const
		{
			return !(this->operator==(_right));
		}
		bool operator!() const
		{
			return this->IsNull();
		}

		void Reset()
		{
			delete val_ptr;
			this->val_ptr = nullptr;
			is_null = true;
		}
		
		//static bool operator==(const Nullable<T>& _x, const Nullable<T>& _y) const
		//{
		//	return !_x.IsNull() && !_y.IsNull() && _x.Val() == _y.Val()
		//}
	};
#ifdef USE_DISCRETE
	class DiscreteBase
	{
	private:
		std::vector<String> value_collection;
	public:
		DiscreteBase();
		DiscreteBase(const std::vector<String>& _value_collection);
		Discrete MakeDiscrete();
		Discrete operator()(const String& _value);
	};
	class Discrete
	{
	private:
		std::vector<String> value_collection;
		String value;
		// bool _Test(const String& _value);
	public:
		Discrete();
		Discrete(const std::vector<String>& _value_collection);
		Discrete(const std::vector<String>& _value_collection, const String& _val);
		Discrete(const Discrete& _refer) = default;
		Discrete(Discrete&& _right_refer) = default;
		void operator=(const String& _value);
		Discrete operator()(const String& _value);
		std::vector<String> ValueCollection() const;
		operator String() const;
	};
#endif

	class WeakValueType : public Object
	{
	private:
		int* val_int;
		double* val_double;
		String* val_string;
#ifdef USE_DISCRETE
		Discrete* value_discrete;
#endif
		VALUE_TYPE type;
		void _Reset(bool _do_delete = true)
		{
			if (_do_delete)
			{
				delete val_int;
				delete val_double;
				delete val_string;
#ifdef USE_DISCRETE
				delete value_discrete;
#endif
			}
			val_int = nullptr;
			val_double = nullptr;
			val_string = nullptr;
#ifdef USE_DISCRETE
			value_discrete = nullptr;
#endif
			type = UNKNOWN;
		}
	public:
		WeakValueType() { _Reset(false); }
		WeakValueType(const WeakValueType& _refer) noexcept
		{
			_Reset(false);
			this->type = _refer.Type();
			switch (this->type)
			{
			case INTEGER:
				this->val_int = new int(int(_refer));
				break;
			case STRING:
				this->val_string = new String(String(_refer));
				break;
			case DOUBLE:
				this->val_double = new double(double(_refer));
				break;
			}
		}
		WeakValueType(WeakValueType& _refer) noexcept
		{
			_Reset(false);
			this->type = _refer.Type();
			switch (this->type)
			{
			case INTEGER:
				this->val_int = new int(int(_refer));
				break;
			case STRING:
				this->val_string = new String(String(_refer));
				break;
			case DOUBLE:
				this->val_double = new double(double(_refer));
				break;
			}
		}
		// WeakValueType(WeakValueType&& _right_refer) noexcept;
		WeakValueType(const int& _value_int)
		{
			_Reset(false);
			val_int = new int(_value_int);
			type = INTEGER;
		}
		WeakValueType(const double& _value_double)
		{
			_Reset(false);
			val_double = new double(_value_double);
			type = DOUBLE;
		}
		WeakValueType(const wchar_t _value_string[])
		{
			_Reset(false);
			val_string = new String(_value_string);
			type = STRING;
		}
		WeakValueType(const String& _value_string)
		{
			_Reset(false);
			val_string = new String(_value_string);
			type = STRING;
		}
		~WeakValueType()
		{
			_Reset(true);
		}

		VALUE_TYPE Type() const { return this->type; }

		void operator=(const int& _value_int)
		{
			_Reset();
			val_int = new int(_value_int);
		}
		void operator=(const double& _value_double)
		{
			_Reset();
			val_double = new double(_value_double);
		}
		void operator=(const String& _value_string)
		{
			_Reset();
			val_string = new String(_value_string);
		}
		void operator=(const wchar_t _value_string[])
		{
			_Reset();
			val_string = new String(_value_string);
		}
		bool operator==(const WeakValueType& _comp)
		{
			return this->Type() == _comp.Type();
		}
		explicit operator int() const
		{
			return *val_int;
		}
		explicit operator double() const
		{
			return *val_double;
		}
		explicit operator String() const
		{
			return *val_string;
		}
		virtual String ToString() const override
		{
			String _ret{};
			switch (this->type)
			{
			case INTEGER:
				_ret += std::to_wstring(*val_int);
				break;
			case DOUBLE:
				_ret += std::to_wstring(*val_double);
				break;
			case STRING:
				_ret += (*val_string);
				break;
			}
			return _ret;
		}
	};
	

}