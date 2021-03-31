#include "SaveModule.h"
#include <Windows.h>
#include <vector>

std::ifstream XmlFile::file_in;



wchar_t XmlFile::entityToSymbol(const std::wstring essence) const
{
	if (essence == L"lt")			return '<';
	else if (essence == L"gt")		return '>';
	else if (essence == L"amp")		return '&';
	else if (essence == L"apos")	return '\'';
	else if (essence == L"quot")	return '\"';

	return '\0';
}


std::wstring XmlFile::symbolToEntity(const wchar_t symbol) const
{
	switch (symbol)
	{
	case '<':	return L"lt";
	case '>':	return L"gt";
	case '&':	return L"amp";
	case '\'':	return L"apos";
	case '\"':	return L"quot";

	default:	return L"";
	}
}


std::wstring XmlFile::convertAllSymbolsToEntities(const std::wstring text) const
{
	if (text.size() == 0)
		return L"";

	std::wstring _newText;

	for (size_t i = 0; i < text.size(); ++i)
	{
		std::wstring newEssence = symbolToEntity(text[i]);
		if (newEssence != L"") {
			_newText += L"&" + newEssence + L";";
		}
		else {
			_newText += text[i];
		}
	}

	return _newText;
}

size_t XmlFile::write(const Tag& tag, int level)
{
	fileStream_.imbue(std::locale("en_US.UTF-8")); //TODO: ???
	int _level = level;
	std::wstring _openingTag = L"";

	_openingTag = L"<" + tag.getName();

	if (tag.attributesCount() != 0)
	{
		Attribute _attribute;
		std::wstring _convertedValue;
		for (size_t i = 0; i < tag.attributesCount(); ++i)
		{
			_attribute = tag.getAttribute(i);
			_convertedValue = convertAllSymbolsToEntities(_attribute.value);
			_openingTag += L" " + _attribute.name + L"=\"" + _convertedValue + L"\"";
		}
	}

	fileStream_ << _openingTag << L">";

	if (tag.getFlag() == TSF_VALUE)
	{
		std::wstring _convertedValue = convertAllSymbolsToEntities(tag.getValue());
		fileStream_ << _convertedValue + L"</" + tag.getName() + L">\n";

		return _level;
	}
	else
	{
		_level++;
		fileStream_ << L"\n";

		for (size_t i = 0; i < tag.subTagsCount(); ++i)
		{
			for (size_t j = 0; j < _level; ++j)
				fileStream_ << L"\t";

			_level = write(tag.getSubTag(i), _level);
		}
		_level--;

		for (size_t i = 0; i < _level; ++i)
			fileStream_ << L"\t";

		fileStream_ << L"</" + tag.getName() + L">\n";

		return _level;
	}
}

void XmlFile::clear()
{
	fileName_.clear();
	openMode_ = NULL;
}


XmlFile::XmlFile()
{
	fileName_.clear();
	openMode_ = NULL;
}

XmlFile::~XmlFile()
{
	close();
}


bool XmlFile::open(const std::wstring fileName, const OpenMode openMode)
{
	switch (openMode)
	{
	case OpenMode::WRITE:	openMode_ = std::fstream::out;						break;
	case OpenMode::READ:	openMode_ = std::fstream::in;						break;
	case OpenMode::APPEND:	openMode_ = std::fstream::out | std::fstream::app;	break;
	}

	fileName_ = fileName;
	fileStream_.open(fileName_, openMode_);

	if (!fileStream_.is_open()) {
		close();
		return false;
	}

	return true;
}

bool XmlFile::close()
{
	fileStream_.close();
	clear();

	return true;
}


bool XmlFile::write(const Tag& tag)
{
	int _level = 0;
	write(tag, _level);

	return true;
}





















std::wstring XmlFile::readXmlLine(std::wstring condition)
{
	char symbol;
	std::wstring result;

	int conditionSize = condition.size();
	if (conditionSize == 0)
		return L"";

	while (file_in.get(symbol))
	{
		if (conditionSize == 1) {
			if (symbol == condition[0])
				return result;
		}
		else if (symbol == condition[0])
		{
			std::wstring buffer = L"";
			for (int i = 0; i < conditionSize; ++i)
			{
				if (condition[i] == symbol && i == conditionSize - 1)
					return result;

				if (condition[i] != symbol)
				{
					result += buffer;
					break;
				}

				buffer += symbol;
				file_in.get(symbol);
			}
		}

		if (symbol == '&')
		{
			std::wstring buf = readXmlLine(L";");
			buf = entityToSymbol(buf);
			result += buf;
			continue;
		}
		result += symbol;
	}

	return L"";
}


int XmlFile::readXmlLine(std::vector<std::wstring> conditions, std::wstring& result)
{
	char symbol;

	if (conditions.size() == 0)
		return -1;

	for (auto i : conditions)
		if (i.size() == 0)
			return -1;

	while (file_in.get(symbol))
	{
		int ind = 0;
		for (auto i : conditions)
		{
			if (i.size() == 1) {
				if (symbol == i[0])
					return ind;
			}
			else if (symbol == i[0])
			{
				std::wstring buffer = L"";
				for (int j = 0; j < i.size(); ++j)
				{
					if (i[j] == symbol && j == i.size() - 1)
						return ind;

					if (i[j] != symbol)
					{
						result += buffer;
						break;
					}

					buffer += symbol;
					file_in.get(symbol);
				}
			}
			ind++;
		}

		if (symbol == '&')
		{
			std::wstring buf = readXmlLine(L";");
			buf = entityToSymbol(buf);
			result += buf;
			continue;
		}
		result += symbol;
	}

	return -1;
}

bool XmlFile::checkLevel()
{
	char symbol;
	bool result = 0;
	while (file_in.get(symbol))
	{
		if (symbol == '\n' || symbol == '\t')
			continue;

		if (symbol == '<')
		{
			file_in.get(symbol);
			if (symbol == '/')
				result = false;
			else
				result = true;

			file_in.unget();
			break;
		}
	}
	file_in.unget();
	return result;
}



static bool isSameLevel = false;

Tag* XmlFile::read()
{
	static std::vector<std::wstring> history;
	char symbol;
	Tag* tagStructure = new Tag;

	while (file_in.get(symbol))
	{
		if (symbol == '<')
		{
			//tag
			std::vector<std::wstring> conditions;
			conditions.push_back(L" ");
			conditions.push_back(L">");
			int res = readXmlLine(conditions, tagStructure->name_);
			history.push_back(tagStructure->name_);


			if (res == -1)
				return 0;

			if (res == 0)
			{
				//attributes
				std::wstring attribute;
				std::wstring attributeValue;
				while (file_in.get(symbol))
				{
					if (symbol == '>')
						break;

					file_in.unget();

					attribute = readXmlLine(L"=\"");
					attributeValue = readXmlLine(L"\"");
					tagStructure->attributes_.emplace(std::make_pair(attribute, attributeValue));

					attribute.clear();
					attributeValue.clear();
				}
			}

			//value
			while (file_in.get(symbol))
			{
				if (symbol == '\n' || symbol == '\t')
					continue;

				if (symbol == '<')
				{
					do {
						tagStructure->flag_ = TSF_SUBTAGS;
						file_in.unget();
						tagStructure->subTags_.push_back(*read());
					} while (isSameLevel);

					readXmlLine(L"</");
					std::wstring closingTag = readXmlLine(L">");
					if (closingTag != history.back())
						return 0;

					history.pop_back();
					goto END;
				}

				file_in.unget();
				tagStructure->flag_ = TSF_VALUE;
				tagStructure->value_ = readXmlLine(L"</");

				std::wstring closingTag = readXmlLine(L">");
				if (closingTag != history.back())
					return 0;

				history.pop_back();
				goto END;
			}
		}
	}
	END:

	isSameLevel = checkLevel();

	return tagStructure;
}





void TagPath::setTagStructure(Tag& tagStructure)
{
	tagStructure_ = &tagStructure;
	currentTagStructure_ = &tagStructure;
	previousTagStructure_ = &tagStructure;;
}


static int _index = 0;
Tag TagPath::getTag(int index)
{
	if (currentTagStructure_->flag_ == TSF_VALUE && _index == index)
	{
		return *currentTagStructure_;
	}
	else
	{
		if (currentTagStructure_->flag_ == TSF_VALUE)
		{
			_index++;
			currentTagStructure_ = previousTagStructure_;
			Tag f;
			return f;// return NULL
		}

		previousTagStructure_ = currentTagStructure_;
		int subTagsCount = currentTagStructure_->subTags_.size();

		for (int i = 0; i < subTagsCount; ++i)
		{
			currentTagStructure_ = &currentTagStructure_->subTags_[i];
			Tag result = getTag(index);
			Tag f;
			if (result != f) {// != NULL
				currentTagStructure_ = tagStructure_;
				_index = 0;
				return result;
			}
		}

		currentTagStructure_ = tagStructure_;
		_index = 0;
		Tag f;
		return f;// return NULL
	}
}

Tag TagPath::getAllTag(int index)
{
	if (_index == index)
		return *currentTagStructure_;


	if (currentTagStructure_->flag_ == TSF_VALUE)
	{
		currentTagStructure_ = previousTagStructure_;
		Tag f;
		return f;// return NULL
	}

	previousTagStructure_ = currentTagStructure_;
	int subTagsCount = currentTagStructure_->subTags_.size();

	for (int i = 0; i < subTagsCount; ++i)
	{
		currentTagStructure_ = &currentTagStructure_->subTags_[i];
		_index++;
		Tag result = getAllTag(index);

		Tag f;
		if (result != f) {// != NULL
			currentTagStructure_ = tagStructure_;
			_index = 0;
			return result;
		}
	}

	currentTagStructure_ = tagStructure_;
	_index = 0;

	Tag f;
	return f;// return NULL
}

Tag TagPath::getRootTag(int index)
{
	if (currentTagStructure_->flag_ == TSF_VALUE)
	{
		currentTagStructure_ = previousTagStructure_;

		Tag f;
		return f;// return NULL
	}

	if (_index == index)
		return *currentTagStructure_;


	_index++;

	previousTagStructure_ = currentTagStructure_;
	int subTagsCount = currentTagStructure_->subTags_.size();

	for (int i = 0; i < subTagsCount; ++i)
	{
		currentTagStructure_ = &currentTagStructure_->subTags_[i];
		Tag result = getRootTag(index);

		Tag f;
		if (result != f) {// != NULL
			currentTagStructure_ = tagStructure_;
			_index = 0;
			return result;
		}
	}

	currentTagStructure_ = tagStructure_;
	_index = 0;

	Tag f;
	return f;// return NULL
}

void TagPath::setFlags(unsigned int flags)
{
	flags_ = flags;
}

SearchResult TagPath::search(Tag& tagStructureFilter)
{
	SearchResult localsearchResult;

	if (checkTag(tagStructureFilter))
	{
		//searchResult_.push_back(currentTagStructure_);
		localsearchResult.push_back(currentTagStructure_);
	}


	if (currentTagStructure_->flag_ == TSF_VALUE)
	{
		currentTagStructure_ = previousTagStructure_;
		return localsearchResult;
	}

	Tag* previousTagStructure = currentTagStructure_;
	previousTagStructure_ = currentTagStructure_;
	int subTagsCount = currentTagStructure_->subTags_.size();

	for (int i = 0; i < subTagsCount; ++i)
	{
		currentTagStructure_ = previousTagStructure;
		currentTagStructure_ = &currentTagStructure_->subTags_[i];
		SearchResult result = search(tagStructureFilter);
		localsearchResult.insert(localsearchResult.end(), result.begin(), result.end());
	}

	currentTagStructure_ = tagStructure_;
	_index = 0;

	//localsearchResult = searchResult_;
	//searchResult_.clear();

	return localsearchResult;
}

bool TagPath::checkTag(Tag& tagStructureFilter)//TODO: Проверять наличие указанных значений.
{
	if (flags_ & TPF_VALUE)
		if (tagStructureFilter.value_ != currentTagStructure_->value_)
			return 0;

	if (flags_ & TPF_FLAG)
		if (tagStructureFilter.flag_ != currentTagStructure_->flag_)
			return 0;

	if (flags_ & TPF_TAG)
		if (tagStructureFilter.name_ != currentTagStructure_->name_)
			return 0;

	if (flags_ & TPF_ATTRIBUTES)
	{
		if (tagStructureFilter.attributes_.size() > currentTagStructure_->attributes_.size())
			return 0;

		auto _iterator = tagStructureFilter.attributes_.begin();
		for (; _iterator != tagStructureFilter.attributes_.end(); ++_iterator)
		{
			if (currentTagStructure_->attributes_.find(_iterator->first) == currentTagStructure_->attributes_.end())
				return 0;
		}
	}

	if (flags_ & TPF_SUBTAGS)
	{
		if (tagStructureFilter.subTags_.size() > currentTagStructure_->subTags_.size())
			return 0;

		bool isEquals = true;

		for (auto i : tagStructureFilter.subTags_)
		{
			for (int j = 0; j < currentTagStructure_->subTags_.size(); ++j)
			{
				if (j == currentTagStructure_->subTags_.size() - 1)
				{
					isEquals = false;
					break;
				}
			}
		}

		if (isEquals == false)
			return 0;
	}

	return true;
}
