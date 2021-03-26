#define UNICODE

#include "..\Common\Debug.h"
#include "Container.h"


Container::Container()
{
	isRegistered = CONTAINER_UNREGISTERED;
	taskType_ = TASKTYPE_NOTSPECIFIED;
	name_ = nullptr;
	task_ = nullptr;
}

Container::Container(const Container& other)
{
	this->operator=(other);
}

Container::~Container()
{
	isRegistered == CONTAINER_UNREGISTERED;
	clear();
}


void Container::clear()
{
	if (isRegistered == CONTAINER_REGISTERED)
		return;

	erase(ContainerDataTypes::NAME);
	erase(ContainerDataTypes::TASK);
	erase(ContainerDataTypes::TASK_TYPE);
	erase(ContainerDataTypes::TAGS);
}

void Container::erase(ContainerDataTypes dataTypes)
{
	if (isRegistered == CONTAINER_REGISTERED)
		return;

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
			taskType_ = TASKTYPE_NOTSPECIFIED;
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
	if (isRegistered == CONTAINER_REGISTERED)
		return;

	erase(ContainerDataTypes::NAME);
	name_ = new WCHAR[length];
	wcscpy_s(name_, length, name);
}

void Container::setTask(const PWSTR task, const size_t length)
{
	if (isRegistered == CONTAINER_REGISTERED)
		return;

	erase(ContainerDataTypes::TASK);
	task_ = new WCHAR[length];
	wcscpy_s(task_, length, task);
}

bool Container::setTaskType(const TaskType taskType)
{
	if (isRegistered == CONTAINER_REGISTERED)
		return false;

	if (TaskTypesCollection::checkTaskType(taskType)) {
		taskType_ = taskType;
		return true;
	}

	return false;
}

bool Container::addTag(const PWSTR tag)
{
	if (isRegistered == CONTAINER_REGISTERED)
		return false;

	for (auto i : tags_) {
		if (!wcscmp(tag, i)) {
			return false;
		}
	}

	const size_t _length = wcslen(tag) + 1;
	PWSTR _tag = new WCHAR[_length];

	wcscpy_s(_tag, _length, tag);
	tags_.push_back(_tag);

	return true;
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

TaskType Container::getTaskType()
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
	PWSTR _taskType = TaskTypesCollection::getTaskTypeName(taskType_);

	//TODO: Инициализировать COM перед ShellExecute.

	if(!wcscmp(_taskType, L"URL"))
		ShellExecute(NULL, L"open", task_, NULL, NULL, SW_SHOW);

	else if (!wcscmp(_taskType, L"Программа"))
		ShellExecute(NULL, L"open", task_, NULL, NULL, SW_SHOW); //TODO: Сделать возможность задавать параметры запуска.
}

void Container::operator=(const Container& other)
{
	int _length = wcslen(other.name_) + 1;
	this->name_ = new WCHAR[_length];
	wcscpy_s(this->name_, _length, other.name_);

	_length = wcslen(other.task_) + 1;
	this->task_ = new WCHAR[_length];
	wcscpy_s(this->task_, _length, other.task_);

	this->taskType_ = other.taskType_;
	this->isRegistered = CONTAINER_UNREGISTERED; //TODO: Написать о том что он всегда копируется как UNREGISTERED.

	for (auto i : other.tags_) {
		_length = wcslen(i) + 1;
		PWSTR _tag = new WCHAR[_length];

		wcscpy_s(_tag, _length, i);
		tags_.push_back(_tag);
	}
}
