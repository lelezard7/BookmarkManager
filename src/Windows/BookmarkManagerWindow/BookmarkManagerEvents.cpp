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
	TagStructure mainTag;

	mainTag.setTag("BookmarkManager");
	mainTag.setFlag(TSF_SUBTAGS);
	std::wstring newVerName = SAVEMODULE_VERSIONNAME;
	mainTag.addAttribute("SaveVer", std::string(newVerName.begin(), newVerName.end()));
	std::wstring newVer = BOOKMARKMANAGER_VERSIONNAME;
	mainTag.addAttribute("BkmVer", std::string(newVer.begin(), newVer.end()));

	TagStructure* archiveTag = new TagStructure;
	mainTag.addSubTag(archiveTag);
	{
		archiveTag->setTag("archive");
		archiveTag->setFlag(TSF_SUBTAGS);

		TagStructure* archiveInfoTag[2];
		archiveInfoTag[0] = new TagStructure;
		archiveTag->addSubTag(archiveInfoTag[0]);
		{
			archiveInfoTag[0]->setFlag(TSF_VALUE);
			archiveInfoTag[0]->setTag("maxId");
			archiveInfoTag[0]->setValue(std::to_string(Archive::getMaxId()));
		}

		for (size_t i = 0; i < Archive::getNextIdCount(); ++i)
		{
			archiveInfoTag[1] = new TagStructure;
			archiveTag->addSubTag(archiveInfoTag[1]);
			{
				archiveInfoTag[1]->setFlag(TSF_VALUE);
				archiveInfoTag[1]->setTag("nextId");
				archiveInfoTag[1]->setValue(std::to_string(Archive::getNextId(i)));
			}
		}

		size_t archiveSize = Archive::size();
		for (size_t i = 0; i < archiveSize; ++i)
		{
			TagStructure* containerTag = new TagStructure;
			archiveTag->addSubTag(containerTag);
			{
				Archive_Id containerId = Archive::getIdByIndex(i);
				Container* container = Archive::getContainer(containerId);

				containerTag->setTag("container");
				containerTag->setFlag(TSF_SUBTAGS);
				containerTag->addAttribute("id", std::to_string(containerId));

				TagStructure* containeDataTypesTag[4];
				containeDataTypesTag[0] = new TagStructure;
				containeDataTypesTag[1] = new TagStructure;
				containeDataTypesTag[2] = new TagStructure;
				containeDataTypesTag[3] = new TagStructure;

				containerTag->addSubTag(containeDataTypesTag[0]);
				containerTag->addSubTag(containeDataTypesTag[1]);
				containerTag->addSubTag(containeDataTypesTag[2]);
				containerTag->addSubTag(containeDataTypesTag[3]);
				{
					containeDataTypesTag[0]->setTag("name");
					containeDataTypesTag[0]->setFlag(TSF_VALUE);
					std::wstring buffer = container->getName();
					containeDataTypesTag[0]->setValue(std::string(buffer.begin(), buffer.end()));

					containeDataTypesTag[1]->setTag("task");
					containeDataTypesTag[1]->setFlag(TSF_VALUE);
					buffer = container->getTask();
					containeDataTypesTag[1]->setValue(std::string(buffer.begin(), buffer.end()));

					containeDataTypesTag[2]->setTag("taskType");
					containeDataTypesTag[2]->setFlag(TSF_VALUE);
					TaskType taskType = container->getTaskType();
					containeDataTypesTag[2]->setValue(std::to_string(taskType));

					containeDataTypesTag[3]->setTag("TagsGroup");
					containeDataTypesTag[3]->setFlag(TSF_SUBTAGS);

					TagStructure* tagTag = new TagStructure;
					int index = 0;

					while (container->getTag(index) != nullptr)
					{
						containeDataTypesTag[3]->addSubTag(tagTag);
						{
							tagTag->setTag("tag");
							tagTag->setFlag(TSF_VALUE);
							buffer = container->getTag(index);
							tagTag->setValue(std::string(buffer.begin(), buffer.end()));
						}
						index++;
					}
				}
			}
		}
	}

	openXmlFile("dfd.bkm", XMLFILE_WRITE); //TODO:Удалять пробелы из tagsListView.
	saveXmlFile(mainTag);
	closeXmlFile("dfd.bkm");

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
	if (wcslen(path) != 0)
	{
		std::wstring path_ = path;
		std::string path2_ = std::string(path_.begin(), path_.end());
		openXmlFile(path2_, XMLFILE_READ);
		TagStructure* mainTag = readXmlFile();
		closeXmlFile(path2_);
	}

	openXmlFile("dfd.bkm", XMLFILE_READ);
	TagStructure* mainTag = readXmlFile();
	closeXmlFile("dfd.bkm");

	TagStructure filter;
	TagPath tagSearch;
	std::vector<TagStructure*> searchResult;
	tagSearch.setTagStructure(*mainTag);

	filter.setTag("maxId");
	tagSearch.setFlags(TPF_TAG);
	searchResult = tagSearch.search(filter);

	int maxId = std::stoi(searchResult[0]->getValue());
	searchResult.clear();

	filter.setTag("nextId");
	tagSearch.setFlags(TPF_TAG);
	searchResult = tagSearch.search(filter);

	std::vector<Archive_Id> nextId;
	for (int i = 0; i < searchResult.size(); ++i)
	{
		nextId.push_back(std::stoi(searchResult[i]->getValue()));
	}

	Archive::initialization(maxId, nextId);
	searchResult.clear();


	filter.setTag("container");
	tagSearch.setFlags(TPF_TAG);
	searchResult = tagSearch.search(filter);

	for (int i = 0; i < searchResult.size(); ++i)
	{
		Container container;

		TagStructure* subTag = searchResult[i]->getSubTag(0);
		std::string vv = subTag->getValue();
		std::wstring dd = std::wstring(vv.begin(), vv.end());
		PWSTR buffer = (PWSTR)dd.c_str();
		container.setName(buffer, subTag->getValue().size() + 1);

		subTag = searchResult[i]->getSubTag(1);
		vv = subTag->getValue();
		dd = std::wstring(vv.begin(), vv.end());
		buffer = (PWSTR)dd.c_str();
		container.setTask(buffer, subTag->getValue().size() + 1);

		subTag = searchResult[i]->getSubTag(2);
		container.setTaskType(std::stoi(subTag->getValue()));

		subTag = searchResult[i]->getSubTag(3);
		for (int j = 0; j < subTag->subTagSize(); ++j)
		{
			TagStructure* tagTag = subTag->getSubTag(j);
			vv = tagTag->getValue();
			dd = std::wstring(vv.begin(), vv.end());
			buffer = (PWSTR)dd.c_str();
			container.addTag(buffer);
		}

		Archive_Id id = std::stoi(searchResult[i]->getAttribute("id"));
		Archive::addContainer(container, id);

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
