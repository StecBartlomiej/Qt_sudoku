#include <gtest/gtest.h>

#include "SudokuBoard.hpp"


TEST(SudokuBoardTest, Initialization)
{
    SudokuBoard board_{};

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
            ASSERT_FALSE(board_.Cell(i, j).HasValue());
    }
}

TEST(SudokuBoardTest, SetValue)
{
    SudokuBoard board{};

    ASSERT_FALSE(board.Cell(2, 2).HasValue());

    board.SetValue(2, 2, 2);
    EXPECT_EQ(board.Cell(2, 2).Value(), 2);

    // Violates the rules of Sudoku
    EXPECT_DEATH_IF_SUPPORTED(board.SetValue(2, 1, 2), "");

    ASSERT_FALSE(board.Cell(2, 1).HasValue());
}

TEST(SudokuBoardTest, RemoveValue)
{
    SudokuBoard board{};

    ASSERT_FALSE(board.Cell(1, 2).HasValue());

    board.SetValue(1, 2, 8);
    ASSERT_EQ(board.Cell(1, 2).Value(), 8);

    board.RemoveValue(1, 2);
    EXPECT_FALSE(board.Cell(1, 2).HasValue());

    // Check if value was removed from rules
    board.SetValue(2, 1, 8);
    EXPECT_EQ(board.Cell(2, 1).Value(), 8);
}