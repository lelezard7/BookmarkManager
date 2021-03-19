/**
* 
*/

#pragma once
#ifndef _CONTAINER_
#define _CONTAINER_

#include "..\Common\Debug.h"
#include "..\Common\CommonOperations.h"
#include "..\ApplicationSettings\ApplicationSettings.h"
#include <Windows.h>
#include <vector>

enum class ContainerDataTypes;


class Container //TODO: Перегрузить операторы.
{
	PWSTR name_;
	PWSTR task_;
	TaskTypes_Index_t taskType_;
	std::vector<PWSTR> tags_;

public:
	Container();
	~Container(); //Утечка памяти в случае если контейнер небыл записан в архив.

	void clear();
	void erase(ContainerDataTypes dataTypes);

	void setName(const PWSTR name, const size_t length);
	void setTask(const PWSTR task, const size_t length);
	void setTaskType(const TaskTypes_Index_t index);
	void addTag(const PWSTR tag);

	PWSTR getName();
	PWSTR getTask();
	TaskTypes_Index_t getTaskType();
	PWSTR getTag(const size_t index);
	
	void start();
};

enum class ContainerDataTypes
{
	NAME,
	TASK,
	TASK_TYPE,
	TAGS
};

#endif
