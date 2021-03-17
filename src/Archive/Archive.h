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

#include "..\Common\Debug.h"
#include "Container.h"
#include <Windows.h>
#include <iostream>
#include <map>

typedef size_t ID;
typedef std::map<ID, Container> Archive_t;


class Archive //TODO: Добавить функцию удаления контейнера
{
	/*
	*		A unique id that is given to each container at the stage of adding
	*		to the archive.
	*/
	static ID id_;
	static Archive_t archive_;

	Archive() = delete;

public:
	static ID addContainer(const Container container);

	/*		If it fails, the function returns nullptr.		*/
	static Container* getContainerByID(const ID id);
	static Container* getContainerByIndex(const size_t index);
	static void clear();
	static bool delContainerByIndex(const size_t index);
	static size_t size();
};

#endif
