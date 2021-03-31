/**
* 
*/

#pragma once
#ifndef _SAVE_MODULE_
#define _SAVE_MODULE_ //TODO: Сделать wstring.

#include "TagStructure.h"
#include <string>
#include <map>
#include <fstream>
#include <memory>


#define SAVEMODULE_VERSION			0001
#define SAVEMODULE_VERSIONNAME		(L"0.0.0.1")


enum class OpenMode
{
	WRITE,
	READ,
	APPEND
};





class XmlFile
{
	std::wfstream fileStream_;
	std::wstring fileName_;
	std::ios_base::openmode openMode_;

	wchar_t entityToSymbol(const std::wstring essence) const;
	std::wstring symbolToEntity(const wchar_t symbol) const;

	std::wstring convertAllSymbolsToEntities(const std::wstring text) const;
	size_t write(const Tag& tag, int level);
	void clear();

public:
	XmlFile();
	~XmlFile();

	bool open(const std::wstring fileName, const OpenMode openMode);
	bool close();

	bool write(const Tag& tag);

















private:



	



	static std::ifstream file_in;
	int readXmlLine(std::vector<std::wstring> conditions, std::wstring& result);
	std::wstring readXmlLine(std::wstring condition);
	bool checkLevel();
	

public:


	





	Tag* read();

};








#define TPF_VALUE				0x0001
#define TPF_FLAG				0x0002
#define TPF_TAG					0x0004
#define TPF_SUBTAGS				0x0008
#define TPF_ATTRIBUTES			0x0010


using SearchResult = std::vector<Tag*>;

//TODO: Не работает если в документе только 1 тег.
class TagPath //TODO: Очищать память в деструкторе.
{
	unsigned int flags_;
	SearchResult searchResult_;

	Tag* tagStructure_;
	Tag* currentTagStructure_;
	Tag* previousTagStructure_;

	bool checkTag(Tag& tagStructureFilter);


public:
	void setTagStructure(Tag& tagStructure); //TODO: Не обрабатывается ошибка если tagStructure_ не была задана.
	
	void setFlags(unsigned int flags);
	SearchResult search(Tag& tagStructureFilter);
	
	Tag getTag(int index);
	Tag getAllTag(int index);
	Tag getRootTag(int index);
};

#endif
