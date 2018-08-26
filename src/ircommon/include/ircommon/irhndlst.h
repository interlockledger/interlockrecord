/*
 * Copyright (c) 2017-2018 InterlockLedger Network
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _IRCOMMON_IRHNDLST_H_
#define _IRCOMMON_IRHNDLST_H_

#include <unordered_map>
#include <memory>
#include <vector>
#include <ircommon/irrwlock.h>
#include <ircommon/iridgen.h>

namespace ircommon {

/**
 * This class template implements a list of objects that can be identified by
 * a unique handle.
 *
 * @tparam ObjectType The type of the object.
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2017.01.11
 * @note This class is thread safe.
 */
template <class ObjectType>
class IRHandleList {
private:
	std::unordered_map<std::uint32_t, ObjectType> _map;
	IRIDGenerator _generator;
	ircommon::threading::IRRWLock _lock;
public:
	/**
	 * Type of the list of handles.
	 */
	typedef std::vector<std::uint32_t> HandleList;

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] seed The seed of the ID generator.
	 */
	IRHandleList(std::uint32_t seed):_generator(seed) {
	}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRHandleList() = default;

	/**
	 *
	 * @note This method executes a read lock.
	 */
	int size() {
		int size;

		this->_lock.lockRead();
		size = this->_map.size();
		this->_lock.unlockRead();
		return size;
	}

	/**
	 * Inserts a new object into this list.
	 *
	 * @param[in] obj The object added into the list.
	 * @return The id assigned to the given object.
	 * @note This method executes a write lock.
	 */
	std::uint32_t insert(ObjectType obj){
		std::uint32_t id;

		this->_lock.lockWrite();
		do {
			id = this->_generator.next();
		} while (this->_map.find(id) != this->_map.end());

		this->_map.insert({id, obj});
		this->_lock.unlockWrite();
		return id;
	}

	/**
	 * Removes the object with the given ID.
	 *
	 * @param[in] The ID of the object to be removed.
	 * @return true if the object was removed or false otherwise.
	 * @note This method executes a write lock.
	 */
	bool remove(std::uint32_t id) {
		bool ret;

		this->_lock.lockWrite();
		auto found = this->_map.find(id);
		if (found != this->_map.end()) {
			this->_map.erase(found);
			ret = true;
		} else {
			ret = false;
		}
		this->_lock.unlockWrite();
		return ret;
	}

	/**
	 * Returns the element identified by a given ID.
	 *
	 * @param[in] The object id.
	 * @param[out] The object found, if any.
	 * @return true if the object exists or false otherwise.
	 * @note This method executes a read lock.
	 */
	bool get(std::uint32_t id, ObjectType & obj) {
		bool ret;

		this->_lock.lockRead();
		auto found = this->_map.find(id);
		if (found != this->_map.end()) {
			obj = found->second;
			ret = true;
		} else {
			ret = false;
		}
		this->_lock.unlockRead();
		return ret;
	}

	/**
	 * Removes all entries in this list.
	 * @note This method executes a write lock.
	 */
	void clear() {
		this->_lock.lockWrite();
		this->_map.clear();
		this->_lock.unlockWrite();
	}

	/**
	 * Verifies if a given handle is stored inside this map.
	 *
	 * @return true if the id is inside the list or false otherwise.
	 * @since 2017.01.12
	 * @note This method executes a read lock.
	 */
	bool contains(std::uint32_t id){
		bool ret;
		this->_lock.lockRead();
		ret = (this->_map.find(id) != this->_map.end());
		this->_lock.unlockRead();
		return ret;
	}

	/**
	 * Returns the list of handles.
	 *
	 * @param[out] The list of handles inside this instance.
	 * @note This method executes a read lock.
	 */
	void listHandles(HandleList & ids) {
		this->_lock.lockRead();
		for (auto entry = this->_map.begin(); entry != this->_map.end(); entry++) {
			ids.push_back(entry->first);
		}
		this->_lock.unlockRead();
	}
};

/**
 * This class template implements a variant of IRHandleList that stores the
 * objects using std::shared_ptr to manage memory.
 *
 * @tparam ObjectType The type of the object.
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2017.01.11
 * @note This class is thread safe.
 */
template <class ObjectType>
class IRSharedPtrHandleList: public IRHandleList<std::shared_ptr<ObjectType>> {
public:
	/**
	 * Type of the shared pointer used by this class.
	 */
	typedef std::shared_ptr<ObjectType> SharedPointer;

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] seed The seed of the ID generator.
	 */
	IRSharedPtrHandleList(std::uint32_t seed) :
		IRHandleList<std::shared_ptr<ObjectType>>(seed){
	}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRSharedPtrHandleList() = default;

	/**
	 * Inserts a new object into this list.
	 *
	 * @param[in] obj Pointer to the object to be added. This method will claim
	 * the ownership of this instance.
	 * @return The id assigned to the given object.
	 * @note This method executes a write lock.
	 */
	std::uint32_t insertPtr(ObjectType * obj){
		return IRHandleList<std::shared_ptr<ObjectType>>::insert(
				SharedPointer(obj));
	}
};

} // namespace ircommon

#endif /* _IRCOMMON_IRHNDLST_H_ */
