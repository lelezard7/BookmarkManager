/*
*		The position and size of the controls are set here.
*		This will make it easier to add new controls and update existing controls.
* 
*		The name of the window is listed in the multi-line comment.
*		The control name is listed in the one-line comment.
*		
*		The sizes and coordinates of the controls can be calculated relative to each other.
*		When calculating, if possible, the number should be in front of the name
*		used in the definition calculations. For example:
*	 -------------------------------------------------------------------------------------------------------	
*	|	#define SettingsProgramWnd_navigationPanel_WIDTH	(SettingsProgramWnd_RECT_RIGHT - \				|
*	|															(2 * SettingsProgramWnd_navigationPanel_X))	|
*	|																										|
*	|	#define ContainerCreationWnd_tagsListView_Y			(3 + ContainerCreationWnd_tagsTextBox_Y + \		|
*	|															ContainerCreationWnd_tagsTextBox_HEIGHT)	|
*	 -------------------------------------------------------------------------------------------------------
*/

#pragma once
#ifndef _POSITIONANDSIZECONTROLS_
#define _POSITIONANDSIZECONTROLS_

#include "Debug.h"
#include "CommonOperations.h"
#include "..\HandleManager\HandleManager.h"
#include "BkmDef.h"


/*		ContainerCreationWindow		*/

#define ContainerCreationWnd_RECT_RIGHT		(CommonOperations::getClientRectValue(\
											HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_WND),\
											ClientRectCoordinates::RIGHT))

#define ContainerCreationWnd_RECT_BOTTOM	(CommonOperations::getClientRectValue(\
											HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_WND),\
											ClientRectCoordinates::BOTTOM))

//			taskTypeDropDList
#define ContainerCreationWnd_taskTypeDropDList_WIDTH	(150)
#define ContainerCreationWnd_taskTypeDropDList_HEIGHT	(15)
#define ContainerCreationWnd_taskTypeDropDList_X		(ContainerCreationWnd_RECT_RIGHT - \
															6 - ContainerCreationWnd_taskTypeDropDList_WIDTH)
#define ContainerCreationWnd_taskTypeDropDList_Y		(10)

//			nameTextBox
#define ContainerCreationWnd_nameTextBox_WIDTH			((ContainerCreationWnd_RECT_RIGHT / 2) - 4)
#define ContainerCreationWnd_nameTextBox_HEIGHT			(23)
#define ContainerCreationWnd_nameTextBox_X				(5)
#define ContainerCreationWnd_nameTextBox_Y				(12 + ContainerCreationWnd_taskTypeDropDList_Y + \
															ContainerCreationWnd_taskTypeDropDList_HEIGHT)

//			adressTextBox
#define ContainerCreationWnd_adressTextBox_WIDTH		((ContainerCreationWnd_RECT_RIGHT / 2) - 9)
#define ContainerCreationWnd_adressTextBox_HEIGHT		(23)
#define ContainerCreationWnd_adressTextBox_X			(4 + (ContainerCreationWnd_RECT_RIGHT / 2))
#define ContainerCreationWnd_adressTextBox_Y			(12 + ContainerCreationWnd_taskTypeDropDList_Y + \
															ContainerCreationWnd_taskTypeDropDList_HEIGHT)

//			tagsTextBox
#define ContainerCreationWnd_tagsTextBox_WIDTH			(ContainerCreationWnd_RECT_RIGHT - 10)
#define ContainerCreationWnd_tagsTextBox_HEIGHT			(23)
#define ContainerCreationWnd_tagsTextBox_X				(5)
#define ContainerCreationWnd_tagsTextBox_Y				(5 + ContainerCreationWnd_adressTextBox_Y + \
															ContainerCreationWnd_adressTextBox_HEIGHT)

//			tagsListView
#define ContainerCreationWnd_tagsListView_X				(5)
#define ContainerCreationWnd_tagsListView_Y				(3 + ContainerCreationWnd_tagsTextBox_Y + \
															ContainerCreationWnd_tagsTextBox_HEIGHT)
#define ContainerCreationWnd_tagsListView_WIDTH			(ContainerCreationWnd_RECT_RIGHT - 10)
#define ContainerCreationWnd_tagsListView_HEIGHT		(ContainerCreationWnd_RECT_BOTTOM - \
															50 - ContainerCreationWnd_tagsListView_Y)

//			applyButton
#define ContainerCreationWnd_applyButton_WIDTH			(100)
#define ContainerCreationWnd_applyButton_HEIGHT			(25)
#define ContainerCreationWnd_applyButton_X				(ContainerCreationWnd_RECT_RIGHT - \
															7 - ContainerCreationWnd_applyButton_WIDTH)
#define ContainerCreationWnd_applyButton_Y				(ContainerCreationWnd_RECT_BOTTOM - \
															15 - ContainerCreationWnd_applyButton_HEIGHT)


/*		BookmarkManagerWindow		*/

#define BookmarkManagerWnd_RECT_RIGHT	(CommonOperations::getClientRectValue(\
											HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERNWND_WND),\
											ClientRectCoordinates::RIGHT))

#define BookmarkManagerWnd_RECT_BOTTOM	(CommonOperations::getClientRectValue(\
											HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERNWND_WND),\
											ClientRectCoordinates::BOTTOM))

//			mainListView
#define BookmarkManagerWnd_mainListView_X			(5)
#define BookmarkManagerWnd_mainListView_Y			(5)
#define BookmarkManagerWnd_mainListView_WIDTH		(BookmarkManagerWnd_RECT_RIGHT - \
														(2 * BookmarkManagerWnd_mainListView_X))
#define BookmarkManagerWnd_mainListView_HEIGHT		(BookmarkManagerWnd_RECT_BOTTOM - 50)

//			addButton
#define BookmarkManagerWnd_addButton_WIDTH			(100)
#define BookmarkManagerWnd_addButton_HEIGHT			(25)
#define BookmarkManagerWnd_addButton_X				(BookmarkManagerWnd_RECT_RIGHT - \
														7 - BookmarkManagerWnd_addButton_WIDTH)
#define BookmarkManagerWnd_addButton_Y				(BookmarkManagerWnd_RECT_BOTTOM - \
														15 - BookmarkManagerWnd_addButton_HEIGHT)

//			openButton
#define BookmarkManagerWnd_openButton_WIDTH			(100)
#define BookmarkManagerWnd_openButton_HEIGHT		(25)
#define BookmarkManagerWnd_openButton_X				(7)
#define BookmarkManagerWnd_openButton_Y				(BookmarkManagerWnd_RECT_BOTTOM - \
														15 - BookmarkManagerWnd_openButton_HEIGHT)

//			cleanButton
#define BookmarkManagerWnd_cleanButton_WIDTH		(100)
#define BookmarkManagerWnd_cleanButton_HEIGHT		(25)
#define BookmarkManagerWnd_cleanButton_X			(12 + BookmarkManagerWnd_openButton_WIDTH)
#define BookmarkManagerWnd_cleanButton_Y			(BookmarkManagerWnd_RECT_BOTTOM - \
														15 - BookmarkManagerWnd_cleanButton_HEIGHT)

#endif
