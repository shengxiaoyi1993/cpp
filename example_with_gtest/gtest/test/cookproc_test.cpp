#include "CookProc.h"
#include "gtest/gtest.h"


TEST(MyString, CookProc_DefaultConstructor) {
     CookProc s;

    EXPECT_EQ(0u, s.getDish());
}
