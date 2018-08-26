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
#ifndef __IRISO10126PADDINGTEST_H__
#define __IRISO10126PADDINGTEST_H__

#include <gtest/gtest.h>

class IRISO10126PaddingTest : public testing::Test {
public:
	IRISO10126PaddingTest();
	virtual ~IRISO10126PaddingTest();
	virtual void SetUp();
	virtual void TearDown();
};
#endif //__IRISO10126PADDINGTEST_H__

