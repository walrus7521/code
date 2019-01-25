#include <gtest/gtest.h>
#include <stdio.h>

extern "C" 
{
    #include "bogus.c"
}

TEST(BOGUSTest, INIT_BOGUS) 
{
    BOGUS_STRUCT temp_bogus;
    int         buf_size = 50;

    BOGUS_Initialize(buf_size, &temp_bogus);

    EXPECT_EQ(temp_bogus.size, 50U);
    EXPECT_EQ(temp_bogus.head, 0U);
    EXPECT_EQ(temp_bogus.tail, 0U);
    EXPECT_EQ(temp_bogus.data_avail, 0U);
    EXPECT_EQ(temp_bogus.status, BOGUS_SUCCESS);

}

