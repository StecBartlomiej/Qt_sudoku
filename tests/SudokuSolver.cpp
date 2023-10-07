#include <gtest/gtest.h>

#include "SudokuSolver.hpp"
#include "SudokuBoard.hpp"


TEST(NaiveSudokuSolverTest, SolveCase1)
{
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
    // For details look for SudokuBoardTest
    auto sudokuBoard = CreateSudokuBoard(array);

    ASSERT_TRUE(NaiveSudokuSolver(sudokuBoard));

    constexpr std::array<std::array<uint8_t, 9>, 9> solvedArray = {{{7, 6, 5,  1, 4, 2,  9, 8, 3},
                                                                    {3, 8, 9,  6, 7, 5,  4, 1, 2},
                                                                    {4, 2, 1,  8, 3, 9,  7, 6, 5},

                                                                    {8, 9, 2,  7, 6, 3,  5, 4, 1},
                                                                    {1, 5, 7,  2, 9, 4,  6, 3, 8},
                                                                    {6, 4, 3,  5, 1, 8,  2, 9, 7},

                                                                    {5, 1, 8,  4, 2, 6,  3, 7, 9},
                                                                    {2, 3, 4,  9, 8, 7,  1, 5, 6},
                                                                    {9, 7, 6,  3, 5, 1,  8, 2, 4}
                                                                   } };

    for (int y = 0; y < 9; ++y)
    {
        for (int x = 0; x < 9; ++x)
            ASSERT_EQ(sudokuBoard.Cell(x, y).Value(), solvedArray[y][x]);
    }
}

TEST(NaiveSudokuSolverTest, SolveCase2)
{
    constexpr std::array<std::array<uint8_t, 9>, 9> array = {{{0, 0, 5,  2, 8, 0,  0, 0, 0},
                                                              {0, 0, 0,  0, 0, 4,  1, 0, 0},
                                                              {0, 0, 9,  0, 0, 0,  4, 0, 3},

                                                              {9, 0, 0,  7, 0, 0,  0, 6, 0},
                                                              {0, 8, 0,  0, 1, 0,  0, 4, 0},
                                                              {0, 5, 0,  0, 0, 9,  0, 0, 1},

                                                              {4, 0, 6,  0, 0, 0,  2, 0, 0},
                                                              {0, 0, 7,  4, 0, 0,  0, 0, 0},
                                                              {0, 0, 0,  0, 2, 5,  6, 0, 0}
                                                             } };

    auto sudokuBoard = CreateSudokuBoard(array);

    ASSERT_TRUE(NaiveSudokuSolver(sudokuBoard));

    constexpr std::array<std::array<uint8_t, 9>, 9> solvedArray = {{{1, 4, 5,  2, 8, 3,  7, 9, 6},
                                                                    {3, 7, 8,  9, 6, 4,  1, 2, 5},
                                                                    {2, 6, 9,  1, 5, 7,  4, 8, 3},

                                                                    {9, 1, 4,  7, 3, 8,  5, 6, 2},
                                                                    {6, 8, 3,  5, 1, 2,  9, 4, 7},
                                                                    {7, 5, 2,  6, 4, 9,  8, 3, 1},

                                                                    {4, 3, 6,  8, 7, 1,  2, 5, 9},
                                                                    {5, 2, 7,  4, 9, 6,  3, 1, 8},
                                                                    {8, 9, 1,  3, 2, 5,  6, 7, 4}
                                                                   } };

    for (int y = 0; y < 9; ++y)
    {
        for (int x = 0; x < 9; ++x)
            ASSERT_EQ(sudokuBoard.Cell(x, y).Value(), solvedArray[y][x]);
    }
}

TEST(NaiveSudokuSolverTest, SolveCase3)
{
    constexpr std::array<std::array<uint8_t, 9>, 9> array = {{{3, 0, 8,  0, 6, 0,  5, 0, 2},
                                                              {0, 0, 2,  8, 0, 0,  0, 6, 0},
                                                              {0, 9, 0,  2, 7, 0,  0, 0, 0},

                                                              {0, 5, 1,  0, 3, 0,  0, 9, 0},
                                                              {7, 0, 3,  0, 9, 0,  2, 0, 6},
                                                              {0, 6, 0,  0, 8, 0,  1, 7, 0},

                                                              {0, 0, 0,  0, 2, 7,  0, 8, 0},
                                                              {0, 1, 0,  0, 0, 8,  6, 0, 0},
                                                              {8, 0, 7,  0, 5, 0,  4, 0, 1}
                                                             } };

    auto sudokuBoard = CreateSudokuBoard(array);

    ASSERT_TRUE(NaiveSudokuSolver(sudokuBoard));

    constexpr std::array<std::array<uint8_t, 9>, 9> solvedArray = {{{3, 7, 8,  9, 6, 4,  5, 1, 2},
                                                                    {5, 4, 2,  8, 1, 3,  7, 6, 9},
                                                                    {1, 9, 6,  2, 7, 5,  3, 4, 8},

                                                                    {2, 5, 1,  7, 3, 6,  8, 9, 4},
                                                                    {7, 8, 3,  4, 9, 1,  2, 5, 6},
                                                                    {4, 6, 9,  5, 8, 2,  1, 7, 3},

                                                                    {6, 3, 4,  1, 2, 7,  9, 8, 5},
                                                                    {9, 1, 5,  3, 4, 8,  6, 2, 7},
                                                                    {8, 2, 7,  6, 5, 9,  4, 3, 1}
                                                                   } };

    for (int y = 0; y < 9; ++y)
    {
        for (int x = 0; x < 9; ++x)
            ASSERT_EQ(sudokuBoard.Cell(x, y).Value(), solvedArray[y][x]);
    }
}
