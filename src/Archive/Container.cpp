#define UNICODE

#include "Container.h"


Container::Container()
{
	name_ = nullptr;
	task_ = nullptr;
	taskType_ = TASKT_NOTSPECIFIED;
}

Container::~Container()
{
	name_ = nullptr;
	task_ = nullptr;
	taskType_ = TASKT_NOTSPECIFIED;
	tags_.clear();
}

void Container::clear()
{
	erase(ContainerDataTypes::NAME);
	erase(ContainerDataTypes::TASK);
	erase(ContainerDataTypes::TASK_TYPE);
	erase(ContainerDataTypes::TAGS);
}

void Container::erase(ContainerDataTypes dataTypes)
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
			taskType_ = TASKT_NOTSPECIFIED;
		}
		break;

	case ContainerDataTypes::TAGS:
		for (size_t i = 0; i < tags_.size(); i++) {
			delete tags_[i];
		}
		tags_.clear();
		break;
	}
}

void Container::setName(const PWSTR name, const size_t length)
{
	erase(ContainerDataTypes::NAME);
	name_ = new WCHAR[length];
	wcscpy_s(name_, length, name);
}

void Container::setTask(const PWSTR task, const size_t length)
{
	erase(ContainerDataTypes::TASK);
	task_ = new WCHAR[length];
	wcscpy_s(task_, length, task);
}

void Container::setTaskType(const TaskTypes_Index_t index)
{
	if (TaskTypesCollection::findTaskType(index))
		taskType_ = index;
}

void Container::addTag(const PWSTR tag)
{
	for (auto i : tags_) {
		if (!wcscmp(tag, i)) {
			return;
		}
	}

	const size_t _length = wcslen(tag) + 1;
	PWSTR _tag = new WCHAR[_length];

	wcscpy_s(_tag, _length, tag);
	tags_.push_back(_tag);
}

PWSTR Container::getName()
{
	if (name_)
		return name_;

	return nullptr;
}

PWSTR Container::getTask()
{
	if (task_)
		return task_;

	return nullptr;
}

TaskTypes_Index_t Container::getTaskType()
{
	return taskType_;
}

PWSTR Container::getTag(const size_t index)
{
	if (tags_.size() > index)
		return tags_[index];

	return nullptr;
}

void Container::start()
{
	PWSTR _taskType = TaskTypesCollection::getTaskType(taskType_);

	if(!wcscmp(_taskType, L"URL"))
		ShellExecute(NULL, L"open", task_, NULL, NULL, SW_SHOW);

	else if (!wcscmp(_taskType, L"Program"))
		ShellExecute(NULL, L"open", task_, NULL, NULL, SW_SHOW); //—делать возможность задавать параметры запуска.
}
