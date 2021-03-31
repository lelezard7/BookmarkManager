#include "TagStructure.h"
#include <fstream>


Tag::Tag()
{
	name_ = L"";
	flag_ = TSF_VALUE;
	value_ = L"";
}

Tag::Tag(const Tag& other)
{
	*this = other;
}

Tag::~Tag()
{
	clear();
}


void Tag::setName(const std::wstring name)
{
	name_ = name;
}

void Tag::setFlag(const Flag flag)
{
	flag_ = flag;
}

void Tag::setValue(const std::wstring value)
{
	value_ = value;
}

bool Tag::addAttribute(const std::wstring name, const std::wstring value)
{
	if (name.size() == 0)
		return false;

	if (attributes_.find(name) != attributes_.end())
		return false;

	attributes_.emplace(std::make_pair(name, value));

	return true;
}

bool Tag::addAttribute(const Attribute& attribute)
{
	if (attribute.name.size() == 0)
		return false;

	if (attributes_.find(attribute.name) != attributes_.end())
		return false;

	attributes_.emplace(std::make_pair(attribute.name, attribute.value));

	return true;
}

void Tag::addSubTag(const Tag& subTag)
{
	subTags_.push_back(subTag);
}


std::wstring Tag::getName() const
{
	return name_;
}

Flag Tag::getFlag() const
{
	return flag_;
}

std::wstring Tag::getValue() const
{
	return value_;
}

Attribute Tag::getAttribute(const size_t index) const
{
	Attribute _attribute;

	if (index >= attributes_.size())
		return _attribute;

	auto _iterator = attributes_.begin();
	std::advance(_iterator, index);

	_attribute.name = _iterator->first;
	_attribute.value = _iterator->second;

	return _attribute;
}

std::wstring Tag::getAttributeValue(const std::wstring name)
{
	if (attributes_.find(name) == attributes_.end())
		return L"";

	return attributes_[name];
}

std::wstring Tag::getAttributeValue(const size_t index) const
{
	if (index >= attributes_.size())
		return L"";

	auto _iterator = attributes_.begin();
	std::advance(_iterator, index);

	return _iterator->second;
}

size_t Tag::attributesCount() const
{
	return attributes_.size();
}

Tag Tag::getSubTag(const size_t index) const
{
	if (index >= subTags_.size()) {
		Tag _tag;
		return _tag;
	}

	return subTags_[index];
}

size_t Tag::subTagsCount() const
{
	return subTags_.size();
}

void Tag::clear()
{
	applySubTags();
	subTags_.clear();

	attributes_.clear();
	name_ = L"";
	flag_ = TSF_VALUE;
	value_ = L"";
}


Tag* Tag::createSubTag(const SubTag_ID id)
{
	if (deferredSubTags_.find(id) != deferredSubTags_.end())
		return nullptr;

	Tag* _tag = new Tag;
	deferredSubTags_.emplace(std::make_pair(id, _tag));

	return _tag;
}

bool Tag::applySubTags()
{
	if (deferredSubTags_.size() == 0)
		return false;

	for (auto i : deferredSubTags_)
	{
		i.second->applySubTags();
		subTags_.push_back(*i.second);
		delete i.second;
	}
	deferredSubTags_.clear();

	return true;
}

bool Tag::applySubTag(const SubTag_ID id)
{
	if (deferredSubTags_.find(id) == deferredSubTags_.end())
		return false;

	deferredSubTags_[id]->applySubTags();
	subTags_.push_back(*deferredSubTags_[id]);

	delete deferredSubTags_[id];
	deferredSubTags_.erase(deferredSubTags_.find(id));

	return true;
}


bool Tag::operator==(const Tag& other) const
{
	return (attributes_ == other.attributes_ &&
		subTags_ == other.subTags_ &&
		value_ == other.value_ &&
		flag_ == other.flag_ &&
		name_ == other.name_);
}

bool Tag::operator!=(const Tag& other) const
{
	return !(*this == other);
}

void Tag::operator=(const Tag& other)
{
	name_ = other.name_;
	flag_ = other.flag_;
	value_ = other.value_;
	subTags_ = other.subTags_;
	attributes_ = other.attributes_;
}








Attribute::Attribute()
{
	name = L"";
	value = L"";
}

Attribute::Attribute(const Attribute& other)
{
	name = other.name;
	value = other.value;
}

Attribute::Attribute(const std::wstring name, const std::wstring value)
{
	this->name = name;
	this->value = value;
}

Attribute::~Attribute()
{
	name = L"";
	value = L"";
}

bool Attribute::operator==(const Attribute& other) const
{
	return (name == other.name && value == other.value);
}

bool Attribute::operator!=(const Attribute& other) const
{
	return !(*this == other);
}

void Attribute::operator=(const Attribute& other)
{
	name = other.name;
	value = other.value;
}
