/**
* 
*/

#pragma once
#ifndef _CONTAINER_
#define _CONTAINER_

#include "..\Common\Debug.h"
#include <Windows.h>
#include <vector>
#include <map>

typedef int	TaskTypes_ID;
typedef std::map<TaskTypes_ID, PWSTR> TaskTypes_t;

enum class ContainerDataTypes;

void addTaskType(const PWSTR name);
void createTaskTypesCB(HWND hWnd);

class Container //TODO: Перегрузить операторы.
{
	PWSTR name_;
	PWSTR task_;
	PWSTR taskType_;
	std::vector<PWSTR> tags_;

public:
	Container();

	/*
	*		The destructor does not destroy the created data, but only wipes the pointers.
	*		'clear' function created to destroy data.
	*/
	~Container(); //Утечка памяти в случае если контейнер небыл записан в архив.

	//		Cleans up everything that was created, and then wipes the pointers.
	void clear();
	void clear(ContainerDataTypes dataTypes);

	void setName(const PWSTR name);
	void setTask(const PWSTR task);
	void setTaskType(const PWSTR taskType);
	
	//void setContent(ContainerDataTypes dataType, PCWSTR content, const size_t length);

	///*
	//*		getContent does not return the tags. Instead, nullptr will be returned.
	//*		Use getAllTeg/getTeg to get them.
	//*/
	//PWSTR getContent(ContainerDataTypes dataType);
	//std::vector<PWSTR>* getAllTags();

	////		index - array element.
	//PWSTR getTag(const size_t index);
	//void addTag(PCWSTR tag);
	//void setTaskType(TaskTypes_ID id);

	//void start();
};

enum class ContainerDataTypes
{
	NAME,
	TASK,
	TASK_TYPE,
	TAGS
};

#endif
