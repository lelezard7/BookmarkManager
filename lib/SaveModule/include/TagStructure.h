/**
* 
*/

#pragma once
#ifndef _TAG_STRUCTURE_
#define _TAG_STRUCTURE_

#include <string>
#include <map>
#include <vector>

class Attribute;

typedef unsigned int Tag_Flag;
typedef int SubTag_ID;

#define TF_EMPTY		0
#define TF_VALUE		1
#define TF_SUBTAGS		2


class Tag
{
	std::map<std::wstring, std::wstring> attributes_;
	std::map<SubTag_ID, Tag*> deferredSubTags_;
	std::vector<Tag> subTags_;
	std::wstring	 name_;
	std::wstring	 value_;
	Tag_Flag		 flag_;

public:
	Tag();
	Tag(const Tag& other);
	~Tag();

	void setName(std::wstring name);
	bool setFlag(Tag_Flag flag = TF_VALUE);
	void setValue(std::wstring value);
	bool addAttribute(std::wstring name, std::wstring value);
	bool addAttribute(const Attribute& attribute);
	bool addSubTag(const Tag& subTag);

	std::wstring getName() const	{	return name_;	}
	Tag_Flag getFlag() const		{	return flag_;	}
	std::wstring getValue() const	{	return value_;	}

	size_t attributesCount() const	{	return attributes_.size();	}
	size_t subTagsCount() const		{	return subTags_.size();		}

	Attribute getAttribute(size_t index) const;
	std::wstring getAttributeValue(std::wstring name) const;
	std::wstring getAttributeValue(size_t index) const;
	bool findAttribute(std::wstring name) const;

	Tag getSubTag(size_t index) const;
	bool findSubTag(const Tag& tag) const;

	void clear();

	Tag* createSubTag(SubTag_ID id);
	bool applyAllSubTags();
	bool applySubTag(SubTag_ID id);

	bool operator==(const Tag& other) const;
	bool operator!=(const Tag& other) const;
	void operator=(const Tag& other);
};



class Attribute
{
public:
	std::wstring name;
	std::wstring value;

	Attribute();
	Attribute(const Attribute& other);
	Attribute(std::wstring name, std::wstring value);
	~Attribute();

	void clear();

	bool operator==(const Attribute& other) const;
	bool operator!=(const Attribute& other) const;
	void operator=(const Attribute& other);
};

#endif
