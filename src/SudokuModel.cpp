#include "SudokuModel.hpp"

SudokuModel::SudokuModel(QObject *parent): QAbstractTableModel(parent), table_{}
{

}

QVariant SudokuModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    CellValue cellValue = table_[index.column()][index.row()];

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if (cellValue.has_value())
            return cellValue.value();
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
            if (ok && uint_value >= 1 & uint_value <= 9)
            {
                table_[index.column()][index.row()] = uint_value;
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

