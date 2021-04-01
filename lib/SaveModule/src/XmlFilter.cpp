#include "XmlFilter.h"


bool XmlFilter::compareTags(const Tag& filter, const Tag& target)
{
	if (flags_ & XFF_VALUE)
		if (filter.getValue() != target.getValue())
			return false;

	if (flags_ & XFF_FLAG)
		if (filter.getFlag() != target.getFlag())
			return false;

	if (flags_ & XFF_NAME)
		if (filter.getName() != target.getName())
			return false;

	if (flags_ & XFF_ATTRIBUTES) {

		if (filter.attributesCount() > target.attributesCount())
			return false;

		for (size_t i = 0; i < filter.attributesCount(); ++i) {

			Attribute _attribute = filter.getAttribute(i);
			if (!target.findAttribute(_attribute.name))
				return false;
		}
	}

	if (flags_ & XFF_SUBTAGS) {

		if (filter.subTagsCount() > target.subTagsCount())
			return false;

		for (size_t i = 0; i < filter.subTagsCount(); ++i)
			if (!target.findSubTag(filter.getSubTag(i)))
				return false;
	}

	return true;
}

SearchResult XmlFilter::search(Tag& nextTag)
{
	if (nextTag == Tag())
		return SearchResult();

	SearchResult _searchResult;
	Tag _currentTag = nextTag;

	if (compareTags(filter_, _currentTag))
		_searchResult.addTag(_currentTag);

	if (_currentTag.getFlag() == TF_VALUE)
		return _searchResult;

	for (int i = 0; i < _currentTag.subTagsCount(); ++i) {

		nextTag = _currentTag.getSubTag(i);
		_searchResult += search(nextTag);
	}

	return _searchResult;
}


Tag XmlFilter::getDataTag(const int requiredCounterValue, int currentCounterValue, Tag& nextTag) const
{
	if (nextTag == Tag())
		return Tag();

	if (nextTag.getFlag() == TF_VALUE && currentCounterValue == requiredCounterValue)
		return nextTag;

	if (nextTag.getFlag() == TF_VALUE) {
		currentCounterValue++;
		return Tag();
	}

	Tag _currentTag = nextTag;

	for (int i = 0; i < _currentTag.subTagsCount(); ++i)
	{
		nextTag = _currentTag.getSubTag(i);
		Tag _tag = getDataTag(requiredCounterValue, currentCounterValue, nextTag);

		if (_tag != Tag())
			return _tag;
	}

	return Tag();
}

Tag XmlFilter::getAnyTag(const int requiredCounterValue, int currentCounterValue, Tag& nextTag) const
{
	if (nextTag == Tag())
		return Tag();

	if (currentCounterValue == requiredCounterValue)
		return nextTag;

	currentCounterValue++;

	if (nextTag.getFlag() == TF_VALUE)
		return Tag();

	Tag _currentTag = nextTag;

	for (int i = 0; i < _currentTag.subTagsCount(); ++i)
	{
		nextTag = _currentTag.getSubTag(i);
		Tag _tag = getAnyTag(requiredCounterValue, currentCounterValue, nextTag);

		if (_tag != Tag())
			return _tag;
	}

	return Tag();
}

Tag XmlFilter::getMarkupTag(const int requiredCounterValue, int currentCounterValue, Tag& nextTag) const
{
	if (nextTag == Tag())
		return Tag();

	if (nextTag.getFlag() == TF_VALUE)
		return Tag();

	if (currentCounterValue == requiredCounterValue)
		return nextTag;

	currentCounterValue++;
	Tag _currentTag = nextTag;

	for (int i = 0; i < _currentTag.subTagsCount(); ++i)
	{
		nextTag = _currentTag.getSubTag(i);
		Tag _tag = getMarkupTag(requiredCounterValue, currentCounterValue, nextTag);

		if (_tag != Tag())
			return _tag;
	}

	return Tag();
}


XmlFilter::XmlFilter()
{
	flags_ = 0;
	target_ = Tag();
	filter_ = Tag();
}

XmlFilter::XmlFilter(const XmlFilter& other)
{
	*this = other;
}

XmlFilter::~XmlFilter()
{
	clear();
}


bool XmlFilter::setFlags(const unsigned int flags)
{
	if (flags == 0)
		return false;

	flags_ = flags;

	return true;
}

bool XmlFilter::setTarget(const Tag& target)
{
	if (target == Tag())
		return false;

	target_ = target;

	return true;
}

bool XmlFilter::setFilter(const Tag& filter)
{
	if (filter == Tag())
		return false;

	filter_ = filter;

	return true;
}


Tag XmlFilter::getTag(const int index, const Tag_Flag tagFlag) const
{
	if (tagFlag != TF_EMPTY && tagFlag != TF_VALUE && tagFlag != TF_SUBTAGS)
		return Tag();

	Tag _nextTag = target_;
	Tag _tag;

	switch (tagFlag)
	{
	case TF_EMPTY:		_tag = getAnyTag(index, 0, _nextTag);		break;
	case TF_VALUE:		_tag = getDataTag(index, 0, _nextTag);		break;
	case TF_SUBTAGS:	_tag = getMarkupTag(index, 0, _nextTag);	break;
	}

	return _tag;
}


SearchResult XmlFilter::search()
{
	if (flags_ == 0 || target_ == Tag() || filter_ == Tag())
		return SearchResult();

	Tag _nextTag = target_;
	SearchResult _searchResult = search(_nextTag);

	return _searchResult;
}

void XmlFilter::clear()
{
	flags_ = 0;
	target_.clear();
	filter_.clear();
}


bool XmlFilter::operator==(const XmlFilter& other) const
{
	return
		flags_ == other.flags_ &&
		target_ == other.target_ &&
		filter_ == other.filter_;
}

bool XmlFilter::operator!=(const XmlFilter& other) const
{
	return !(*this == other);
}

void XmlFilter::operator=(const XmlFilter& other)
{
	clear();

	flags_ = other.flags_;
	target_ = other.target_;
	filter_ = other.filter_;
}






SearchResult::SearchResult(const SearchResult& other)
{
	*this = other;
}

SearchResult::~SearchResult()
{
	clear();
}


void SearchResult::addTag(const Tag& tag)
{
	searchResult_.push_back(tag);
}

Tag SearchResult::getTag(const size_t index) const
{
	if (index >= searchResult_.size())
		return Tag();

	return searchResult_[index];
}


size_t SearchResult::size() const
{
	return searchResult_.size();
}

void SearchResult::clear()
{
	searchResult_.clear();
}


bool SearchResult::operator==(const SearchResult& other) const
{
	return (searchResult_ == other.searchResult_);
}

bool SearchResult::operator!=(const SearchResult& other) const
{
	return !(*this == other);
}


void SearchResult::operator=(const SearchResult& other)
{
	clear();

	searchResult_ = other.searchResult_;
}

void SearchResult::operator+=(const SearchResult& other)
{
	if (other == SearchResult())
		return;

	searchResult_.insert(searchResult_.end(), other.searchResult_.begin(), other.searchResult_.end());
}
