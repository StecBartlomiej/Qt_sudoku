#include "SudokuModel.hpp"

#include <QMessageBox>


SudokuModel::SudokuModel(QObject *parent, SudokuSolver solver): QAbstractTableModel(parent), board_{}, solver_{std::move(solver)}
{

}

QVariant SudokuModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    Cell cellValue = board_.Cell(index.row(), index.column());

    if (role == Qt::DisplayRole)
    {
        if (cellValue.HasValue())
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
            if (ok && uint_value >= 1 && uint_value <= 9)
            {
                if (board_.IsAllowed(index.row(), index.column(), uint_value))
                {
                    board_.SetValue(index.row(), index.column(), uint_value);
                    emit dataChanged(index, index, {role});
                }
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
    return solver_(board_);
}

void SudokuModel::Reset()
{
    beginResetModel();

    board_ = SudokuBoard{};

    endResetModel();
}
