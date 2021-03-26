/**
* 
*/

#pragma once
#ifndef _SAVE_MODULE_
#define _SAVE_MODULE_

#include <string>
#include <map>
#include <vector>

#define SAVEMODULE_VERSION		0001

#define TSF_VALUE				0
#define TSF_SUBTAGS				1

#define XMLFILE_WRITE			0
#define XMLFILE_READ			1




using Attributes = std::map<std::string, std::string>;


struct TagsPair
{
	std::string openingTag;
	std::string closingTag;
};

TagsPair createTagsPair(std::string tagName);







class TagStructure //TODO: Очищать память в деструкторе.
{
	//size_t index;
	std::string tag;
	Attributes attributes;
	bool flag;
	std::string value;
	std::vector<TagStructure*> subTags;
public:
	void setTag(std::string tag);
	void addAttribute(std::string attribute, std::string attributeValue);
	void setFlag(bool flag);
	void setValue(std::string value);
	TagStructure* addSubTag(TagStructure*& subTags);

	TagStructure();
	TagStructure(TagStructure& other);


	friend bool openXmlFile(std::string, int);
	friend bool closeXmlFile(std::string);
	friend bool saveXmlFile(TagStructure&);
	friend TagStructure* readXmlFile();
};

bool openXmlFile(std::string fileName, int mode);
bool closeXmlFile(std::string fileName);
bool saveXmlFile(TagStructure& tagStructure);
TagStructure* readXmlFile();

#endif
