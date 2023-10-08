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

TEST(SudokuBoardTest, CreateSudokuBoard)
{
    // Value that are out of <1, 9> range are set to empty cells in SudokuBoard
    constexpr std::array<std::array<uint8_t, 9>, 9> array = {{{7, 0, 0,  0, 0, 0,  0, 8, 3},
                                                              {0, 0, 0,  0, 7, 5,  0, 0, 2},
                                                              {0, 0, 0,  0, 3, 0,  0, 6, 0},

                                                              {8, 0, 0,  0, 6, 0,  5, 4, 0},
                                                              {0, 0, 0,  2, 0, 4,  0, 0, 0},
                                                              {0, 4, 3,  0, 1, 0,  0, 0, 7},

                                                              {0, 1, 0,  0, 2, 0,  0, 0, 0},
                                                              {2, 0, 0,  9, 8, 0,  0, 0, 0},
                                                              {9, 7, 0,  0, 0, 0,  0, 0, 4}
                                                             } };

    auto sudokuBoard = CreateSudokuBoard(array);

    for (int y = 0; y < 9; ++y)
    {
        for (int x = 0; x < 9; ++x)
        {
            if (array[y][x] == 0)
                EXPECT_FALSE(sudokuBoard.Cell(x, y).HasValue());
            else
                EXPECT_EQ(sudokuBoard.Cell(x, y).Value(), array[y][x]);
        }
    }
}