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
#include "IRHandleListTest.h"
#include <ircommon/irhndlst.h>
#include <thread>
#include <memory>
using namespace ircommon;

//==============================================================================
// class IRHandleListTest
//------------------------------------------------------------------------------
IRHandleListTest::IRHandleListTest() {
}

//------------------------------------------------------------------------------
IRHandleListTest::~IRHandleListTest() {
}

//------------------------------------------------------------------------------
void IRHandleListTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRHandleListTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRHandleListTest,Constructor) {
	IRHandleList<int> * l;

	l = new IRHandleList<int>(0);
	ASSERT_EQ(0, l->size());
	delete l;
}

//------------------------------------------------------------------------------
TEST_F(IRHandleListTest, size) {
	IRHandleList<int> l(0);

	ASSERT_EQ(0, l.size());
	l.insert(0);
	ASSERT_EQ(1, l.size());
	l.insert(0);
	ASSERT_EQ(2, l.size());
}

//------------------------------------------------------------------------------
TEST_F(IRHandleListTest, insert) {
	IRHandleList<int> l(0);
	std::uint32_t id1;
	std::vector<std::uint32_t> handles;

	ASSERT_FALSE(l.contains(0));
	for (int i = 0; i < 16; i++) {
		ASSERT_EQ(i, l.size());
		id1 = l.insert(i);
		handles.push_back(id1);
		ASSERT_EQ(i + 1, l.size());
		int v;
		ASSERT_TRUE(l.get(id1, v));
		ASSERT_EQ(i, v);
		ASSERT_TRUE(l.contains(id1));
	}
	ASSERT_EQ(16, l.size());
	for (unsigned int i = 0; i < handles.size(); i++) {
		int v;
		ASSERT_TRUE(l.get(handles[i], v));
		ASSERT_EQ(i, v);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRHandleListTest, remove) {
	IRHandleList<int> l(0);
	std::uint32_t id;
	std::vector<std::uint32_t> handles;

	ASSERT_FALSE(l.remove(0));
	for (int i = 0; i < 16; i++) {
		id = l.insert(i);
		handles.push_back(id);
	}
	for (unsigned int i = 0; i < handles.size(); i++) {
		id = handles[i];
		ASSERT_TRUE(l.remove(id));
		ASSERT_FALSE(l.contains(id));
		ASSERT_EQ(16 - i - 1, l.size());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRHandleListTest, get) {
	IRHandleList<int> l(0);
	std::uint32_t id;
	std::map<std::uint32_t, int> handles;
	int i;

	for (i = 0; i < 16; i++) {
		id = l.insert(i);
		handles.insert({id, i});
	}

	for (auto entry = handles.begin(); entry != handles.end(); entry++) {
		int v;
		ASSERT_TRUE(l.get(entry->first, v));
		ASSERT_EQ(entry->second, v);
	}

	for (i = 0; i < 100; i++) {
		if (handles.find(i) == handles.end()) {
			int v;
			ASSERT_FALSE(l.get(i, v));
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(IRHandleListTest, clear) {
	IRHandleList<int> l(0);

	for (int i = 0; i < 16; i++) {
		l.insert(i);
	}
	ASSERT_EQ(16, l.size());
	l.clear();
	ASSERT_EQ(0, l.size());
}

//------------------------------------------------------------------------------
TEST_F(IRHandleListTest, contains) {
	IRHandleList<int> l(0);
	std::uint32_t id;
	std::map<std::uint32_t, int> handles;
	int i;

	for (i = 0; i < 16; i++) {
		id = l.insert(i);
		handles.insert({id, i});
	}

	for (auto entry = handles.begin(); entry != handles.end(); entry++) {
		ASSERT_TRUE(l.contains(entry->first));
	}

	for (i = 0; i < 100; i++) {
		if (handles.find(i) == handles.end()) {
			ASSERT_FALSE(l.contains(i));
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(IRHandleListTest, listHandles) {
	IRHandleList<int> l(0);
	std::vector<std::uint32_t> ids;
	std::set<std::uint32_t> dups;
	int i;

	for (i = 0; i < 16; i++) {
		l.insert(i);
	}
	l.listHandles(ids);
	ASSERT_EQ(16, ids.size());
	for (unsigned int i = 0; i < ids.size(); i++) {
		ASSERT_TRUE(l.contains(ids[i]));
		ASSERT_EQ(dups.end(), dups.find(ids[i]));
		dups.insert(ids[i]);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRHandleListTest, Concurrency) {
	std::vector<std::shared_ptr<std::thread>> threads;
	IRHandleList<int> l(0);

	// Insert the first one
	l.insert(0);

	// Create 5 readers
	for (int i = 0; i < 5; i++) {
		threads.push_back(
				std::shared_ptr<std::thread>(
				new std::thread([&l](){
					do {
						IRHandleList<int>::HandleList list;
						l.listHandles(list);
						if (list.size() > 0) {
							int v;
							l.get(list[0], v);
						}
					} while (l.size() > 0);
				})));
	}

	// Create 3 writers
	for (int i = 0; i < 3; i++) {
		threads.push_back(
				std::shared_ptr<std::thread>(
				new std::thread([&l](){
					do {
						IRHandleList<int>::HandleList list;
						std::uint32_t h  = l.insert(0);
						l.remove(h);
					} while (l.size() > 0);
				})));
	}

	// Let them run for 15ms to see if they will deadlock
	std::this_thread::sleep_for(std::chrono::milliseconds(15));

	// Launch the one who will clear then all
	threads.push_back(
			std::shared_ptr<std::thread>(
			new std::thread([&l](){
				do {
					l.clear();
				} while (l.size() > 0);
			})));

	for (unsigned int i = 0; i < threads.size(); i++){
		threads[i]->join();
	}
}

//------------------------------------------------------------------------------


