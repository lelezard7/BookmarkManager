/**
*
*/

#pragma once
#ifndef _XML_FILTER_
#define _XML_FILTER_

#include "TagStructure.h"
#include <vector>

class SearchResult;

#define XFF_VALUE				0x0001
#define XFF_FLAG				0x0002
#define XFF_NAME				0x0004
#define XFF_SUBTAGS				0x0008
#define XFF_ATTRIBUTES			0x0010


class XmlFilter //TODO: Не работает если в документе только 1 тег.
{
	unsigned int flags_;
	Tag target_;
	Tag filter_;

	bool compareTags(const Tag& filter, const Tag& target);
	SearchResult search(Tag& nextTag);

	Tag getDataTag(const int requiredCounterValue, int currentCounterValue, Tag& nextTag) const;
	Tag getAnyTag(const int requiredCounterValue, int currentCounterValue, Tag& nextTag) const;
	Tag getMarkupTag(const int requiredCounterValue, int currentCounterValue, Tag& nextTag) const;

public:
	XmlFilter();
	XmlFilter(const XmlFilter& other);
	~XmlFilter();

	bool setFlags(const unsigned int flags);
	bool setTarget(const Tag& target);
	bool setFilter(const Tag& filter);

	Tag getTag(const int index, const Tag_Flag tagFlag) const;

	SearchResult search();
	void clear();

	bool operator==(const XmlFilter& other) const;
	bool operator!=(const XmlFilter& other) const;
	void operator=(const XmlFilter& other);
};



class SearchResult
{
	std::vector<Tag> searchResult_;

public:
	SearchResult() {};
	SearchResult(const SearchResult& other);
	~SearchResult();

	void addTag(const Tag& tag);
	Tag getTag(const size_t index) const;

	size_t size() const;
	void clear();

	bool operator==(const SearchResult& other) const;
	bool operator!=(const SearchResult& other) const;

	void operator=(const SearchResult& other);
	void operator+=(const SearchResult& other);
};

#endif
