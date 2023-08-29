#include "Cell.hpp"

Cell::Cell(QVariant value, bool modifiable): value_{std::move(value)}, modifiable_(modifiable)
{
}

void Cell::setData(int role, const QVariant &newValue)
{
    if (role == Qt::EditRole && modifiable_)
    {
        if (newValue.typeId() == QMetaType::Int)
        {
            bool ok;
            auto x = newValue.toInt(&ok);
            if (ok && x <= 9 && x >= 1)
                value_ = newValue;
        }
    }
}

QVariant Cell::data(int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (value_.isValid())
            return value_.toString();
        else
            return {};
    }
    else if (role == Qt::TextAlignmentRole)
    {
        return Qt::AlignCenter;
    }
    else
        return QTableWidgetItem::data(role);
}

QTableWidgetItem *Cell::clone() const
{
     return new Cell{*this};
}

void Cell::write(QDataStream &out) const
{
    if (value_.isValid())
    {
        bool ok;
        out << value_.toInt(&ok);
        assert(ok);
    }
    else
        out << " ";
    out << ";" << QString::number(modifiable_);
}

