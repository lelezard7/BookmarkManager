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

static bool isProgramChanged = false;


static void changeProgramState(bool state)
{
	isProgramChanged = state;
	HWND hWndParent = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_WND);

	if (state == true)
		SetWindowText(hWndParent, L"Bookmark Manager*");
	else
		SetWindowText(hWndParent, L"Bookmark Manager");
}

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

	changeProgramState(true);

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

LRESULT bkmManagerWnd_menu_file_save()
{
	Tag rootTag;
	rootTag.setName(L"BookmarkManager");
	rootTag.setFlag(TF_SUBTAGS);
	rootTag.addAttribute(L"SaveVer", SAVEMODULE_VERSIONNAME);
	rootTag.addAttribute(L"BkmVer", BOOKMARKMANAGER_VERSIONNAME);

	Tag* archiveTag = rootTag.createSubTag(0);
	{
		archiveTag->setName(L"archive");
		archiveTag->setFlag(TF_SUBTAGS);

		Tag* archiveInfoTag = archiveTag->createSubTag(1);
		{
			archiveInfoTag->setName(L"maxId");
			archiveInfoTag->setValue(std::to_wstring(Archive::getMaxId()));

			archiveTag->applySubTag(1);
		}

		if (Archive::nextIdCount() != 0)
		{
			archiveInfoTag = archiveTag->createSubTag(1);
			{
				archiveInfoTag->setFlag(TF_SUBTAGS);
				archiveInfoTag->setName(L"NextIdGroup");

				for (size_t i = 0; i < Archive::nextIdCount(); ++i)
				{
					Tag* nextIdTag = archiveInfoTag->createSubTag(2);
					{
						nextIdTag->setName(L"nextId");
						nextIdTag->setValue(std::to_wstring(Archive::getNextId(i)));

						archiveInfoTag->applySubTag(2);
					}
				}

				archiveTag->applySubTag(1);
			}
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
				{
					containeDataTypesTag[0]->setName(L"name");
					std::wstring buffer = container->getName();
					containeDataTypesTag[0]->setValue(std::wstring(buffer.begin(), buffer.end()));

					containeDataTypesTag[1]->setName(L"task");
					buffer = container->getTask();
					containeDataTypesTag[1]->setValue(std::wstring(buffer.begin(), buffer.end()));

					containeDataTypesTag[2]->setName(L"taskType");
					TaskType taskType = container->getTaskType();
					containeDataTypesTag[2]->setValue(std::to_wstring(taskType));

					if (container->tagsCount() != 0)
					{
						containeDataTypesTag[3] = containerTag->createSubTag(8);
						{
							containeDataTypesTag[3]->setName(L"TagsGroup");
							containeDataTypesTag[3]->setFlag(TF_SUBTAGS);

							for (size_t i = 0; i < container->tagsCount(); ++i)
							{
								Tag* tagTag = containeDataTypesTag[3]->createSubTag(10);
								{
									tagTag->setName(L"tag");
									buffer = container->getTag(i);
									tagTag->setValue(std::wstring(buffer.begin(), buffer.end()));

									containeDataTypesTag[3]->applySubTag(10);
								}
							}
						}
					}

					containerTag->applyAllSubTags();
				}

				archiveTag->applySubTag(1);
			}
		}

		rootTag.applySubTag(0);
	}

	XmlFile saveFile;
	saveFile.open(L"dfd.bkm", OpenMode::WRITE);
	saveFile.write(rootTag);
	saveFile.close();

	changeProgramState(false);

	return 0;
}


static LRESULT bkmManagerWnd_menu_file_open_error(HWND hWnd, std::wstring errorMessage);
static bool bkmManagerWnd_menu_file_open_setStandardData(
	HWND hWnd,
	Container* container,
	Tag* containerTag,
	std::wstring searchSubTagName,
	std::wstring errorMessage);
#include <shobjidl_core.h>
LRESULT bkmManagerWnd_menu_file_open(HWND hWnd, PWSTR path)
{
	if (isProgramChanged) {
		int answer = MessageBox(hWnd, L"Сохранить изменения?", L"Bookmark Manager", MB_YESNOCANCEL | MB_ICONQUESTION);
		if (answer == IDYES) {
			bkmManagerWnd_menu_file_save();
		}
		else if (answer == IDCANCEL) {
			return 0;
		}
	}
	changeProgramState(false);
	bkmManagerWnd_menu_file_new(hWnd);






	// CoCreate the File Open Dialog object.
	IFileDialog* pfd = NULL;
	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pfd));
	if (SUCCEEDED(hr))
	{
		// Set the options on the dialog.
		DWORD dwFlags;

		// Before setting, always get the options first in order 
		// not to override existing options.
		hr = pfd->GetOptions(&dwFlags);
		if (SUCCEEDED(hr))
		{
			// In this case, get shell items only for file system items.
			hr = pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);
			if (SUCCEEDED(hr))
			{
				// Set the default extension to be ".doc" file.
				hr = pfd->SetDefaultExtension(L"doc;docx");
				if (SUCCEEDED(hr))
				{
					// Show the dialog
					hr = pfd->Show(NULL);
					if (SUCCEEDED(hr))
					{
						// Obtain the result once the user clicks 
						// the 'Open' button.
						// The result is an IShellItem object.
						IShellItem* psiResult;
						hr = pfd->GetResult(&psiResult);
						if (SUCCEEDED(hr))
						{
							// We are just going to print out the 
							// name of the file for sample sake.
							PWSTR pszFilePath = NULL;
							hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH,
								&pszFilePath);
							if (SUCCEEDED(hr))
							{
								TaskDialog(NULL,
									NULL,
									L"CommonFileDialogApp",
									pszFilePath,
									NULL,
									TDCBF_OK_BUTTON,
									TD_INFORMATION_ICON,
									NULL);
								CoTaskMemFree(pszFilePath);
							}
							psiResult->Release();
						}
					}


				}
			}

		}
		
	}
		pfd->Release();
	







	/*IFileDialog* pfd = NULL;
	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_IFileDialog, (void**)&pfd);

	LPOPENFILENAMEW lpofn;

	GetOpenFileName(lpofn);

	pfd->Release();*/



	Tag rootTag;

	XmlFile saveFile;
	bool errCode;
	if (path != nullptr) {
		errCode = saveFile.open(path);
	}
	else {
		
		errCode = saveFile.open(L"dfd.bkm");
	}

	if (!errCode) {
		saveFile.close();
		MessageBox(hWnd, L"Не удалось открыть файл сохранения!", L"Bookmark Manager", MB_OK | MB_ICONWARNING);
		return 0;
	}
	else {
		rootTag = saveFile.read();
		saveFile.close();
	}

	if (rootTag == Tag()) {
		MessageBox(hWnd, L"Не удалось считать данные из файла сохранения!", L"Bookmark Manager", MB_OK | MB_ICONSTOP);
		return 0;
	}

	XmlFilter filter;
	filter.setTarget(rootTag);
	filter.setFlags(XFF_NAME);

	Tag filterTag;
	SearchResult searchResult;


	filterTag.setName(L"maxId");
	filter.setFilter(filterTag);

	searchResult = filter.search();
	Tag maxIdTag = searchResult.getTag(0);
	if (searchResult == SearchResult() || maxIdTag == Tag()) {
		MessageBox(
			hWnd,
			L"Не удалось считать данные из файла сохранения! Не найденно поле \"maxId.\"",
			L"Bookmark Manager",
			MB_OK | MB_ICONSTOP);
		return 0;
	}

	int maxId = std::stoi(maxIdTag.getValue());
	searchResult.clear();
	filterTag.clear();


	filterTag.setName(L"nextId");
	filter.setFilter(filterTag);
	searchResult = filter.search();

	std::vector<Archive_Id> nextIds;
	for (int i = 0; i < searchResult.size(); ++i) {
		Tag nextIdTag = searchResult.getTag(i);
		nextIds.push_back(std::stoi(nextIdTag.getValue()));
	}

	if (!Archive::initialization(maxId, nextIds)) {
		MessageBox(
			hWnd,
			L"Не удалось инициализировать архив!",
			L"Bookmark Manager",
			MB_OK | MB_ICONSTOP);
		return 0;
	}
	searchResult.clear();
	filterTag.clear();


	filterTag.setName(L"container");
	filter.setFilter(filterTag);
	searchResult = filter.search();

	Tag containerTag;
	Container container;
	Tag subTag;
	std::wstring value;
	for (size_t i = 0; i < searchResult.size(); ++i) {
		containerTag = searchResult.getTag(i);
		
		errCode = bkmManagerWnd_menu_file_open_setStandardData(
			hWnd,
			&container,
			&containerTag,
			L"name",
			L"Не удалось полностью считать данные из файла сохранения! В " +
			std::to_wstring(i + 1) + L"м контейнере не найденно имя.");

		if (errCode == 0)
			return 0;

		errCode = bkmManagerWnd_menu_file_open_setStandardData(
			hWnd,
			&container,
			&containerTag,
			L"task",
			L"Не удалось полностью считать данные из файла сохранения! В " +
			std::to_wstring(i + 1) + L"м контейнере не найдена задача.");

		if (errCode == 0)
			return 0;

		errCode = bkmManagerWnd_menu_file_open_setStandardData(
			hWnd,
			&container,
			&containerTag,
			L"taskType",
			L"Не удалось полностью считать данные из файла сохранения! В " +
			std::to_wstring(i + 1) + L"м контейнере не найден тип задачи.");

		if (errCode == 0)
			return 0;

		for (size_t j = 0; j < 4; ++j) {
			subTag = containerTag.getSubTag(j);

			if (subTag.getName() == L"TagsGroup") {
				for (size_t k = 0; k < subTag.subTagsCount(); ++k)
				{
					Tag tagTag = subTag.getSubTag(k);
					value = tagTag.getValue();
					if (value == L"") {
						return bkmManagerWnd_menu_file_open_error(hWnd,
							L"Не удалось полностью считать данные из файла сохранения! В " +
							std::to_wstring(i + 1) + L"м контейнере " + std::to_wstring(k + 1) +
							L"й тег не имеет имя.");
					}
					container.addTag((PWSTR)value.c_str());
				}
			}
		}

		std::wstring idTagValue = containerTag.getAttributeValue(L"id");
		if(idTagValue == L"") {
			return bkmManagerWnd_menu_file_open_error(hWnd,
				L"Не удалось полностью считать данные из файла сохранения! В " +
				std::to_wstring(i + 1) + L"м контейнере атрибут id не найден или не имеет значения.");
		}

		Archive_Id id = std::stoi(idTagValue);
		if (!Archive::addContainer(container, id, Archive::AddContainerMode::INITIALIZATION)) {
			return bkmManagerWnd_menu_file_open_error(hWnd,
				L"Не удалось полностью считать данные из файла сохранения! В " +
				std::to_wstring(i + 1) + L"м контейнере неверный id.");
		}

		SendMessage(hWnd, UM_SHOWCREATEDCONTAINER, id, NULL);

		containerTag.clear();
		container.clear();
		subTag.clear();
	}

	changeProgramState(false);

	return 0;
}

static LRESULT bkmManagerWnd_menu_file_open_error(HWND hWnd, std::wstring errorMessage)
{
	Archive::close();

	HWND hMainListView = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MAINLISTVIEW);
	ListView_DeleteAllItems(hMainListView);

	MessageBox(hWnd, errorMessage.c_str(), L"Bookmark Manager", MB_OK | MB_ICONSTOP);

	return 0;
}

static bool bkmManagerWnd_menu_file_open_setStandardData(
	HWND hWnd,
	Container* container,
	Tag* containerTag,
	std::wstring searchSubTagName,
	std::wstring errorMessage)
{
	Tag subTag;
	std::wstring value;

	for (size_t j = 0; j < 4; ++j) {
		subTag = containerTag->getSubTag(j);

		if (subTag.getName() == searchSubTagName) {
			value = subTag.getValue();
			if (value == L"")
				return bkmManagerWnd_menu_file_open_error(hWnd, errorMessage);

			if (searchSubTagName == L"name")
				container->setName((PWSTR)value.c_str(), subTag.getValue().size() + 1);
			else if (searchSubTagName == L"task")
				container->setTask((PWSTR)value.c_str(), subTag.getValue().size() + 1);
			else if (searchSubTagName == L"taskType")
				container->setTaskType(std::stoi(value));

			break;
		}
		else if (j == 3) {
			return bkmManagerWnd_menu_file_open_error(hWnd, errorMessage);
		}
	}

	return true;
}

LRESULT bkmManagerWnd_menu_file_new(HWND hWnd)
{
	if (isProgramChanged) {
		int answer = MessageBox(hWnd, L"Сохранить изменения?", L"Bookmark Manager", MB_YESNOCANCEL | MB_ICONQUESTION);
		if (answer == IDYES) {
			bkmManagerWnd_menu_file_save();
		}
		else if (answer == IDNO) {
			changeProgramState(false);
		}
		else {
			return 0;
		}
	}

	Archive::close();
	HWND hMainListView = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MAINLISTVIEW);
	ListView_DeleteAllItems(hMainListView);

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
