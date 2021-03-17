#define UNICODE

#include "Container.h"

static TaskTypes_ID TaskTypes_id = 0;
static TaskTypes_t TaskTypes;

Container::Container()
{
	name_ = nullptr;
	task_ = nullptr;
	taskType_ = nullptr;
}

Container::~Container()
{
	name_ = nullptr;
	task_ = nullptr;
	taskType_ = nullptr;
	tags_.clear();
}

void Container::clear()
{
	clear(ContainerDataTypes::NAME);
	clear(ContainerDataTypes::TASK);
	clear(ContainerDataTypes::TASK_TYPE);
	clear(ContainerDataTypes::TAGS);
}

void Container::clear(ContainerDataTypes dataTypes)
{
	switch (dataTypes)
	{
	case ContainerDataTypes::NAME:
		if (name_) {
			delete name_;
			name_ = nullptr;
		}
		break;

	case ContainerDataTypes::TASK:
		if (task_) {
			delete task_;
			task_ = nullptr;
		}
		break;

	case ContainerDataTypes::TASK_TYPE:
		if (taskType_) {
			delete taskType_;
			taskType_ = nullptr;
		}
		break;

	case ContainerDataTypes::TAGS:
		for (size_t i = 0; i < tags_.size(); i++)
		{
			delete tags_[i];
		}
		tags_.clear();
		break;
	}
}

void Container::setName(const PWSTR name)
{
	clear(ContainerDataTypes::NAME);
	name_ = name;
}

void Container::setTask(const PWSTR task)
{
	clear(ContainerDataTypes::TASK);
	task_ = task;
}

void Container::setTaskType(const PWSTR taskType)
{
	clear(ContainerDataTypes::TASK_TYPE);
	taskType_ = taskType;
}

//void Container::setContent(ContainerDataTypes dataType, PCWSTR content, const size_t length)
//{
//	WCHAR** _dataType = nullptr;
//
//	switch (dataType)
//	{
//	case ContainerDataTypes::NAME: {
//		_dataType = &name_;
//		break;
//	}
//
//	case ContainerDataTypes::TASK: {
//		_dataType = &task_;
//		break;
//	}
//
//	case ContainerDataTypes::TAGS: {
//		addTag(content);
//		break;
//	}
//	}
//
//	if (_dataType)
//	{
//		if (*_dataType)
//		{
//			delete[] * _dataType;
//			*_dataType = nullptr;
//		}
//
//		*_dataType = new WCHAR[length];
//		wcscpy_s(*_dataType, length, content);
//	}
//}

//PWSTR Container::getContent(ContainerDataTypes dataType)
//{
//	switch (dataType)
//	{
//	case ContainerDataTypes::NAME: {
//		return name_;
//	}
//
//	case ContainerDataTypes::TASK: {
//		return task_;
//	}
//
//	case ContainerDataTypes::TAGS: {
//		return nullptr;
//	}
//	}
//}
//
//std::vector<PWSTR>* Container::getAllTags()
//{
//	return &tags_;
//}
//
//PWSTR Container::getTag(const size_t index)
//{
//	return tags_[index];
//}
//
//void Container::addTag(PCWSTR tag)
//{
//	/*		Check if such a tag already exists.		*/
//	std::wstring _verifiableTag(tag);
//
//	for (std::wstring i : tags_)
//	{
//		if (_verifiableTag == i)
//		{
//			return;
//		}
//	}
//
//
//	const size_t _length = std::wcslen(tag) + 1;
//	PWSTR _tag = new WCHAR[_length];
//
//	wcscpy_s(_tag, _length, tag);
//	tags_.push_back(_tag);
//}
//
//void Container::setTaskType(TaskTypes_ID id)
//{
//	if (TaskTypes.find(id) != TaskTypes.end())
//	{
//		taskType_ = TaskTypes[id];
//	}
//}
//
//void Container::start() //TODO: Test
//{
//	STARTUPINFO startupinfo;
//	ZeroMemory(&startupinfo, sizeof(STARTUPINFO));
//	PROCESS_INFORMATION pi;
//
//	PWSTR o = nullptr;
//	if (!wcscmp(taskType_, L"Program"))
//	{
//		o = task_;
//	}
//	else if (!wcscmp(taskType_, L"URL"))
//	{
//		o = new WCHAR[600]{ L"Z:\\OperaGX\\launcher.exe" };
//		std::wcscat(o, L" \"");
//		std::wcscat(o, task_);
//		std::wcscat(o, L"\"");
//	}
//
//	if (CreateProcess(NULL, o, NULL, NULL, false, NULL, NULL, NULL, &startupinfo, &pi))
//	{
//		//CreateProcess(L"Z:\\OperaGX\\launcher.exe", NULL, NULL, NULL, false, NULL, NULL, NULL, &startupinfo, &pi)
//		//Sleep(1000);
//		//TerminateProcess(pi.hProcess, NO_ERROR);
//	}
//	delete[] o;
//}

void addTaskType(const PWSTR name)
{
	TaskTypes.emplace(std::make_pair(TaskTypes_id, name));
	TaskTypes_id++;
}

void createTaskTypesCB(HWND hWnd)
{
	for (auto i : TaskTypes)
	{
		SendMessage(hWnd, CB_INSERTSTRING, -1, (LPARAM)i.second);
	}
}