#include "SudokuModel.hpp"

#include <cassert>


void SudokuRules::SetValue(int x, int y, int cellValue)
{
    assert(IsAllowed(x, y, cellValue));
    int groupIdx = GetGroupIdx(x, y);

    rows_[y][cellValue - 1] = true;
    columns_[x][cellValue - 1] = true;
    group_[groupIdx][cellValue - 1] = true;
}

void SudokuRules::RemoveValue(int x, int y, int cellValue)
{
    assert(cellValue >= 1 && cellValue <= 9);
    int groupIdx = GetGroupIdx(x, y);

    rows_[y][cellValue - 1] = false;
    columns_[x][cellValue - 1] = false;
    group_[groupIdx][cellValue - 1] = false;
}

bool SudokuRules::IsAllowed(int x, int y, int cellValue) const
{
    assert(cellValue >= 1 && cellValue <= 9);
    int groupIdx = GetGroupIdx(x, y);
    return !rows_[y][cellValue - 1] && !columns_[x][cellValue - 1] && !group_[groupIdx][cellValue - 1];
}


SudokuModel::SudokuModel(QObject *parent): QAbstractTableModel(parent), table_{}
{

}

QVariant SudokuModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    Cell cellValue = table_[index.column()][index.row()];

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if (cellValue.hasValue())
            return cellValue.Value();
    }
    else if (role == Qt::TextAlignmentRole)
    {
        return Qt::AlignCenter;
    }
    return {};
}

bool SudokuModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        if (value.typeId() == QMetaType::Int || value.typeId() == QMetaType::UInt || value.typeId() == QMetaType::QString)
        {
            bool ok{};
            auto uint_value = value.toUInt(&ok);
            if (ok && uint_value >= 1 && uint_value <= 9 && rules_.IsAllowed(index.row(), index.column(), static_cast<int>(uint_value)))
            {
                table_[index.column()][index.row()] = Cell(uint_value);
                emit dataChanged(index, index, {role});
            }
            return ok;
        }
    }
    return false;
}

Qt::ItemFlags SudokuModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool SudokuModel::Solve()
{
    int y, x;
    Cell cellValue;
    quint8 currValue = 0;
    Array2D originalBoard = table_;
    bool isGoingBack = false;

    for (int i = 0; i < 9 * 9; ++i)
    {
        REVERT_BACK:
        if (i < 0)
        {
            table_ = originalBoard;
            return false;
        }

        y = i / 9;
        x = i % 9;

        // TODO - delete .has_value() -> make a option to create sudoku from GUI
        if (originalBoard[y][x].hasValue() && originalBoard[y][x].isModifiable())
        {
            if (isGoingBack)
                --i;
            else
                ++i;
            goto REVERT_BACK;
        }

        cellValue = table_[y][x];
        isGoingBack = false;

        currValue = 0;
        if (cellValue.hasValue())
        {
            currValue = cellValue.Value();
            rules_.RemoveValue(x, y, currValue);
            table_[y][x].deleteValue();
        }

        do
        {
            currValue += 1;
            if (currValue > 9)
            {
                --i;
                isGoingBack = true;
                goto REVERT_BACK;
            }
        } while (!rules_.IsAllowed(x, y, currValue));

        table_[y][x].setValue(currValue);
        rules_.SetValue(x, y, currValue);
    }

    return true;
}

inline void Cell::setValue(quint8 value)
{
    assert(isModifiable_);
    optionalValue_ = value;
}

inline void Cell::deleteValue()
{
    assert(isModifiable_);
    optionalValue_ = std::nullopt;
}

