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
#ifndef __IRZEROPADDINGTEST_H__
#define __IRZEROPADDINGTEST_H__

#include <gtest/gtest.h>

class IRZeroPaddingTest : public testing::Test {
public:
	IRZeroPaddingTest();
	virtual ~IRZeroPaddingTest();
	virtual void SetUp();
	virtual void TearDown();
};
#endif //__IRZEROPADDINGTEST_H__

