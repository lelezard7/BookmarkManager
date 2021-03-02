#ifndef UNICODE
#define UNICODE
#endif

#include "Archive.h"
#include <wchar.h>
#include <iterator>

/*		---class Archive---		*/

ID Archive::id_ = 0;
Archive_t Archive::archive_;

ID Archive::addContainer(const Container container)
{
	archive_.emplace(std::make_pair(id_, container));
	return id_++;
}

Container* Archive::getContainerByID(const ID id)
{
	if (archive_.find(id) != archive_.end())
	{
		return &archive_[id];
	}
	return nullptr;
}

Container* Archive::getContainerByIndex(const size_t index)
{
	if (index > archive_.size() - 1) {
		return nullptr;
	}

	Archive_t::iterator _iterator = archive_.begin();
	std::advance(_iterator, index);
	return &_iterator->second;
}

size_t Archive::size()
{
	return archive_.size();
}

/*		---class Container---		*/

Container::Container()
{
	name_ = nullptr;
	task_ = nullptr;
}

Container::~Container()
{
	name_ = nullptr;
	task_ = nullptr;
	tags_.clear();
}

void Container::clear()
{
	if (name_) {
		delete name_;
		name_ = nullptr;
	}

	if (task_) {
		delete task_;
		task_ = nullptr;
	}

	for (size_t i = 0; i < tags_.size(); i++)
	{
		delete tags_[i];
	}
	tags_.clear();
}

void Container::setContent(ContainerDataTypes dataType, PCWSTR content, const size_t length)
{
	WCHAR** _dataType = nullptr;

	switch (dataType)
	{
	case ContainerDataTypes::NAME: {
		_dataType = &name_;
		break;
	}

	case ContainerDataTypes::TASK: {
		_dataType = &task_;
		break;
	}

	case ContainerDataTypes::TAGS: {
		addTag(content);
		break;
	}
	}

	if (_dataType)
	{
		if (*_dataType)
		{
			delete[] * _dataType;
			*_dataType = nullptr;
		}

		*_dataType = new WCHAR[length];
		wcscpy_s(*_dataType, length, content);
	}
}

PWSTR Container::getContent(ContainerDataTypes dataType)
{
	switch (dataType)
	{
	case ContainerDataTypes::NAME: {
		return name_;
	}

	case ContainerDataTypes::TASK: {
		return task_;
	}

	case ContainerDataTypes::TAGS: {
		return nullptr;
	}
	}
}

std::vector<PWSTR>* Container::getAllTags()
{
	return &tags_;
}

PWSTR Container::getTag(const size_t index)
{
	return tags_[index];
}

void Container::addTag(PCWSTR tag)
{
	/*		Check if such a tag already exists.		*/
	std::wstring _verifiableTag(tag);

	for (std::wstring i : tags_)
	{
		if (_verifiableTag == i)
		{
			return;
		}
	}


	const size_t _length = std::wcslen(tag) + 1;
	PWSTR _tag = new WCHAR[_length];

	wcscpy_s(_tag, _length, tag);
	tags_.push_back(_tag);
}

void Container::setTaskType(TaskTypes taskType)
{
	taskType_ = taskType;
}

void Container::start() //TODO: Test
{
	STARTUPINFO startupinfo;
	ZeroMemory(&startupinfo, sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;

	PWSTR o = nullptr;
	if (taskType_ == TaskTypes::PROGRAM)
	{
		o = task_;
	}
	else if (taskType_ == TaskTypes::URL)
	{
		o = new WCHAR[600]{ L"Z:\\OperaGX\\launcher.exe" };
		std::wcscat(o, L" \"");
		std::wcscat(o, task_);
		std::wcscat(o, L"\"");
	}

	//MessageBox(NULL, o, L"", MB_OK);
	if (CreateProcess(NULL, o, NULL, NULL, false, NULL, NULL, NULL, &startupinfo, &pi))
	{
		//CreateProcess(L"Z:\\OperaGX\\launcher.exe", NULL, NULL, NULL, false, NULL, NULL, NULL, &startupinfo, &pi)
		//Sleep(1000);
		//TerminateProcess(pi.hProcess, NO_ERROR);
	}
	delete[] o;
}
