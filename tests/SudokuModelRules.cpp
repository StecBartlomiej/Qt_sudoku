#include <gtest/gtest.h>

#include "SudokuModel.hpp"


TEST(SudokuRulesTest, DefaultInitalization)
{
    SudokuRules rules{};

    for (int y = 0; y < 9; ++y)
    {
        for (int x = 0; x < 9; ++x)
        {
            for (int value = 1; value <= 9; ++value)
                ASSERT_TRUE(rules.IsAllowed(x, y, value));
        }
    }
}

TEST(SudokuRulesTest, SetValueAndIsAllowed)
{
    SudokuRules rules{};

    constexpr int value = 1;
    rules.SetValue(2, 2, value);

    // In group
    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 3; ++x)
            EXPECT_FALSE(rules.IsAllowed(x, y, value));
    }

    // In row
    for (int x = 0; x < 9; ++x)
        EXPECT_FALSE(rules.IsAllowed(x, 2, value));

    // In column
    for (int y = 0; y < 9; ++y)
        EXPECT_FALSE(rules.IsAllowed(2, y, value));

    // Rest is allowed
    for (int y = 0; y < 9; ++y)
    {
        for (int x = 0; x < 9; ++x)
        {
            for (int v = 1; v <= 9; ++v)
            {
                if (v == value)
                    continue;

                /** SudokuRules does not know numbers on board, it only tracks occupied values in relation to rules
                 *  so IsAllowed returns true if in already occupied position
                 *  if we try to insert another value It is valid position in Sudoku rule
                 *  In this example rules.IsAllowed(2, 2, not_2) will return true
                 **/
                EXPECT_TRUE(rules.IsAllowed(x, y, v));
            }
        }
    }
}

TEST(SudokuRulesTest, GetGroupIdx)
{
    ASSERT_EQ(SudokuRules::GetGroupIdx(0, 0), 0);
    ASSERT_EQ(SudokuRules::GetGroupIdx(3, 3), 4);
    ASSERT_EQ(SudokuRules::GetGroupIdx(2, 3), 3);
    ASSERT_EQ(SudokuRules::GetGroupIdx(8, 8), 8);
    ASSERT_EQ(SudokuRules::GetGroupIdx(5, 5), 4);
}
