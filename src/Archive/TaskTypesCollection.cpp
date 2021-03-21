#define UNICODE

#include "..\Common\Debug.h"
#include "TaskTypesCollection.h"

TaskType TaskTypesCollection::nextTaskType_ = 0;
std::map<TaskType, PWSTR> TaskTypesCollection::taskTypes_;


TaskType TaskTypesCollection::addTaskType(const PWSTR name)
{
	if (!checkTaskTypeName(name))
		return -1;

	int _length = wcslen(name) + 1;
	PWSTR _name = new WCHAR[_length];
	wcscpy_s(_name, _length, name);

	taskTypes_.emplace(std::make_pair(nextTaskType_, _name));

	return nextTaskType_++;
}


PWSTR TaskTypesCollection::getTaskTypeName(const TaskType taskType)
{
	if (taskTypes_.find(taskType) == taskTypes_.end())
		return nullptr;

	return taskTypes_[taskType];
}

TaskType TaskTypesCollection::getTaskType(const PWSTR name)
{
	for (auto i : taskTypes_) {
		if (!wcscmp(i.second, name))
			return i.first;
	}

	return -1;
}


bool TaskTypesCollection::checkTaskType(const TaskType taskType)
{
	return taskTypes_.find(taskType) != taskTypes_.end();
}

bool TaskTypesCollection::checkTaskTypeName(const PWSTR name)
{
	for (auto i : taskTypes_) {
		if (!wcscmp(i.second, name))
			return false;
	}

	return true;
}


size_t TaskTypesCollection::size()
{
	return taskTypes_.size();
}

void TaskTypesCollection::clear()
{
	for (auto i : taskTypes_)
		delete[] i.second;

	taskTypes_.clear();
	nextTaskType_ = 0;
}
