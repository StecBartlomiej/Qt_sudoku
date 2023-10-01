#include <gtest/gtest.h>

#include "SudokuModel.hpp"


TEST(SudokuRulesTest, DefaultInitalization)
{
    SudokuRules rules{};

    rules.SetValue(0, 0, 1);
    ASSERT_TRUE(true);
}


TEST(SudokuRulesTest, GetGroupIdx)
{
    ASSERT_EQ(SudokuRules::GetGroupIdx(0, 0), 0);
    ASSERT_EQ(SudokuRules::GetGroupIdx(3, 3), 4);
    ASSERT_EQ(SudokuRules::GetGroupIdx(2, 3), 3);
    ASSERT_EQ(SudokuRules::GetGroupIdx(8, 8), 8);
    ASSERT_EQ(SudokuRules::GetGroupIdx(5, 5), 4);
}
