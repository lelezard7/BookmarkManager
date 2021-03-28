/**
* 
*/

#pragma once
#ifndef _SAVE_MODULE_
#define _SAVE_MODULE_

#include <string>
#include <map>
#include <vector>

#define SAVEMODULE_VERSION			0001
#define SAVEMODULE_VERSIONNAME		(L"0.0.0.1")

#define TSF_VALUE					0
#define TSF_SUBTAGS					1

#define XMLFILE_WRITE				0
#define XMLFILE_READ				1




using Attributes = std::map<std::string, std::string>;


struct TagsPair
{
	std::string openingTag;
	std::string closingTag;
};

TagsPair createTagsPair(std::string tagName);







class TagStructure //TODO: Очищать память в деструкторе + по цепочке.
{
	int err = 1;
	std::string tag;
	Attributes attributes;
	bool flag;
	std::string value;
	std::vector<TagStructure*> subTags;
public:
	void setTag(std::string tag);
	std::string getTag();

	void addAttribute(std::string attribute, std::string attributeValue);
	std::string getAttribute(const int index, std::string what);
	std::string getAttribute(std::string attribute);

	void setFlag(bool flag);
	bool getFlag();

	void setValue(std::string value);
	std::string getValue();

	TagStructure* addSubTag(TagStructure*& subTags);
	int subTagSize();
	TagStructure* getSubTag(const int index);

	bool operator==(const int number);
	bool operator!=(const int number);

	TagStructure();
	TagStructure(int);
	TagStructure(TagStructure& other);


	friend bool openXmlFile(std::string, int);
	friend bool closeXmlFile(std::string);
	friend bool saveXmlFile(TagStructure&);
	friend TagStructure* readXmlFile();
	friend class TagPath;
};

bool openXmlFile(std::string fileName, int mode);
bool closeXmlFile(std::string fileName);
bool saveXmlFile(TagStructure& tagStructure);
TagStructure* readXmlFile();


#define TPF_VALUE				0x0001
#define TPF_FLAG				0x0002
#define TPF_TAG					0x0004
#define TPF_SUBTAGS				0x0008
#define TPF_ATTRIBUTES			0x0010


using SearchResult = std::vector<TagStructure*>;

//TODO: Не работает если в документе только 1 тег.
class TagPath //TODO: Очищать память в деструкторе.
{
	unsigned int flags_;
	SearchResult searchResult_;

	TagStructure* tagStructure_;
	TagStructure* currentTagStructure_;
	TagStructure* previousTagStructure_;

	bool checkTag(TagStructure& tagStructureFilter);
public:
	void setTagStructure(TagStructure& tagStructure); //TODO: Не обрабатывается ошибка если tagStructure_ не была задана.
	
	void setFlags(unsigned int flags);
	SearchResult search(TagStructure& tagStructureFilter);
	
	TagStructure getTag(int index);
	TagStructure getAllTag(int index);
	TagStructure getRootTag(int index);
};

#endif
