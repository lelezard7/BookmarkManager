/**
* 
*/

#pragma once
#ifndef _CONTAINER_
#define _CONTAINER_

#include "TaskTypesCollection.h"
#include <Windows.h>
#include <vector>

#define CONTAINER_REGISTERED	(true)
#define CONTAINER_UNREGISTERED	(false)

class Archive;
enum class ContainerDataTypes;


class Container //TODO: перегрузить операторы.
{
	PWSTR name_;
	PWSTR task_;
	TaskType taskType_;
	std::vector<PWSTR> tags_;

	bool isRegistered;

public:
	Container();
	~Container();

	void clear();
	void erase(ContainerDataTypes dataTypes);

	void setName(const PWSTR name, const size_t length);
	void setTask(const PWSTR task, const size_t length);
	bool setTaskType(const TaskType taskType);
	bool addTag(const PWSTR tag);

	PWSTR getName();
	PWSTR getTask();
	TaskType getTaskType();
	PWSTR getTag(const size_t index);
	void start();

	friend Archive;
};

enum class ContainerDataTypes
{
	NAME,
	TASK,
	TASK_TYPE,
	TAGS
};

#endif
