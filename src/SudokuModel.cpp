#include "SudokuModel.hpp"

SudokuModel::SudokuModel(QWidget *parent): QAbstractTableModel(parent), table_{}
{

}

QVariant SudokuModel::data(const QModelIndex &index, int role) const
{
    CellValue cellValue = table_[index.column()][index.row()];

    if (role == Qt::DisplayRole)
    {
        if (cellValue.has_value())
            return cellValue.value();
    }
    return {};
}

bool SudokuModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        if (value.typeId() == QMetaType::QString || value.typeId() == QMetaType::UInt || value.typeId() == QMetaType::Int)
        {
            bool ok{};
            auto uint_value = value.toUInt(&ok);
            if (ok)
            {
                table_[index.column()][index.row()] = uint_value;
            }
            return ok;
        }
    }
    return false;
}

Qt::ItemFlags SudokuModel::flags(const QModelIndex &index) const
{
    return {QAbstractTableModel::flags(index) | Qt::ItemIsEditable};
}

