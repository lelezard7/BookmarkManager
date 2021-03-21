#define UNICODE

#include "..\Common\Debug.h"
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


Archive_Id Archive::addContainer(const Container& container)
{
	Archive_Id _id = getFreeId();
	archive_.emplace(std::make_pair(_id, container));

	archive_[_id].isRegistered = CONTAINER_REGISTERED;

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

	archive_[id].isRegistered = CONTAINER_UNREGISTERED;
	archive_[id].clear();

	auto _iterator = archive_.find(id);
	archive_.erase(_iterator->first);
	freeId(id);

	return true;
}

void Archive::clear()
{
	for (auto i : archive_) {
		i.second.isRegistered = CONTAINER_UNREGISTERED;
		i.second.clear();
	}

	archive_.clear();
	nextId_.clear();
	maxId_ = 0;
}

size_t Archive::size()
{
	return archive_.size();
}
