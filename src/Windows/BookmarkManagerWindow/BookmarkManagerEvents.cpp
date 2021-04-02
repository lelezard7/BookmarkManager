#define UNICODE

#include "..\..\ApplicationSettings\ApplicationSettings.h"
#include "..\..\Common\PositionAndSizeControls.h"
#include "..\..\HandleManager\HandleManager.h"
#include "..\..\Archive\Archive.h"
#include "..\..\Common\BkmDef.h"
#include "..\..\Common\Debug.h"
#include "..\..\res\res.h"
#include "..\ContainerCreationWindow\ContainerCreationWindow.h"
#include "..\AboutProgramWindow\AboutProgramWindow.h"
#include "BookmarkManagerEvents.h"
#include <SaveModule.h>
#include <CommCtrl.h>
#include <HtmlHelp.h>

//static PWSTR pCmdLine;


static size_t mainListView_getSelectedId()
{
	HWND hWnd = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MAINLISTVIEW);
	size_t index = ListView_GetNextItem(hWnd, -1, LVNI_SELECTED);

	PWSTR buffer_id = new WCHAR[0xF4240];  //TODO: Сделать нормальное ограничение размеров во всей программе.
	ListView_GetItemText(hWnd, index, 0, buffer_id, 0xF4240);

	size_t id = std::stoull(buffer_id);
	delete[] buffer_id;

	return id;
}

LRESULT bkmManagerWnd_initialization(PWSTR pCmdLine)
{
	//::pCmdLine = pCmdLine;
	if (wcslen(pCmdLine) != 0)
		bkmManagerWnd_menu_file_open(pCmdLine);

	return 0;
}

LRESULT bkmManagerWnd_adjustmentControls(HWND hWnd)
{
	HWND hMainListView = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MAINLISTVIEW);
	HWND hAddButton = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_ADDBUTTON);
	HWND hOpenButton = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_OPENBUTTON);
	HWND hClearButton = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_CLEARBUTTON);

	SetWindowPos(hMainListView, HWND_TOP, BookmarkManagerWnd_MainListView_X,
		BookmarkManagerWnd_MainListView_Y,
		BookmarkManagerWnd_MainListView_Width,
		BookmarkManagerWnd_MainListView_Height, NULL);
	SetWindowPos(hAddButton, HWND_TOP, BookmarkManagerWnd_AddButton_X,
		BookmarkManagerWnd_AddButton_Y,
		BookmarkManagerWnd_AddButton_Width,
		BookmarkManagerWnd_AddButton_Height, NULL);
	SetWindowPos(hOpenButton, HWND_TOP, BookmarkManagerWnd_OpenButton_X,
		BookmarkManagerWnd_OpenButton_Y,
		BookmarkManagerWnd_OpenButton_Width,
		BookmarkManagerWnd_OpenButton_Height, NULL);
	SetWindowPos(hClearButton, HWND_TOP, BookmarkManagerWnd_ClearButton_X,
		BookmarkManagerWnd_ClearButton_Y,
		BookmarkManagerWnd_ClearButton_Width,
		BookmarkManagerWnd_ClearButton_Height, NULL);

	ListView_SetColumnWidth(hMainListView, 1, BookmarkManagerWnd_MainListView_Width / 2);
	ListView_SetColumnWidth(hMainListView, 2, BookmarkManagerWnd_MainListView_Width / 2);

	return 0;
}

LRESULT showCreatedContainer(WPARAM wParam)
{
	HWND hWnd = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MAINLISTVIEW);

	LVITEM lvitem = { NULL };
	lvitem.mask = LVIF_TEXT;

	std::wstring buffer = std::to_wstring(wParam);
	lvitem.pszText = (LPWSTR)buffer.c_str();
	ListView_InsertItem(hWnd, &lvitem);
	buffer.clear();

	Container* container = Archive::getContainer(wParam);
	lvitem.iSubItem = 1;
	lvitem.pszText = container->getName();
	ListView_SetItem(hWnd, &lvitem);

	lvitem.iSubItem = 2;
	lvitem.pszText = container->getTask();
	ListView_SetItem(hWnd, &lvitem);

	return 0;
}



LRESULT bkmManagerWnd_ClearMainListView(HWND hWnd)
{
	HWND hMainLv = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MAINLISTVIEW);

	if (ListView_GetItemCount(hMainLv) == 0)
		return 0;

	if (MessageBox(hWnd, L"Вы действительно хотите очистить весь список?",
		L"Bookmark Manager", MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		ListView_DeleteAllItems(hMainLv);
		Archive::clear();
	}

	return 0;
}

LRESULT bkmManagerWnd_startСontainer(HWND hWnd)
{
	HWND hMainLv = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MAINLISTVIEW);
	size_t index = ListView_GetNextItem(hMainLv, -1, LVNI_SELECTED);

	if (index == -1 || GetFocus() != hMainLv)
		return 0;

	Archive_Id id = mainListView_getSelectedId();
	Container* container = Archive::getContainer(id);

	if (!container) {
		std::wstring errMessage = L"Не удалось запустить контейнер. Контейнер с ID: " +
			std::to_wstring(id) + L" не найден!";
		MessageBox(hWnd, errMessage.c_str(), L"Bookmark Manager", MB_OK | MB_ICONWARNING);

		return 0;
	}

	container->start();

	return 0;
}

LRESULT bkmManagerWnd_delete_pressed(HWND hWnd)
{
	HWND hMainLv = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MAINLISTVIEW);
	size_t index = ListView_GetNextItem(hMainLv, -1, LVNI_SELECTED);

	if (index == -1 || GetFocus() != hMainLv)
		return 0;

	Archive_Id id = mainListView_getSelectedId();

	if (Archive::deleteContainer(id)) {
		ListView_DeleteItem(hMainLv, index);
	}
	else {
		std::wstring errMessage = L"Не удалось удалить контейнер. Контейнер с ID: " +
			std::to_wstring(id) + L" не найден!";
		MessageBox(hWnd, errMessage.c_str(), L"Bookmark Manager", MB_OK | MB_ICONWARNING);
	}

	return 0;
}

LRESULT bkmManagerWnd_addButton_pressed(HWND hWnd)
{
	LaunchMethod launchMethod = ApplicationSettings::getLaunchMethodContainerCreationWindow();

	if (launchMethod == LaunchMethod::SHOW_CLOSED_WINDOW ||
		launchMethod == LaunchMethod::CONTINUE_UNFINISHED_CREATION)
	{
		if (HandleManager::checkExistence(HNAME_CONTAINERCREATIONWND_WND))
		{
			HWND hContCreatWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_WND);
			ShowWindow(hContCreatWnd, true);

			EnableWindow(hWnd, false);

			return 0;
		}
	}

	create_containerCreationWindow(GetModuleHandle(NULL));

	return 0;
}



LRESULT bkmManagerWnd_menu_help_howToUse(HWND hWnd)
{
	HWND hHelpWnd = HtmlHelp(hWnd, L"BookmarkManager.chm", HH_DISPLAY_TOPIC, NULL);

	if (hHelpWnd) {
		moveWindowToCenterScreen(hHelpWnd);
		return 0;
	}

	size_t length = GetCurrentDirectory(NULL, NULL);
	PWSTR buffer = new WCHAR[length];

	GetCurrentDirectory(length, buffer);
	std::wstring errMessage = L"Не удалось найти файл справки: \"" + std::wstring(buffer) +
		L"\\BookmarkManager.chm\"";
	delete[] buffer;

	MessageBox(hWnd, errMessage.c_str(), L"Bookmark Manager", MB_OK | MB_ICONWARNING);

	return 0;
}

LRESULT bkmManagerWnd_menu_help_aboutProg(HWND hWnd)
{
	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(BKM_ABOUTWND), hWnd, AboutProc);

	return 0;
}

LRESULT bkmManagerWnd_menu_file_close(HWND hWnd)
{
	PostMessage(hWnd, WM_CLOSE, NULL, NULL);

	return 0;
}

LRESULT bkmManagerWnd_menu_file_save() //TODO: clear memory.
{
	Tag mainTag;

	mainTag.setName(L"BookmarkManager");
	mainTag.setFlag(TF_SUBTAGS);
	mainTag.addAttribute(L"SaveVer", SAVEMODULE_VERSIONNAME);
	mainTag.addAttribute(L"BkmVer", BOOKMARKMANAGER_VERSIONNAME);

	Tag* archiveTag = mainTag.createSubTag(0);
	{
		archiveTag->setName(L"archive");
		archiveTag->setFlag(TF_SUBTAGS);

		Tag* archiveInfoTag = archiveTag->createSubTag(1);
		{
			archiveInfoTag->setFlag(TF_VALUE);
			archiveInfoTag->setName(L"maxId");
			archiveInfoTag->setValue(std::to_wstring(Archive::getMaxId()));

			archiveTag->applySubTag(1);
		}

		archiveInfoTag = archiveTag->createSubTag(1);
		{
			archiveInfoTag->setFlag(TF_SUBTAGS);
			archiveInfoTag->setName(L"NextIdGroup");
			
			for (size_t i = 0; i < Archive::nextIdCount(); ++i)
			{
				Tag* nextIdTag = archiveInfoTag->createSubTag(2);
				{
					nextIdTag->setFlag(TF_VALUE);
					nextIdTag->setName(L"nextId");
					nextIdTag->setValue(std::to_wstring(Archive::getNextId(i)));

					archiveInfoTag->applySubTag(2);
				}
			}

			archiveTag->applySubTag(1);
		}

		for (size_t i = 0; i < Archive::size(); ++i)
		{
			Tag* containerTag = archiveTag->createSubTag(1);
			{
				Archive_Id containerId = Archive::getIdByIndex(i);
				Container* container = Archive::getContainer(containerId);

				containerTag->setName(L"container");
				containerTag->setFlag(TF_SUBTAGS);
				containerTag->addAttribute(L"id", std::to_wstring(containerId));


				Tag* containeDataTypesTag[4];
				containeDataTypesTag[0] = containerTag->createSubTag(5);
				containeDataTypesTag[1] = containerTag->createSubTag(6);
				containeDataTypesTag[2] = containerTag->createSubTag(7);
				containeDataTypesTag[3] = containerTag->createSubTag(8);
				{
					containeDataTypesTag[0]->setName(L"name");
					containeDataTypesTag[0]->setFlag(TF_VALUE);
					std::wstring buffer = container->getName();
					containeDataTypesTag[0]->setValue(std::wstring(buffer.begin(), buffer.end()));

					containeDataTypesTag[1]->setName(L"task");
					containeDataTypesTag[1]->setFlag(TF_VALUE);
					buffer = container->getTask();
					containeDataTypesTag[1]->setValue(std::wstring(buffer.begin(), buffer.end()));

					containeDataTypesTag[2]->setName(L"taskType");
					containeDataTypesTag[2]->setFlag(TF_VALUE);
					TaskType taskType = container->getTaskType();
					containeDataTypesTag[2]->setValue(std::to_wstring(taskType));

					containeDataTypesTag[3]->setName(L"TagsGroup");
					containeDataTypesTag[3]->setFlag(TF_SUBTAGS);

					int index = 0;
					while (container->getTag(index) != nullptr)
					{
						Tag* tagTag = containeDataTypesTag[3]->createSubTag(10);
						{
							tagTag->setName(L"tag");
							tagTag->setFlag(TF_VALUE);
							buffer = container->getTag(index);
							tagTag->setValue(std::wstring(buffer.begin(), buffer.end()));

							containeDataTypesTag[3]->applySubTag(10);
						}
						index++;
					}

					containerTag->applyAllSubTags();
				}

				archiveTag->applySubTag(1);
			}
		}

		mainTag.applySubTag(0);
	}

	XmlFile newXmlFile;

	newXmlFile.open(L"dfd.bkm", OpenMode::WRITE); //TODO:Удалять пробелы из tagsListView.
	newXmlFile.write(mainTag);
	newXmlFile.close();


	//Tag ddd;
	//ddd.setName(L"name");

	//XmlFilter f;
	//f.setTarget(mainTag);
	//f.setFilter(ddd);
	//f.setFlags(XFF_NAME);
	//SearchResult _searchResult = f.search();

	//TagStructure filter;
	//filter.setValue("rrr");
	//filter.setTag("tag");

	//TagPath tagPath;
	//tagPath.setFlags(TPF_VALUE | TPF_TAG);
	//tagPath.setTagStructure(mainTag);
	//auto d = tagPath.search(filter);


	//TagStructure f = tagPath.getRootTag(0);
	//TagStructure k = tagPath.getRootTag(2);
	//TagStructure h = tagPath.getRootTag(1);
	//TagStructure z = tagPath.getRootTag(90);
	//TagStructure j = tagPath.getRootTag(3);

	//tagPath.setTagStructure(mainTag);
	//TagStructure f = tagPath.getTag(0);
	//TagStructure g = tagPath.getTag(1);
	//TagStructure j = tagPath.getTag(100);
	//TagStructure p = tagPath.getTag(3);

	//TagStructure u = tagPath.getAllTag(0);
	//TagStructure m = tagPath.getAllTag(3);
	//TagStructure n = tagPath.getAllTag(6);
	//TagStructure o = tagPath.getAllTag(80);
	//TagStructure y = tagPath.getAllTag(1);

	return 0;
}

LRESULT bkmManagerWnd_menu_file_open(PWSTR path)
{
	XmlFile newXmlFile;

	if (wcslen(path) != 0)
	{
		std::wstring path_ = path;
		newXmlFile.open(path_, OpenMode::READ);
		Tag mainTag = newXmlFile.read();
		newXmlFile.close();
	}

	newXmlFile.open(L"dfd.bkm", OpenMode::READ);
	Tag mainTag = newXmlFile.read();
	newXmlFile.close();

	Tag filter;
	XmlFilter tagSearch;
	SearchResult searchResult;
	tagSearch.setTarget(mainTag);

	filter.setName(L"maxId");
	tagSearch.setFlags(XFF_NAME);
	tagSearch.setFilter(filter);
	searchResult = tagSearch.search();

	Tag tg1 = searchResult.getTag(0);
	int maxId = std::stoi(tg1.getValue());
	searchResult.clear();

	filter.setName(L"nextId");
	tagSearch.setFlags(XFF_NAME);
	tagSearch.setFilter(filter);
	searchResult = tagSearch.search();

	std::vector<Archive_Id> nextId;
	for (int i = 0; i < searchResult.size(); ++i)
	{
		Tag tg2 = searchResult.getTag(i);
		nextId.push_back(std::stoi(tg2.getValue()));
	}

	Archive::initialization(maxId, nextId);
	searchResult.clear();


	filter.setName(L"container");
	tagSearch.setFlags(XFF_NAME);
	tagSearch.setFilter(filter);
	searchResult = tagSearch.search();

	for (int i = 0; i < searchResult.size(); ++i)
	{
		Container container;

		Tag __tag = searchResult.getTag(i);
		Tag subTag = __tag.getSubTag(0);
		std::wstring dd = subTag.getValue();
		PWSTR buffer = (PWSTR)dd.c_str();
		container.setName(buffer, subTag.getValue().size() + 1);

		subTag = __tag.getSubTag(1);
		dd = subTag.getValue();
		buffer = (PWSTR)dd.c_str();
		container.setTask(buffer, subTag.getValue().size() + 1);

		subTag = __tag.getSubTag(2);
		container.setTaskType(std::stoi(subTag.getValue()));

		subTag = __tag.getSubTag(3);
		for (int j = 0; j < subTag.subTagsCount(); ++j)
		{
			Tag tagTag = subTag.getSubTag(j);
			dd = tagTag.getValue();
			buffer = (PWSTR)dd.c_str();
			container.addTag(buffer);
		}

		Archive_Id id = std::stoi(__tag.getAttributeValue(L"id"));
		Archive::addContainer(container, id, Archive::AddContainerMode::INITIALIZATION);

		HWND hWndParent = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_WND);
		SendMessage(hWndParent, UM_SHOWCREATEDCONTAINER, id, NULL);
	}

	return 0;
}



LRESULT bkmManagerWnd_closeProgram(HWND hWnd)
{
	DestroyWindow(hWnd);

	return 0;
}

LRESULT bkmManagerWnd_destroyWindow()
{
	PostQuitMessage(0);

	return 0;
}
