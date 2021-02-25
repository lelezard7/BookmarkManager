/*
*		The position and size of the controls are set here.
*		This will make it easier to add new controls and update existing controls.
*/

#pragma once
#ifndef _POSITIONANDSIZECONTROLS_
#define _POSITIONANDSIZECONTROLS_

#include "CommonOperations.h"
#include "..\HandleManager\HandleManager.h"


/*		ContainerCreationWindow		*/

#define ContainerCreationWnd_RECT_RIGHT		(CommonOperations::getClientRectValue(\
											*HandleManager::getHandleWnd(L"containerCreationWindow_wnd"),\
											ClientRectCoordinates::RIGHT))

#define ContainerCreationWnd_RECT_BOTTOM	(CommonOperations::getClientRectValue(\
											*HandleManager::getHandleWnd(L"containerCreationWindow_wnd"),\
											ClientRectCoordinates::BOTTOM))

//			taskTypeDropDList

#define ContainerCreationWnd_taskTypeDropDList_X		((ContainerCreationWnd_RECT_RIGHT / 2) + 4)
#define ContainerCreationWnd_taskTypeDropDList_Y		(15)
#define ContainerCreationWnd_taskTypeDropDList_WIDTH	(100)
#define ContainerCreationWnd_taskTypeDropDList_HEIGHT	(15)

//			nameTextBox
#define ContainerCreationWnd_nameTextBox_X				(5)
#define ContainerCreationWnd_nameTextBox_Y				(30)
#define ContainerCreationWnd_nameTextBox_WIDTH			((ContainerCreationWnd_RECT_RIGHT / 2) - 4)
#define ContainerCreationWnd_nameTextBox_HEIGHT			(25)

//			adressTextBox
#define ContainerCreationWnd_adressTextBox_X			((ContainerCreationWnd_RECT_RIGHT / 2) + 4)
#define ContainerCreationWnd_adressTextBox_Y			(30)
#define ContainerCreationWnd_adressTextBox_WIDTH		((ContainerCreationWnd_RECT_RIGHT / 2) - 9)
#define ContainerCreationWnd_adressTextBox_HEIGHT		(25)

//			tagsTextBox
#define ContainerCreationWnd_tagsTextBox_X				(5)
#define ContainerCreationWnd_tagsTextBox_Y				(55)
#define ContainerCreationWnd_tagsTextBox_WIDTH			(ContainerCreationWnd_RECT_RIGHT - 10)
#define ContainerCreationWnd_tagsTextBox_HEIGHT			(25)

//			applyButton
#define ContainerCreationWnd_applyButton_X				(ContainerCreationWnd_RECT_RIGHT - 107)
#define ContainerCreationWnd_applyButton_Y				(ContainerCreationWnd_RECT_BOTTOM - 40)
#define ContainerCreationWnd_applyButton_WIDTH			(100)
#define ContainerCreationWnd_applyButton_HEIGHT			(25)

//			tagsListView
#define ContainerCreationWnd_tagsListView_X				(5)
#define ContainerCreationWnd_tagsListView_Y				(85)
#define ContainerCreationWnd_tagsListView_WIDTH			(ContainerCreationWnd_RECT_RIGHT - 10)
#define ContainerCreationWnd_tagsListView_HEIGHT		((ContainerCreationWnd_RECT_BOTTOM - 85) - 80)


/*		BookmarkManagerWindow		*/

#define BookmarkManagerWindow_RECT_RIGHT	(CommonOperations::getClientRectValue(\
											*HandleManager::getHandleWnd(L"bookmarkManagerWindow_wnd"),\
											ClientRectCoordinates::RIGHT))

#define BookmarkManagerWindow_RECT_BOTTOM	(CommonOperations::getClientRectValue(\
											*HandleManager::getHandleWnd(L"bookmarkManagerWindow_wnd"),\
											ClientRectCoordinates::BOTTOM))

//			mainListView
#define BookmarkManagerWnd_mainListView_X				(5)
#define BookmarkManagerWnd_mainListView_Y				(5)
#define BookmarkManagerWnd_mainListView_WIDTH			(BookmarkManagerWindow_RECT_RIGHT - 10)
#define BookmarkManagerWnd_mainListView_HEIGHT			(BookmarkManagerWindow_RECT_BOTTOM - 50)

//			addButton
#define BookmarkManagerWnd_addButton_X					(BookmarkManagerWindow_RECT_RIGHT - 107)
#define BookmarkManagerWnd_addButton_Y					(BookmarkManagerWindow_RECT_BOTTOM - 40)
#define BookmarkManagerWnd_addButton_WIDTH				(100)
#define BookmarkManagerWnd_addButton_HEIGHT				(25)

//			openButton
#define BookmarkManagerWnd_openButton_X					(7)
#define BookmarkManagerWnd_openButton_Y					(BookmarkManagerWindow_RECT_BOTTOM - 40)
#define BookmarkManagerWnd_openButton_WIDTH				(100)
#define BookmarkManagerWnd_openButton_HEIGHT			(25)

//			cleanButton
#define BookmarkManagerWnd_cleanButton_X				(112)
#define BookmarkManagerWnd_cleanButton_Y				(BookmarkManagerWindow_RECT_BOTTOM - 40)
#define BookmarkManagerWnd_cleanButton_WIDTH			(100)
#define BookmarkManagerWnd_cleanButton_HEIGHT			(25)


#endif
