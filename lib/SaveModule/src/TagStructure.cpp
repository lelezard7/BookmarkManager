#include "TagStructure.h"


Tag::Tag()
{
	name_ = L"";
	flag_ = TF_VALUE;
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


void Tag::setName(std::wstring name)
{
	name_ = name;
}

bool Tag::setFlag(Tag_Flag flag)
{
	if (flag != TF_VALUE && flag != TF_SUBTAGS)
		return false;

	flag_ = flag;

	return true;
}

void Tag::setValue(std::wstring value)
{
	value_ = value;
}

bool Tag::addAttribute(std::wstring name, std::wstring value)
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

bool Tag::addSubTag(const Tag& subTag)
{
	if (subTag == Tag())
		return false;

	subTags_.push_back(subTag);
}

Attribute Tag::getAttribute(size_t index) const
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

std::wstring Tag::getAttributeValue(std::wstring name) const
{
	auto _iterator = attributes_.find(name);

	if (_iterator == attributes_.end())
		return L"";

	return _iterator->second;
}

std::wstring Tag::getAttributeValue(size_t index) const
{
	if (index >= attributes_.size())
		return L"";

	auto _iterator = attributes_.begin();
	std::advance(_iterator, index);

	return _iterator->second;
}

bool Tag::findAttribute(std::wstring name) const
{
	if (attributes_.find(name) != attributes_.end())
		return true;

	return false;
}

Tag Tag::getSubTag(size_t index) const
{
	if (index >= subTags_.size()) {
		Tag _tag;
		return _tag;
	}

	return subTags_[index];
}

bool Tag::findSubTag(const Tag& tag) const
{
	for (auto i : subTags_)
		if (tag == i)
			return true;

	return false;
}


void Tag::clear()
{
	applyAllSubTags();
	subTags_.clear();

	attributes_.clear();
	name_ = L"";
	flag_ = TF_VALUE;
	value_ = L"";
}


Tag* Tag::createSubTag(SubTag_ID id)
{
	if (deferredSubTags_.find(id) != deferredSubTags_.end())
		return nullptr;

	Tag* _tag = new Tag;
	deferredSubTags_.emplace(std::make_pair(id, _tag));

	return _tag;
}

bool Tag::applyAllSubTags()
{
	if (deferredSubTags_.size() == 0)
		return false;

	for (auto i : deferredSubTags_)
	{
		i.second->applyAllSubTags();
		subTags_.push_back(*i.second);
		delete i.second;
	}
	deferredSubTags_.clear();

	return true;
}

bool Tag::applySubTag(SubTag_ID id)
{
	if (deferredSubTags_.find(id) == deferredSubTags_.end())
		return false;

	deferredSubTags_[id]->applyAllSubTags();
	subTags_.push_back(*deferredSubTags_[id]);

	delete deferredSubTags_[id];
	deferredSubTags_.erase(deferredSubTags_.find(id));

	return true;
}


bool Tag::operator==(const Tag& other) const
{
	return
		attributes_ == other.attributes_ &&
		subTags_ == other.subTags_ &&
		value_ == other.value_ &&
		flag_ == other.flag_ &&
		name_ == other.name_;
}

bool Tag::operator!=(const Tag& other) const
{
	return !(*this == other);
}

void Tag::operator=(const Tag& other)
{
	clear();

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

Attribute::Attribute(std::wstring name, std::wstring value)
{
	this->name = name;
	this->value = value;
}

Attribute::~Attribute()
{
	clear();
}


void Attribute::clear()
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
	clear();

	name = other.name;
	value = other.value;
}
