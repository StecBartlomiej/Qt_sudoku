#include "Cell.hpp"

Cell::Cell(std::optional<uint8_t> value, bool modifiable): value_{value}, modifiable_(modifiable)
{
}

void Cell::setData(int role, const QVariant &value)
{
    if (role == Qt::EditRole && modifiable_)
    {
        bool ok;
        value_ = value.toUInt(&ok);
        if (!ok | value_ > 9 | value_ == 0)
            value_ = std::nullopt;
    }
}

QVariant Cell::data(int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (value_.has_value())
            return value_.value();
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
    if (value_.has_value())
        out << value_.value();
    else
        out << " ";
    out << ";" << QString::number(modifiable_);
}

