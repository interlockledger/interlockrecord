#ifndef ${FILE_MACRO}
#define ${FILE_MACRO}

#include <gtest/gtest.h>

class ${TEST_NAME} : public testing::Test {
public:
	${TEST_NAME}();
	virtual ~${TEST_NAME}();
	virtual void SetUp();
	virtual void TearDown();
};
#endif //${FILE_MACRO}

