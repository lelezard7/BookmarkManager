#define UNICODE

#include "Archive.h"
#include <wchar.h>
#include <iterator>

std::map<Archive_Id, Container> Archive::archive_;
std::vector<Archive_Id> Archive::nextId_;
Archive_Id Archive::maxId_ = 0;


Archive_Id Archive::getFreeId()
{
	if (nextId_.size() == 0)
		return maxId_++;

	Archive_Id _id = *nextId_.begin();
	nextId_.erase(nextId_.begin());
	return _id;
}

bool Archive::freeId(const Archive_Id id)
{
	if (id >= maxId_)
		return false;

	if (maxId_ - 1 == id) {
		maxId_--;
		return true;
	}

	nextId_.push_back(id);
	return true;
}

Archive_Id Archive::addContainer(const Container container)
{
	Archive_Id _id = getFreeId();
	archive_.emplace(std::make_pair(_id, container));
	return _id;
}

Container* Archive::getContainer(const Archive_Id id)
{
	if (archive_.find(id) == archive_.end())
		return nullptr;

	auto _iterator = archive_.find(id);
	return &_iterator->second;
}

bool Archive::deleteContainer(const Archive_Id id)
{
	if (archive_.find(id) == archive_.end())
		return false;

	archive_[id].clear();
	auto _iterator = archive_.find(id);
	archive_.erase(_iterator->first);
	freeId(id);
	return true;
}

void Archive::clear()
{
	for (auto i : archive_)
		i.second.clear();

	archive_.clear();
}

size_t Archive::size()
{
	return archive_.size();
}



//ID Archive::addContainer(const Container container)
//{
//	archive_.emplace(std::make_pair(id_, container));
//	return id_++;
//}
//
//Container* Archive::getContainerByID(const ID id)
//{
//	if (archive_.find(id) != archive_.end())
//	{
//		return &archive_[id];
//	}
//	return nullptr;
//}
//
//Container* Archive::getContainerByIndex(const size_t index)
//{
//	if (index > archive_.size() - 1) {
//		return nullptr;
//	}
//
//	Archive_t::iterator _iterator = archive_.begin();
//	std::advance(_iterator, index);
//	return &_iterator->second;
//}
//
//void Archive::clear()
//{
//	archive_.clear();
//}
//
//bool Archive::delContainerByIndex(const size_t index)
//{
//	if (index > archive_.size() - 1) {
//		return false;
//	}
//
//	Archive_t::iterator _iterator = archive_.begin();
//	std::advance(_iterator, index);
//	archive_.erase(_iterator->first);
//	return true;
//}
//
//size_t Archive::size()
//{
//	return archive_.size();
//}
