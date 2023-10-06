#include "SudokuBoard.hpp"


void Cell::SetValue(quint8 value)
{
    assert(isModifiable_);
    optionalValue_ = value;
}

void Cell::RemoveValue()
{
    assert(isModifiable_);
    optionalValue_ = std::nullopt;
}


void SudokuRules::SetValue(int x, int y, uint8_t cellValue)
{
    assert(IsAllowed(x, y, cellValue));
    int groupIdx = GetGroupIdx(x, y);

    rows_[y][cellValue - 1] = true;
    columns_[x][cellValue - 1] = true;
    group_[groupIdx][cellValue - 1] = true;
}

void SudokuRules::RemoveValue(int x, int y, uint8_t cellValue)
{
    assert(cellValue >= 1 && cellValue <= 9);
    int groupIdx = GetGroupIdx(x, y);

    rows_[y][cellValue - 1] = false;
    columns_[x][cellValue - 1] = false;
    group_[groupIdx][cellValue - 1] = false;
}

bool SudokuRules::IsAllowed(int x, int y, uint8_t cellValue) const
{
    assert(cellValue >= 1 && cellValue <= 9);
    int groupIdx = GetGroupIdx(x, y);
    return !rows_[y][cellValue - 1] && !columns_[x][cellValue - 1] && !group_[groupIdx][cellValue - 1];
}

void SudokuBoard::SetValue(int x, int y, Cell::ValueT value)
{
    assert(value >= 1 && value <= 9);
    rules_.SetValue(x, y, value);
    Cell(x, y).SetValue(value);
}

bool SudokuBoard::IsAllowed(int x, int y, Cell::ValueT value) const
{
    return Cell(x, y).IsModifiable() && rules_.IsAllowed(x, y, value);
}

void SudokuBoard::RemoveValue(int x, int y)
{
    auto cell = Cell(x, y);
    if (cell.HasValue())
    {
        rules_.RemoveValue(x, y, cell.Value());
        Cell(x, y).RemoveValue();
    }
}
