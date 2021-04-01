/**
* 
*/

#pragma once
#ifndef _SAVE_MODULE_
#define _SAVE_MODULE_

#include "TagStructure.h"
#include "XmlFilter.h"
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
	using History = std::vector<std::wstring>;
	using Сonditions = std::vector<std::wstring>;

	std::wfstream fileStream_;
	std::wstring fileName_;
	std::ios_base::openmode openMode_;

	wchar_t entityToSymbol(const std::wstring essence) const;
	std::wstring symbolToEntity(const wchar_t symbol) const;
	std::wstring convertAllSymbolsToEntities(const std::wstring text) const;
	void clear();

	size_t write(const Tag& tag, int level); //TODO: check

	Tag XmlFile::read(History& history); //TODO: check
	int readXmlLine(Сonditions conditions, std::wstring& result); //TODO: refact
	std::wstring readXmlLine(std::wstring condition); //TODO: refact
	bool read_isSameLevel_check(); //TODO: refact

public:
	XmlFile();
	~XmlFile();

	bool open(const std::wstring fileName, const OpenMode openMode);
	bool close();

	bool write(const Tag& tag); //TODO: check
	Tag read(); //TODO: check
};

#endif
