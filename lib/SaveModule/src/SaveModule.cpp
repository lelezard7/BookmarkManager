#include "SaveModule.h"


wchar_t XmlFile::entityToSymbol(std::wstring entity) const
{
	if (entity == L"lt")			return '<';
	else if (entity == L"gt")		return '>';
	else if (entity == L"amp")		return '&';
	else if (entity == L"apos")		return '\'';
	else if (entity == L"quot")		return '\"';

	return '\0';
}

std::wstring XmlFile::symbolToEntity(wchar_t symbol) const
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

std::wstring XmlFile::convertAllSymbolsToEntities(std::wstring sourceText) const
{
	if (sourceText.size() == 0)
		return L"";

	std::wstring _newText;

	for (auto i : sourceText) {
		std::wstring _entity = symbolToEntity(i);

		if (_entity != L"")
			_newText += L"&" + _entity + L";";
		else
			_newText += i;
	}

	return _newText;
}

std::wstring XmlFile::convertAllEntitiesToSymbols(std::wstring sourceText) const
{
	if (sourceText.size() == 0)
		return L"";

	bool _isEntity = false;
	std::wstring _entity;
	std::wstring _newText;

	for (auto i : sourceText) {

		if (i == '&') {
			_isEntity = true;

			continue;
		}

		if (_isEntity) {
			if (i == ';') {
				_isEntity = false;
				_newText += entityToSymbol(_entity);
				_entity.clear();
				continue;
			}

			_entity += i;
		}
		else
			_newText += i;
	}

	if (_isEntity)
		return L"";

	return _newText;
}

std::wstring XmlFile::removeSpacesAndTabs(std::wstring sourceText) const
{
	if (sourceText.size() == 0)
		return L"";

	size_t _sourceTextSize = sourceText.size();
	for (size_t i = 0; i < _sourceTextSize; ++i) {

		if (sourceText[0] == '\t' || sourceText[0] == ' ')
			sourceText.erase(0, 1);
		else
			break;
	}

	return sourceText;
}


int XmlFile::write(const Tag& tag, int startingLevel)
{
	if(startingLevel < 0)
		return -1;

	if (tag.getName() == L"")
		return -1;

	std::wstring _openingTag = L"<" + tag.getName();

	size_t _attributesCount = tag.attributesCount();
	if (_attributesCount != 0) {

		Attribute _attribute;

		for (size_t i = _attributesCount - 1; i >= 0 && i <= _attributesCount - 1; --i) {
			_attribute = tag.getAttribute(i);
			_attribute.value = convertAllSymbolsToEntities(_attribute.value);
			_openingTag += L" " + _attribute.name + L"=\"" + _attribute.value + L"\"";
		}
	}

	for (size_t i = 0; i < startingLevel; ++i)
		fileStream_ << '\t';

	fileStream_ << _openingTag << L">";
	int _level = startingLevel;

	if (tag.getFlag() == TF_VALUE) {
		std::wstring _convertedValue = convertAllSymbolsToEntities(tag.getValue());
		fileStream_ << _convertedValue + L"</" + tag.getName() + L">\n";

		return _level;
	}
	else {
		_level++;
		fileStream_ << L"\n";

		for (size_t i = 0; i < tag.subTagsCount(); ++i) {
			_level = write(tag.getSubTag(i), _level);

			if (_level == -1)
				return -1;
		}

		_level--;

		for (size_t i = 0; i < _level; ++i)
			fileStream_ << L"\t";

		fileStream_ << L"</" + tag.getName() + L">\n";

		return _level;
	}
}

Tag XmlFile::read(History& history, std::wstring& xmlFileText) const
{
	if (xmlFileText.size() == 0)
		return Tag();

	Tag _tag;
	bool _isAttribute = false;

	//tag name
	std::wstring _tagName = searchTag(xmlFileText, &xmlFileText, &_isAttribute);
	if (_tagName != L"") {
		history.push_back(_tagName);
		_tag.setName(_tagName);
	}
	else {
		return Tag();
	}

	//attributes
	while (_isAttribute) {
		Attribute _attribute = searchAttribute(xmlFileText, &xmlFileText, &_isAttribute);

		if (_attribute == Attribute())
			return Tag();

		_attribute.value = convertAllEntitiesToSymbols(_attribute.value);

		if (!_tag.addAttribute(_attribute)) {
			return Tag();
		}
	}

	while (true)
	{
		//value
		if (xmlFileText[0] != '<') {
			std::wstring _value = searchValue(xmlFileText, &xmlFileText);

			if (_value == L"")
				return Tag();

			_tag.setFlag(TF_VALUE);

			_value = convertAllEntitiesToSymbols(_value);
			_tag.setValue(_value);
		}

		bool _isClosingTag = false;

		_tagName = searchTag(xmlFileText, nullptr, nullptr, &_isClosingTag);
		if (_tagName == L"")
			return Tag();

		//sub tag
		if (!_isClosingTag) {
			_tag.setFlag(TF_SUBTAGS);

			Tag _subTag = read(history, xmlFileText);
			if (_subTag == Tag())
				return Tag();
			else
				_tag.addSubTag(_subTag);
		}

		//closing tag
		if (_isClosingTag)
		{
			if (_tagName == history.back() && _tagName == _tag.getName()) {
				searchTag(xmlFileText, &xmlFileText);
				history.pop_back();

				return _tag;
			}
			else
				return Tag();
		}
	}
}

std::wstring XmlFile::searchTag(std::wstring sourceText, std::wstring* buffer, bool* isAttribute, bool* isClosingTag) const
{
	sourceText = removeSpacesAndTabs(sourceText);

	if (sourceText.size() == 0)
		return L"";

	if (sourceText[0] != '<') {
		return L"";
	}
	else {
		sourceText.erase(0, 1);
	}

	if (sourceText[0] == ' ' || sourceText[0] == '\t')
		return L"";

	if (sourceText[0] == '/') {
		sourceText.erase(0, 1);

		if (isClosingTag != nullptr)
			*isClosingTag = true;
	}
	else {
		if (isClosingTag != nullptr)
			*isClosingTag = false;
	}

	if (sourceText[0] == ' ' || sourceText[0] == '\t')
		return L"";

	std::wstring _tagName;
	size_t _sourceTextSize = sourceText.size();

	for (size_t i = 0; i < _sourceTextSize; ++i) {

		if (sourceText[0] == '>' || sourceText[0] == ' ' || sourceText[0] == '\t') {

			sourceText = removeSpacesAndTabs(sourceText);

			if (sourceText[0] == '>') {
				sourceText.erase(0, 1);

				if (isAttribute != nullptr)
					*isAttribute = false;
			}
			else {
				if (isAttribute != nullptr)
					*isAttribute = true;
			}

			if (buffer != nullptr)
				*buffer = sourceText;

			return _tagName;
		}

		_tagName += sourceText[0];
		sourceText.erase(0, 1);
	}

	if (isClosingTag != nullptr)
		*isClosingTag = false;

	if (buffer != nullptr)
		*buffer = L"";

	return L"";
}

Attribute XmlFile::searchAttribute(std::wstring sourceText, std::wstring* buffer, bool* isAttribute) const
{
	sourceText = removeSpacesAndTabs(sourceText);

	if (sourceText.size() == 0)
		return Attribute();

	Attribute _attribute;
	bool _isAttributeName = true;
	std::wstring _correctnessControl;

	size_t _sourceTextSize = sourceText.size();
	for (size_t i = 0; i < _sourceTextSize; ++i) {

		if (_isAttributeName == true) {

			_correctnessControl = removeSpacesAndTabs(sourceText);
			if (_correctnessControl != sourceText) {

				if (_correctnessControl[0] == '=')
					sourceText = _correctnessControl;
				else
					break;
			}

			if (sourceText[0] == '=') {
				sourceText.erase(0, 1);
				sourceText = removeSpacesAndTabs(sourceText);

				if (sourceText[0] != '"')
					break;
				else
					sourceText.erase(0, 1);

				_isAttributeName = false;
				continue;
			}

			_attribute.name += sourceText[0];
			sourceText.erase(0, 1);
		}
		else {

			if (sourceText[0] == '"') {
				sourceText.erase(0, 1);
				sourceText = removeSpacesAndTabs(sourceText);

				if (sourceText[0] == '>') {
					sourceText.erase(0, 1);

					if (isAttribute != nullptr)
						*isAttribute = false;
				}
				else {
					if (isAttribute != nullptr)
						*isAttribute = true;
				}

				if (buffer != nullptr)
					*buffer = sourceText;

				return _attribute;
			}

			_attribute.value += sourceText[0];
			sourceText.erase(0, 1);
		}
	}

	if (buffer != nullptr)
		*buffer = L"";

	if (isAttribute != nullptr)
		*isAttribute = false;

	return Attribute();
}

std::wstring XmlFile::searchValue(std::wstring sourceText, std::wstring* buffer) const
{
	if (sourceText.size() == 0)
		return L"";

	std::wstring _value;

	size_t _sourceTextSize = sourceText.size();
	for (size_t i = 0; i < _sourceTextSize; ++i) {
		if (sourceText[0] == '<') {

			if (buffer != nullptr)
				*buffer = sourceText;

			return _value;
		}

		_value += sourceText[0];
		sourceText.erase(0, 1);
	}

	return L"";
}


XmlFile::XmlFile()
{
	fileName_ = L"";
	openMode_ = std::wfstream::in;
}

XmlFile::~XmlFile()
{
	close();
}


bool XmlFile::open(std::wstring fileName, OpenMode openMode)
{
	if (fileName == L"")
		return false;

	openMode_ = std::wfstream::in;

	switch (openMode)
	{
	case OpenMode::WRITE:	openMode_ = std::wfstream::out;							break;
	case OpenMode::APPEND:	openMode_ = std::wfstream::out | std::wfstream::app;	break;
	}

	fileName_ = fileName;
	fileStream_.open(fileName_, openMode_);

	if (!fileStream_.is_open()) {
		close();
		return false;
	}

	fileStream_.imbue(std::locale("en_US.UTF-8")); //TODO: ???

	return true;
}

void XmlFile::close()
{
	fileStream_.close();
	fileName_.clear();
	openMode_ = std::wfstream::in;
}


int XmlFile::write(const Tag& tag)
{
	if (fileName_ == L"")
		return 0;

	int _errCode = write(tag, 0);
	if (_errCode == -1) {
		fileStream_.close();
		fileStream_.open(fileName_, openMode_);

		if (fileStream_.is_open())
			return 0;
		else
			return -1;
	}

	return 1;
}

Tag XmlFile::read()
{
	if (fileName_ == L"")
		return Tag();

	std::wstring _xmlFileText;

	std::wstring _line;
	while (std::getline(fileStream_, _line)) {
		_xmlFileText += removeSpacesAndTabs(_line);
	}

	History _history;
	Tag _tag = read(_history, _xmlFileText);

	if (_history.size() == 0)
		return _tag;
	else
		return Tag();
}
