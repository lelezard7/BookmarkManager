/**
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
#ifndef _POSITION_AND_SIZE_CONTROLS_
#define _POSITION_AND_SIZE_CONTROLS_

#include "..\HandleManager\HandleManager.h"
#include "CommonOperations.h"
#include "BkmDef.h"
#include "Debug.h"


/*		ContainerCreationWindow		*/

#define ContainerCreationWnd_Rect_Right		(getClientRectValue(\
											HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_WND),\
											ClientRectCoordinates::RIGHT))

#define ContainerCreationWnd_Rect_Bottom	(getClientRectValue(\
											HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_WND),\
											ClientRectCoordinates::BOTTOM))

//			taskTypeComboBox
#define ContainerCreationWnd_TaskTypeComboBox_Width		(150)
#define ContainerCreationWnd_TaskTypeComboBox_Height	(15)
#define ContainerCreationWnd_TaskTypeComboBox_X			(ContainerCreationWnd_Rect_Right - \
														    6 - ContainerCreationWnd_TaskTypeComboBox_Width)
#define ContainerCreationWnd_TaskTypeComboBox_Y			(10)

//			taskTypeHelpText
#define ContainerCreationWnd_TaskTypeHelpText_Width		(85)
#define ContainerCreationWnd_TaskTypeHelpText_Height	(ContainerCreationWnd_TaskTypeComboBox_Height)
#define ContainerCreationWnd_TaskTypeHelpText_X			(ContainerCreationWnd_TaskTypeComboBox_X - \
															(5 + ContainerCreationWnd_TaskTypeHelpText_Width))
#define ContainerCreationWnd_TaskTypeHelpText_Y			(ContainerCreationWnd_TaskTypeComboBox_Y + \
															((ContainerCreationWnd_TaskTypeComboBox_Y / 2) / 2))

//			nameTextBox
#define ContainerCreationWnd_NameTextBox_Width			((ContainerCreationWnd_Rect_Right / 2) - 4)
#define ContainerCreationWnd_NameTextBox_Height			(23)
#define ContainerCreationWnd_NameTextBox_X				(5)
#define ContainerCreationWnd_NameTextBox_Y				(12 + ContainerCreationWnd_TaskTypeComboBox_Y + \
														    ContainerCreationWnd_TaskTypeComboBox_Height)

//			taskTextBox
#define ContainerCreationWnd_TaskTextBox_Width			((ContainerCreationWnd_Rect_Right / 2) - 9)
#define ContainerCreationWnd_TaskTextBox_Height			(23)
#define ContainerCreationWnd_TaskTextBox_X				(4 + (ContainerCreationWnd_Rect_Right / 2))
#define ContainerCreationWnd_TaskTextBox_Y				(12 + ContainerCreationWnd_TaskTypeComboBox_Y + \
															ContainerCreationWnd_TaskTypeComboBox_Height)

//			tagsTextBox
#define ContainerCreationWnd_TagsTextBox_Width			(ContainerCreationWnd_Rect_Right - 55)
#define ContainerCreationWnd_TagsTextBox_Height			(23)
#define ContainerCreationWnd_TagsTextBox_X				(5)
#define ContainerCreationWnd_TagsTextBox_Y				(5 + ContainerCreationWnd_TaskTextBox_Y + \
														    ContainerCreationWnd_TaskTextBox_Height)

//			tagsListView
#define ContainerCreationWnd_TagsListView_X				(5)
#define ContainerCreationWnd_TagsListView_Y				(3 + ContainerCreationWnd_TagsTextBox_Y + \
														    ContainerCreationWnd_TagsTextBox_Height)
#define ContainerCreationWnd_TagsListView_Width			(ContainerCreationWnd_Rect_Right - 10)
#define ContainerCreationWnd_TagsListView_Height		(ContainerCreationWnd_Rect_Bottom - \
														    50 - ContainerCreationWnd_TagsListView_Y)

//			applyButton
#define ContainerCreationWnd_ApplyButton_Width			(100)
#define ContainerCreationWnd_ApplyButton_Height			(25)
#define ContainerCreationWnd_ApplyButton_X				(ContainerCreationWnd_Rect_Right - \
														    7 - ContainerCreationWnd_ApplyButton_Width)
#define ContainerCreationWnd_ApplyButton_Y				(ContainerCreationWnd_Rect_Bottom - \
														    15 - ContainerCreationWnd_ApplyButton_Height)

//			applyTagButton
#define ContainerCreationWnd_ApplyTagButton_Width		(41)
#define ContainerCreationWnd_ApplyTagButton_Height		(23)
#define ContainerCreationWnd_ApplyTagButton_X			(ContainerCreationWnd_Rect_Right - \
														    6 - ContainerCreationWnd_ApplyTagButton_Width)
#define ContainerCreationWnd_ApplyTagButton_Y			(ContainerCreationWnd_TagsTextBox_Y)
															


/*		BookmarkManagerWindow		*/

#define BookmarkManagerWnd_Rect_Right	(getClientRectValue(\
											HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_WND),\
											ClientRectCoordinates::RIGHT))

#define BookmarkManagerWnd_Rect_Bottom	(getClientRectValue(\
											HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_WND),\
											ClientRectCoordinates::BOTTOM))

//			mainListView
#define BookmarkManagerWnd_MainListView_X			(5)
#define BookmarkManagerWnd_MainListView_Y			(5)
#define BookmarkManagerWnd_MainListView_Width		(BookmarkManagerWnd_Rect_Right - \
													    (2 * BookmarkManagerWnd_MainListView_X))
#define BookmarkManagerWnd_MainListView_Height		(BookmarkManagerWnd_Rect_Bottom - 50)

//			addButton
#define BookmarkManagerWnd_AddButton_Width			(100)
#define BookmarkManagerWnd_AddButton_Height			(25)
#define BookmarkManagerWnd_AddButton_X				(BookmarkManagerWnd_Rect_Right - \
													    7 - BookmarkManagerWnd_AddButton_Width)
#define BookmarkManagerWnd_AddButton_Y				(BookmarkManagerWnd_Rect_Bottom - \
													    15 - BookmarkManagerWnd_AddButton_Height)

//			openButton
#define BookmarkManagerWnd_OpenButton_Width			(100)
#define BookmarkManagerWnd_OpenButton_Height		(25)
#define BookmarkManagerWnd_OpenButton_X				(7)
#define BookmarkManagerWnd_OpenButton_Y				(BookmarkManagerWnd_Rect_Bottom - \
													    15 - BookmarkManagerWnd_OpenButton_Height)

//			clearButton
#define BookmarkManagerWnd_ClearButton_Width		(100)
#define BookmarkManagerWnd_ClearButton_Height		(25)
#define BookmarkManagerWnd_ClearButton_X			(12 + BookmarkManagerWnd_OpenButton_Width)
#define BookmarkManagerWnd_ClearButton_Y			(BookmarkManagerWnd_Rect_Bottom - \
													    15 - BookmarkManagerWnd_ClearButton_Height)

#endif
