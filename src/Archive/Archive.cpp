#define UNICODE

#include "Archive.h"
#include <wchar.h>
#include <iterator>

/*		---class Archive---		*/

ID Archive::id_ = 0;
Archive_t Archive::archive_;




ID Archive::addContainer(const Container container)
{
	archive_.emplace(std::make_pair(id_, container));
	return id_++;
}

Container* Archive::getContainerByID(const ID id)
{
	if (archive_.find(id) != archive_.end())
	{
		return &archive_[id];
	}
	return nullptr;
}

Container* Archive::getContainerByIndex(const size_t index)
{
	if (index > archive_.size() - 1) {
		return nullptr;
	}

	Archive_t::iterator _iterator = archive_.begin();
	std::advance(_iterator, index);
	return &_iterator->second;
}

void Archive::clear()
{
	archive_.clear();
}

bool Archive::delContainerByIndex(const size_t index)
{
	if (index > archive_.size() - 1) {
		return false;
	}

	Archive_t::iterator _iterator = archive_.begin();
	std::advance(_iterator, index);
	archive_.erase(_iterator->first);
	return true;
}

size_t Archive::size()
{
	return archive_.size();
}

/*		---class Container---		*/

