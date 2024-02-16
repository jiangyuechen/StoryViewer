#pragma once
#include "basic.h"
#include "Object.h"

#ifndef _VALUE_TYPE
#define _VALUE_TYPE
#endif

namespace StoryViewer
{
	typedef StringList Collection;
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
		COLLECTION,
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
		//Nullable(T _value) noexcept
		//{
		//	val_ptr = new T(_value);
		//	is_null = false;
		//}
		Nullable(const T& _value_ref) noexcept
		{
			val_ptr = new T(_value_ref);
			is_null = false;
		}
		Nullable(T&& _rvalue_ref) noexcept
		{
			val_ptr = new T(_rvalue_ref);
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

		void operator=(const T& _value)
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
			PTR_VALIDATE(val_ptr);
			return *(this->val_ptr);
		}
		T& ValRef() _MUTABLE
		{
			PTR_VALIDATE(val_ptr);
			return *(this->val_ptr);
		}
		/// <summary>
		/// Returns the pointer of the stored value.
		/// Tips: If T is an abstract class, or you want to implement polymorphic characteristics, use ValPtr() instead of Val().
		/// </summary>
		T* ValPtr() const
		{
			return this->val_ptr;
		}
		T*& ValPtrRef() _MUTABLE
		{
			return this->val_ptr;
		}

		T operator*() const
		{
			PTR_VALIDATE(val_ptr);
			return *(this->val_ptr);
		}

		bool operator==(const Nullable<T>& _right) const
		{
			return !this->IsNull() && !_right.IsNull() && this->Val() == _right.Val();
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
		Collection* val_collection;
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
				delete val_collection;
#ifdef USE_DISCRETE
				delete value_discrete;
#endif
			}
			val_int = nullptr;
			val_double = nullptr;
			val_string = nullptr;
			val_collection = nullptr;
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
				this->val_int = new int(static_cast<int>(_refer));
				break;
			case STRING:
				this->val_string = new String(static_cast<String>(_refer));
				break;
			case DOUBLE:
				this->val_double = new double(static_cast<double>(_refer));
				break;
			case COLLECTION:
				this->val_collection = new Collection(static_cast<Collection>(_refer));
			}
		}
		WeakValueType(WeakValueType& _refer) noexcept
		{
			_Reset(false);
			this->type = _refer.Type();
			switch (this->type)
			{
			case INTEGER:
				this->val_int = new int(static_cast<int>(_refer));
				break;
			case STRING:
				this->val_string = new String(static_cast<String>(_refer));
				break;
			case DOUBLE:
				this->val_double = new double(static_cast<double>(_refer));
				break;
			case COLLECTION:
				this->val_collection = new Collection(static_cast<Collection>(_refer));
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
		WeakValueType(const Collection& _value_collection)
		{
			_Reset(false);
			val_collection = new Collection(_value_collection);
			type = COLLECTION;
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
			type = INTEGER;
		}
		void operator=(const double& _value_double)
		{
			_Reset();
			val_double = new double(_value_double);
			type = DOUBLE;
		}
		void operator=(const String& _value_string)
		{
			_Reset();
			val_string = new String(_value_string);
			type = STRING;
		}
		void operator=(const wchar_t _value_string[])
		{
			_Reset();
			val_string = new String(_value_string);
			type = STRING;
		}
		void operator=(const Collection& _value_collection)
		{
			_Reset();
			val_collection = new Collection(_value_collection);
			type = COLLECTION;
		}
		void* ValAnyPtr() const
		{
			if (val_int) 
				return val_int;
			if (val_double)
				return val_double;
			if (val_string)
				return val_string;
			if (val_collection)
				return val_collection;
			return nullptr;
		}
		bool operator==(const WeakValueType& _comp) const
		{
			void* _va1 = this->ValAnyPtr();
			void* _va2 = _comp.ValAnyPtr();
			return this->Type() == _comp.Type() &&
				(
					*(int*)(_va1) == *(int*)(_va2) ||
					*(double*)(_va1) == *(double*)(_va2) ||
					*(String*)(_va1) == *(String*)(_va2) || 
					*(StringList*)(_va1) == *(StringList*)(_va2)
				);
		}
		bool operator!=(const WeakValueType& _comp) const
		{
			return !(this->operator==(_comp));
		}
		explicit operator int() const
		{
			PTR_VALIDATE(val_int);
			return *val_int;
		}
		explicit operator double() const
		{
			PTR_VALIDATE(val_double);
			return *val_double;
		}
		explicit operator String() const
		{
			PTR_VALIDATE(val_string);
			return *val_string;
		}
		explicit operator Collection() const
		{
			PTR_VALIDATE(val_collection);
			return *val_collection;
		}
		virtual String ToString(int _style = 0) const override
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
			case COLLECTION:
				_ret += L"{";
				if (val_collection->empty())
				{
					_ret += L"}";
					break;
				}
				for (size_t _i = 0ull; _i < val_collection->size(); ++_i)
				{
					_ret += (*val_collection)[_i];
					if (_i != val_collection->size() - 1)
						_ret += L" , ";
				}
				_ret += L"}";
				break;
			}
			return _ret;
		}
	};
	

}