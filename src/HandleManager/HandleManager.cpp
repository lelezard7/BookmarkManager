#define UNICODE

#include "..\Common\Debug.h"
#include "HandleManager.h"

std::map<HandleName, HWND> HandleManager::handleContainer_;


HWND HandleManager::getHandleWnd(const HandleName name)
{
	if (handleContainer_.find(name) != handleContainer_.end())
		return handleContainer_[name];

	debugMessage(L"Дескриптора с именем " + std::to_wstring(name) + L" не существует!");
	return nullptr;
}

bool HandleManager::addHandleWnd(HWND hWnd, const HandleName name)
{
	if (handleContainer_.find(name) == handleContainer_.end()) {
		handleContainer_.emplace(std::make_pair(name, hWnd));
		return true;
	}
	else {
		debugMessage(L"Дескриптор с именем" + std::to_wstring(name) + L" уже существует!");
		return false;
	}
}

bool HandleManager::checkExistence(const HandleName name)
{
	return handleContainer_.find(name) != handleContainer_.end();
}

bool HandleManager::checkExistence(const CheckList& checkList)
{
	for (size_t i = 0; i < checkList.size(); i++) {
		if (handleContainer_.find(checkList[i]) == handleContainer_.end())
			return false;
	}

	return true;
}

bool HandleManager::removeHandleWnd(const HandleName name)
{
	if (handleContainer_.find(name) != handleContainer_.end()) {
		handleContainer_.erase(name);
		return true;
	}
	else {
		debugMessage(L"Handle with name " + std::to_wstring(name) + L" not found!");
		return false;
	}
}
