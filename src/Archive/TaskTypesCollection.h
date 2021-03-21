/**
*
*/

#pragma once
#ifndef _TASK_TYPES_COLLECTION_
#define _TASK_TYPES_COLLECTION_

#include <Windows.h>
#include <map>

#define TASKTYPE_NOTSPECIFIED (-1)

typedef int	TaskType;


class TaskTypesCollection
{
	static TaskType nextTaskType_;
	static std::map<TaskType, PWSTR> taskTypes_;

	TaskTypesCollection() = delete;
	~TaskTypesCollection() = delete;
public:
	static TaskType addTaskType(const PWSTR name);

	static PWSTR getTaskTypeName(const TaskType taskType);
	static TaskType getTaskType(const PWSTR name);

	static bool checkTaskType(const TaskType taskType);
	static bool checkTaskTypeName(const PWSTR name);

	static size_t size();
	static void clear();
};

#endif
