/*
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

#include <Windows.h>
#include <iostream>
#include <vector>
#include <map>

class Container;
enum class ContainerDataTypes;

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
	static size_t size();
};



class Container //TODO: Перегрузить операторы.
{
	PWSTR name_;
	PWSTR task_;
	std::vector<PWSTR> tags_;

public:
	Container();

	/*
	*		The destructor does not destroy the created data, but only wipes the pointers.
	*		'clear' function created to destroy data.
	*/
	~Container();

	/*		Cleans up everything that was created, and then wipes the pointers.		*/
	void clear(); //TODO: Перегрузить для удаления name_/task_ и т.д.
	void setContent(ContainerDataTypes dataType, PCWSTR content, const size_t length);

	/*
	*		getContent does not return the tags. Instead, nullptr will be returned.
	*		Use getAllTeg/getTeg to get them.
	*/
	PWSTR getContent(ContainerDataTypes dataType);
	std::vector<PWSTR>* getAllTags();

	/*		index - array element.		*/
	PWSTR getTag(const size_t index);
	void addTag(PCWSTR tag);
};

enum class ContainerDataTypes
{
	NAME,
	TASK,
	TAGS
};

#endif
