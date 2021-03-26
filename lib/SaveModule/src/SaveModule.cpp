#include "SaveModule.h"
#include <fstream>
//#include <CommCtrl.h>
#include <Windows.h>

static std::ofstream file;
static std::ifstream file_in;

TagsPair createTagsPair(std::string tagName)
{
	TagsPair tagsPair;
	return tagsPair;
}







char essenceToSymbol(std::string essence)
{
	if (essence == "lt")			return '<';
	else if (essence == "gt")		return '>';
	else if (essence == "amp")		return '&';
	else if (essence == "apos")		return '\'';
	else if (essence == "quot")		return '\"';

	return '\0';
}


std::string symbolToEssence(char symbol)
{
	if (symbol == '<')				return "lt";
	else if (symbol == '>')			return "gt";
	else if (symbol == '&')			return "amp";
	else if (symbol == '\'')		return "apos";
	else if (symbol == '\"')		return "quot";

	return "";
}

bool openXmlFile(std::string fileName, int mode)
{
	if (mode == XMLFILE_WRITE)
	{
		file.open(fileName);//TODO: записывать информацию о версии.

		if (!file.is_open())
			return false;
	}
	else if (mode == XMLFILE_READ)
	{
		file_in.open(fileName);

		if (!file_in.is_open())
			return false;
	}

	return true;
}

bool closeXmlFile(std::string fileName) //TODO: Проверять имя файла.
{
	file.close();
	file_in.close();
	return true;
}


std::string writeXmlFile(std::string text)
{
	std::string newText;
	for (size_t i = 0; i < text.size(); ++i)
	{
		std::string newEssence = symbolToEssence(text[i]);
		if (newEssence != "")
		{
			newText += "&" + newEssence + ";";
		}
		else
		{
			newText += text[i];
		}
	}

	return newText;
}


bool saveXmlFile(TagStructure& tagStructure)
{
	static int level = 0;
	std::string openingTag;
	openingTag = "<" + tagStructure.tag;

	if (tagStructure.attributes.size() != 0)
	{
		Attributes::iterator iter = tagStructure.attributes.begin();
		for (; iter != tagStructure.attributes.end(); ++iter)
		{
			std::string newValue = writeXmlFile(iter->second);
			openingTag += " " + iter->first + "=\"" + newValue + "\"";
		}
	}

	openingTag += ">";
	file << openingTag;

	if (tagStructure.flag == TSF_VALUE) {
		std::string newValue = writeXmlFile(tagStructure.value);
		file << newValue;
		file << "</" + tagStructure.tag + ">\n";

		return false;
	}
	else {
		level++;

		file << "\n";

		size_t subTagsCount = tagStructure.subTags.size();
		for (size_t i = 0; i < subTagsCount; ++i)
		{
			for (size_t i = 0; i < level; ++i)
				file << "\t";

			saveXmlFile(*tagStructure.subTags[i]);
		}
		level--;

		for (size_t i = 0; i < level; ++i)
			file << "\t";

		file << "</" + tagStructure.tag + ">\n";
	}
	return false;
}






std::string readXmlLine(std::string condition)
{
	char symbol;
	std::string result;

	int conditionSize = condition.size();
	if (conditionSize == 0)
		return "";

	while (file_in.get(symbol))
	{
		if (conditionSize == 1) {
			if (symbol == condition[0])
				return result;
		}
		else if (symbol == condition[0])
		{
			std::string buffer = "";
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
			std::string buf = readXmlLine(";");
			buf = essenceToSymbol(buf);
			result += buf;
			continue;
		}
		result += symbol;
	}

	return "";
}


int readXmlLine(std::vector<std::string> conditions, std::string& result)
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
				std::string buffer = "";
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
			std::string buf = readXmlLine(";");
			buf = essenceToSymbol(buf);
			result += buf;
			continue;
		}
		result += symbol;
	}

	return -1;
}

bool checkLevel()
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

TagStructure* readXmlFile()
{
	static std::vector<std::string> history;
	char symbol;
	TagStructure* tagStructure = new TagStructure;

	while (file_in.get(symbol))
	{
		if (symbol == '<')
		{
			//tag
			std::vector<std::string> conditions;
			conditions.push_back(" ");
			conditions.push_back(">");
			int res = readXmlLine(conditions, tagStructure->tag);
			history.push_back(tagStructure->tag);


			if (res == -1)
				return 0;

			if (res == 0)
			{
				//attributes
				std::string attribute;
				std::string attributeValue;
				while (file_in.get(symbol))
				{
					if (symbol == '>')
						break;

					file_in.unget();

					attribute = readXmlLine("=\"");
					attributeValue = readXmlLine("\"");
					tagStructure->attributes.emplace(std::make_pair(attribute, attributeValue));

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
						tagStructure->flag = TSF_SUBTAGS;
						file_in.unget();
						tagStructure->subTags.push_back(readXmlFile());
					} while (isSameLevel);

					readXmlLine("</");
					std::string closingTag = readXmlLine(">");
					if (closingTag != history.back())
						return 0;

					history.pop_back();
					goto END;
				}

				file_in.unget();
				tagStructure->flag = TSF_VALUE;
				tagStructure->value = readXmlLine("</");

				std::string closingTag = readXmlLine(">");
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

void TagStructure::setTag(std::string tag)
{
	this->tag = tag;
}

void TagStructure::addAttribute(std::string attribute, std::string attributeValue)
{
	attributes.emplace(std::make_pair(attribute, attributeValue));
}

void TagStructure::setFlag(bool flag)
{
	this->flag = flag;
}

void TagStructure::setValue(std::string value)
{
	this->value = value;
}

TagStructure* TagStructure::addSubTag(TagStructure*& subTags)
{
	TagStructure* newTagStructure = new TagStructure(*subTags);
	this->subTags.push_back(newTagStructure);
	subTags = newTagStructure;
	return newTagStructure;
}

TagStructure::TagStructure()
{
	tag = "";
	flag = TSF_VALUE;
	value = "";
}

TagStructure::TagStructure(TagStructure& other)
{

	tag = other.tag;
	flag = other.flag;
	value = other.value;
	subTags = other.subTags;
	attributes = other.attributes;
}
