/**
* 
*/

#pragma once
#ifndef _SAVE_MODULE_
#define _SAVE_MODULE_

#include "TagStructure.h"
#include "XmlFilter.h"
#include <string>
#include <fstream>
#include <vector>

#define SAVEMODULE_VERSION			(0x00010000)
#define SAVEMODULE_VERSIONNAME		(L"0.1.0.0")


enum class OpenMode
{
	WRITE,
	READ,
	APPEND
};


class XmlFile
{
	using History = std::vector<std::wstring>;

	std::wfstream fileStream_;
	std::wstring fileName_;
	std::ios_base::openmode openMode_;

	wchar_t entityToSymbol(std::wstring entity) const;
	std::wstring symbolToEntity(wchar_t symbol) const;
	std::wstring convertAllSymbolsToEntities(std::wstring sourceText) const;
	std::wstring convertAllEntitiesToSymbols(std::wstring sourceText) const;
	std::wstring removeSpacesAndTabs(std::wstring sourceText) const;

	int write(const Tag& tag, int startingLevel);
	Tag read(History& history, std::wstring& xmlFileText) const;

	std::wstring searchTag(
		std::wstring sourceText,
		std::wstring* buffer = nullptr,
		bool* isAttribute = nullptr,
		bool* isClosingTag = nullptr
	) const;

	Attribute searchAttribute(
		std::wstring sourceText,
		std::wstring* buffer = nullptr,
		bool* isAttribute = nullptr
	) const;

	std::wstring searchValue(
		std::wstring sourceText,
		std::wstring* buffer = nullptr
	) const;

public:
	XmlFile();
	~XmlFile();

	bool open(std::wstring fileName, OpenMode openMode = OpenMode::READ);
	void close();

	int write(const Tag& tag);
	Tag read();
};

#endif
