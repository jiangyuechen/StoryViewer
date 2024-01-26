#pragma once

#include "Link.h"
#include "Object.h"
#include "basic.h"
#include "ValueType.h"

#ifndef _CHARACTER
#define _CHARACTER
#endif

#define NIL nullptr

namespace StoryViewer
{
	class WeakValueType;
	class CharacterAttributeAdder;
#ifdef _USE_CHARACTER_LINKER_OPERATOR
	class CharacterLinker;
#endif
	class Story;
	class Character;
	class MultiCharacter;
	typedef std::vector<StoryViewer::Character*> CharacterCollection;
	typedef std::pair<std::wstring, WeakValueType> Attribute;
	typedef std::vector<std::pair<String, WeakValueType>> AttributeList;
	
	class Character : public Object
	{
	protected:
		String name;
		StringList aka;
		AttributeList attributes;

	public:
		Character();
		Character(
			const String &_name,
			Nullable<StringList> _p_aka = nullptr,
			Nullable<AttributeList> _p_attributes = nullptr);

		virtual ~Character();

		String &Name();

		StringList &Aka();

		AttributeList &Attributes();

		bool ContainKeyValue(const Attribute &_attrib) const;

		void AddAttribute(const Attribute &_p_attrib);

		bool RemoveAttribute(const String &_key);

		Nullable<Attribute> FindAttribute(const String &_key) const;
		Nullable<WeakValueType> GetValue(const String &_key) const;

		bool AlterAttribute(const Attribute &_attrib);

		void ClearAttribute();

		bool AddAKA(const String &_aka);

		bool ContainAKA(const String &_aka);
		bool ContainKey(const String &_key) const;
		
		// Override
		virtual String ToString() const override;


#ifdef _USE_CHARACTER_LINKER_OPERATOR
		CharacterLinker operator[](const String &_desc);
#endif
		// void operator[](const String& _attr_name);

		void operator>>(Story &_tar_story);
		Character &operator<<(const String &_new_aka);
		Character &operator<<(const Attribute &_new_attr);
		CharacterAttributeAdder operator[](const String& _new_key);

		// std::vector<SubCharacter *> sub_characters;
	};
#ifdef _USE_CHARACTER_LINKER_OPERATOR
	class CharacterLinker : public Object
	{
	protected:
		Character *main;
		String description;

	private:
		Link<Character, Character> _MakeLink(Character &_sub, LINKTYPE _type) const;

	public:
		CharacterLinker();
		CharacterLinker(Character *_main, const String &_desc);
		~CharacterLinker();

		// CharacterLinker operator[](const String& _desc);
		Link<Character, Character> operator>>(Character &_main) const;
		Link<Character, Character> operator>(Character &_main) const;
	};
#endif
	class CharacterAttributeAdder : public Object
	{
	protected:
		mutable Character* tar_char;
		String key;
	public:
		CharacterAttributeAdder(Character* _tar_char, const String& _key);
		void operator=(WeakValueType val);

		virtual String ToString() const override;
	};

	class MultiCharacter : public Character
	{
		CharacterCollection sub_characters;
	public:
		MultiCharacter();
		MultiCharacter(
			const String& _name,
			Nullable<StringList> _p_aka = nullptr,
			Nullable<AttributeList> _p_attributes = nullptr,
			Nullable<CharacterCollection> _p_sub_characters = nullptr);
		MultiCharacter(const Character&);
		~MultiCharacter();
		void SetAsSubCharacter(Character&);
		CharacterCollection& SubCharacters();
		Nullable<Character> Getter(size_t _code) const;
		Nullable<Character> operator[](size_t _code) const;
		size_t Count() const;
		void operator+=(Character&);

		virtual String ToString() const override;
	};
}