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

using Attributes = std::map<std::wstring, std::wstring>;
typedef bool Flag;
typedef int SubTag_ID;

#define TSF_VALUE					0
#define TSF_SUBTAGS					1


class Tag
{
	std::wstring name_;
	Attributes attributes_;
	Flag flag_;
	std::wstring value_;
	std::vector<Tag> subTags_;
	std::map<SubTag_ID, Tag*> deferredSubTags_;

public:
	Tag();
	Tag(const Tag& other);
	~Tag();

	void setName(const std::wstring name);
	void setFlag(const Flag flag);
	void setValue(const std::wstring value);
	bool addAttribute(const std::wstring name, const std::wstring value);
	bool addAttribute(const Attribute& attribute);
	void addSubTag(const Tag& subTag);

	std::wstring getName() const;
	Flag getFlag() const;
	std::wstring getValue() const;
	Attribute getAttribute(const size_t index) const;
	std::wstring getAttributeValue(const std::wstring name);
	std::wstring getAttributeValue(const size_t index) const;
	size_t attributesCount() const;
	Tag getSubTag(const size_t index) const;
	size_t subTagsCount() const;
	void clear();

	Tag* createSubTag(const SubTag_ID id);
	bool applySubTags(); //TODO: rename to applyAllSubTags
	bool applySubTag(const SubTag_ID id);

	bool operator==(const Tag& other) const;
	bool operator!=(const Tag& other) const;
	void operator=(const Tag& other);


	friend class XmlFile;
	friend class TagPath;
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

	bool operator==(const Attribute& other) const;
	bool operator!=(const Attribute& other) const;
	void operator=(const Attribute& other);
};

#endif
