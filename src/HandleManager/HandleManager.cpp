#ifndef UNICODE
#define UNICODE
#endif

#include "HandleManager.h"

std::map<HandleName, HWND> HandleManager::handleContainer_;


//HWND* HandleManager::addHandleWnd(cHandleName name)
//{
//	if (handleContainer_.find(name) == handleContainer_.end())
//	{
//		HWND* hWnd = new HWND;
//		handleContainer_.emplace(std::make_pair(name, hWnd));
//		return hWnd;
//	}
//	else
//	{
//		debugMessage(L"The " + name + L" handle already exists!");
//		return nullptr;
//	}
//}
//
//bool HandleManager::addHandleWnd(cHandleName name, HWND*& localHandle)
//{
//	if (handleContainer_.find(name) == handleContainer_.end())
//	{
//		HWND* hWnd = new HWND;
//		handleContainer_.emplace(std::make_pair(name, hWnd));
//		localHandle = hWnd;
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

//HWND* HandleManager::createHandleWnd(cHandleName name)
//{
//	if (handleContainer_.find(name) == handleContainer_.end())
//	{
//		HWND* hWnd = new HWND;
//		handleContainer_.emplace(std::make_pair(name, *hWnd));
//		return hWnd;
//	}
//	else
//	{
//		debugMessage(L"The " + name + L" handle already exists!");
//		return nullptr;
//	}
//}

HWND HandleManager::getHandleWnd(const HandleName name)
{
	if (handleContainer_.find(name) != handleContainer_.end())
	{
		return handleContainer_[name];
	}
	else
	{
		debugMessage(L"Handle with the name " + name + L" does not exist!");
		return nullptr;
	}
}

bool HandleManager::addHandleWnd(const HandleName name, HWND hWnd)
{
	if (handleContainer_.find(name) == handleContainer_.end())
	{
		handleContainer_.emplace(std::make_pair(name, hWnd));
		return true;
	}
	else
	{
		debugMessage(L"The " + name + L" handle already exists!");
		return false;
	}
}

bool HandleManager::checkExistence(const HandleName name)
{
	return handleContainer_.find(name) != handleContainer_.end();
}

bool HandleManager::checkExistence(const CheckList& checkList)
{
	for (size_t i = 0; i < checkList.size(); i++)
	{
		if (handleContainer_.find(checkList[i]) == handleContainer_.end())
		{
			return false;
		}
	}
	return true;
}

bool HandleManager::removeHandleWnd(const HandleName name)
{
	if (handleContainer_.find(name) != handleContainer_.end())
	{
		handleContainer_.erase(name);
		return true;
	}
	else
	{
		debugMessage(L"Handle with name " + name + L" not found!");
		return false;
	}
}


//HWND* HandleManager::getHandleWnd(cHandleName name)
//{
//	if (handleContainer_.find(name) != handleContainer_.end())
//	{
//		return handleContainer_[name];
//	}
//	else
//	{
//		return nullptr;
//	}
//}

//bool HandleManager::getHandleWnd(cHandleName name, HWND*& localHandle)
//{
//	if (handleContainer_.find(name) != handleContainer_.end())
//	{
//		localHandle = handleContainer_[name];
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}


//bool HandleManager::checkExistence(cHandleName name)
//{
//	return handleContainer_.find(name) != handleContainer_.end();
//}
//
//bool HandleManager::checkExistence(pcHandleName names)
//{
//	for (size_t i = 0; names[i] != L"\0"; i++) //TODO: Если не найдет \0?
//	{
//		if (handleContainer_.find(names[i]) == handleContainer_.end())
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//bool HandleManager::checkExistence(pcHandleName names, const size_t size)
//{
//	for (size_t i = 0; i < size; i++)
//	{
//		if (handleContainer_.find(names[i]) == handleContainer_.end())
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//
//bool HandleManager::removeHandleWnd(cHandleName name)
//{
//	if (handleContainer_.find(name) != handleContainer_.end())
//	{
//		delete handleContainer_[name];
//		handleContainer_.erase(name);
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
