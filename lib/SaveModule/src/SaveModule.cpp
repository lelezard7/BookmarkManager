#include "SaveModule.h"
#include <Windows.h>
#include <vector>



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

	if (tag.getFlag() == TF_VALUE)
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









Tag XmlFile::read()
{
	History _history;
	Tag _tag = read(_history);

	return _tag;
}



static bool isSameLevel = false;

Tag XmlFile::read(History& history)
{
	wchar_t _symbol;
	Tag _tag;

	while (fileStream_.get(_symbol))
	{
		//tag
		if (_symbol == '<')
		{
			Сonditions _conditions;
			_conditions.push_back(L" ");
			_conditions.push_back(L">");

			int _errCode = readXmlLine(_conditions, _tag.getName());
			history.push_back(_tag.getName());

			if (_errCode == -1) {//TODO: return NULL
				Tag _nullTag;
				return _nullTag;
			}

			//attributes
			if (_errCode == 0)
			{
				Attribute _attribute;

				while (fileStream_.get(_symbol))
				{
					if (_symbol == '>')
						break;

					fileStream_.unget();

					_attribute.name = readXmlLine(L"=\"");
					_attribute.value = readXmlLine(L"\"");
					_tag.addAttribute(_attribute.name, _attribute.value);

					_attribute.clear();
				}
			}
		}

		//value
		while (fileStream_.get(_symbol))
		{
			if (_symbol == '\n' || _symbol == '\t')
				continue;

			if (_symbol == '<')
			{
				do {
					_tag.setFlag(TF_SUBTAGS);
					fileStream_.unget();
					_tag.addSubTag(read(history));
				} while (isSameLevel);

				readXmlLine(L"</");
				std::wstring _closingTag = readXmlLine(L">");

				if (_closingTag != history.back()) {//TODO: return NULL
					Tag _nullTag;
					return _nullTag;
				}

				history.pop_back();
				goto END;
			}

			fileStream_.unget();
			_tag.setFlag(TF_VALUE);
			_tag.setValue(readXmlLine(L"</"));

			std::wstring _closingTag = readXmlLine(L">");

			if (_closingTag != history.back()) {//TODO: return NULL
				Tag _nullTag;
				return _nullTag;
			}

			history.pop_back();
			goto END;
		}
	}
END:

	isSameLevel = read_isSameLevel_check();

	return _tag;
}

bool XmlFile::read_isSameLevel_check()
{
	wchar_t _symbol;
	bool _isSameLevel = 0;

	while (fileStream_.get(_symbol))
	{
		if (_symbol == '\n' || _symbol == '\t')
			continue;

		if (_symbol == '<')
		{
			fileStream_.get(_symbol);
			if (_symbol == '/')
				_isSameLevel = false;
			else
				_isSameLevel = true;

			fileStream_.unget();
			break;
		}
	}
	fileStream_.unget();
	return _isSameLevel;
}

int XmlFile::readXmlLine(Сonditions conditions, std::wstring& result)
{
	if (conditions.size() == 0)
		return -1;

	for (auto i : conditions)
		if (i.size() == 0)
			return -1;

	wchar_t _symbol;

	while (fileStream_.get(_symbol))
	{
		int ind = 0;
		for (auto i : conditions)
		{
			if (i.size() == 1) {
				if (_symbol == i[0])
					return ind;
			}
			else if (_symbol == i[0])
			{
				std::wstring _buffer = L"";
				for (int j = 0; j < i.size(); ++j)
				{
					if (i[j] == _symbol && j == i.size() - 1)
						return ind;

					if (i[j] != _symbol)
					{
						result += _buffer;
						break;
					}

					_buffer += _symbol;
					fileStream_.get(_symbol);
				}
			}
			ind++;
		}

		if (_symbol == '&')
		{
			std::wstring _buffer = readXmlLine(L";");
			_buffer = entityToSymbol(_buffer);
			result += _buffer;
			continue;
		}
		result += _symbol;
	}

	return -1;
}

std::wstring XmlFile::readXmlLine(std::wstring condition)
{
	int _conditionSize = condition.size();

	if (_conditionSize == 0)
		return L"";

	wchar_t _symbol;
	std::wstring _result;

	while (fileStream_.get(_symbol))
	{
		if (_conditionSize == 1) {
			if (_symbol == condition[0])
				return _result;
		}
		else if (_symbol == condition[0])
		{
			std::wstring _buffer = L"";
			for (int i = 0; i < _conditionSize; ++i)
			{
				if (condition[i] == _symbol && i == _conditionSize - 1)
					return _result;

				if (condition[i] != _symbol)
				{
					_result += _buffer;
					break;
				}

				_buffer += _symbol;
				fileStream_.get(_symbol);
			}
		}

		if (_symbol == '&')
		{
			std::wstring _buffer = readXmlLine(L";");
			_buffer = entityToSymbol(_buffer);
			_result += _buffer;
			continue;
		}
		_result += _symbol;
	}

	return L"";
}
