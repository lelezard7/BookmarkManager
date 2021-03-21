/**
*		Class Archive stores and manages containers.
*		
*		Class Container stores information specified by the user in
*		the ContainerCreationWindow window. It includes:
*				1) name - the name of the task. Task name is the basic information that
*							should be displayed by mainListView.
*				2) task - what the program will execute when the user selects an item
*							with the task name in mainListView. The tasks can be
*							the following types:
*									1) Opening URL
*									2) Running the program on the PC
*				3) tags - help with searching and filtering.
* 
*		Search and filtering can be carried out by:
*				1) name
*				2) task
*				3) task type
*				3) tags
*				4) unique id
*/

#pragma once
#ifndef _ARCHIVE_
#define _ARCHIVE_

#include "Container.h"
#include <Windows.h>
#include <map>
#include <vector>

typedef size_t Archive_Id;


class Archive //Сделать find()
{
	static std::map<Archive_Id, Container> archive_;
	static std::vector<Archive_Id> nextId_;
	static Archive_Id maxId_;

	Archive() = delete;
	~Archive() = delete;

	static Archive_Id getFreeId();
	static bool freeId(const Archive_Id id);

public:
	static Archive_Id addContainer(Container& container);
	static Container* getContainer(const Archive_Id id);
	static bool deleteContainer(const Archive_Id id);
	static void clear();
	static size_t size();
};

#endif
