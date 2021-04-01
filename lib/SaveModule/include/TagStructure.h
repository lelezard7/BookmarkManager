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

	void setName(const std::wstring name);
	bool setFlag(const Tag_Flag flag);
	void setValue(const std::wstring value);
	bool addAttribute(const std::wstring name, const std::wstring value);
	bool addAttribute(const Attribute& attribute);
	void addSubTag(const Tag& subTag);

	std::wstring getName() const;
	Tag_Flag getFlag() const;
	std::wstring getValue() const;

	Attribute getAttribute(const size_t index) const;
	std::wstring getAttributeValue(const std::wstring name);
	std::wstring getAttributeValue(const size_t index) const;
	size_t attributesCount() const;
	bool findAttribute(const std::wstring name) const;

	Tag getSubTag(const size_t index) const;
	size_t subTagsCount() const;
	bool findSubTag(const Tag& tag) const;

	void clear();

	Tag* createSubTag(const SubTag_ID id);
	bool applyAllSubTags();
	bool applySubTag(const SubTag_ID id);

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
	Attribute(const std::wstring name, const std::wstring value);
	~Attribute();

	void clear();

	bool operator==(const Attribute& other) const;
	bool operator!=(const Attribute& other) const;
	void operator=(const Attribute& other);
};

#endif
