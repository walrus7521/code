#include <gtest/gtest.h>
#include <stdio.h>

extern "C" 
{
    #include "bogus.c"
}

TEST(BOGUSTest, INIT_BOGUS) 
{
    BOGUS_STRUCT temp_bogus;
    int size = 42;

    BOGUS_Initialize(size, &temp_bogus);

    EXPECT_EQ(temp_bogus.dude, 42U);
    EXPECT_EQ(temp_bogus.sup, BOGUS_SUCCESS);

}

