#include <iostream>
#include "Sudoku.hpp"

void SudokuRules::SetValue(int x, int y, int value)
{
    assert(IsAllowed(x, y, value));
    int groupIdx = GetGroupIdx(x, y);

    rows_[y][value-1] = true;
    columns_[x][value-1] = true;
    group_[groupIdx][value-1] = true;
}

bool SudokuRules::IsAllowed(int x, int y, int value) const
{
    int groupIdx = GetGroupIdx(x, y);
    if (rows_[y][value - 1] || columns_[x][value - 1] || group_[groupIdx][value - 1])
        return false;
    return true;
}

void SudokuRules::RemoveValue(int x, int y, int value)
{
    int groupIdx = GetGroupIdx(x, y);

    rows_[y][value-1] = false;
    columns_[x][value-1] = false;
    group_[groupIdx][value-1] = false;
}

void Sudoku::SetValue(int x, int y, int value)
{
    assert(IsAllowed(x, y, value));
    rules_.SetValue(x, y, value);
    board_[y][x] = value;
}

void Sudoku::RemoveValue(int x, int y)
{
    if (board_[y][x].has_value())
    {
        rules_.RemoveValue(x, y, board_[y][x].value());
        board_[y][x] = std::nullopt;
    }
}

bool Sudoku::Solve()
{
    int y, x;
    std::optional<ValueT> cellValue;
    ValueT currValue = 0;
    Array2D originalBoard = board_;
    bool isGoingBack = false;

    for (int i = 0; i < 9 * 9; ++i)
    {
    REVERT_BACK:
        if (i < 0)
        {
            board_ = originalBoard;
            return false;
        }

        y = i / 9;
        x = i % 9;

        if (originalBoard[y][x].has_value())
        {
            if (isGoingBack)
                --i;
            else
                ++i;
            goto REVERT_BACK;
        }

        cellValue = board_[y][x];
        isGoingBack = false;

        currValue = -1;
        if (cellValue.has_value())
        {
            currValue = cellValue.value();
            RemoveValue(x, y);
        }

        do
        {
            currValue += 1;
            if (currValue > 8)
            {
                --i;
                isGoingBack = true;
                goto REVERT_BACK;
            }
        } while (!rules_.IsAllowed(x, y, currValue));

        SetValue(x, y, currValue);
    }

    return true;
}

std::ostream &operator<<(std::ostream &oss, Sudoku &sudoku)
{
    for (int i = 0; i < 9; ++i)
    {
        if (i == 3 || i == 6)
            oss << '\n';

        for (int j = 0; j < 9; ++j)
        {
            auto v = sudoku.board_[i][j];
            if (v.has_value())
                oss << v.value() + 1;
            else
                oss << "-";

            if (j == 2  || j == 5)
                oss << '\t';
            else
                oss << " ";
        }
        oss << '\n';
    }
    return oss;
}

