#include "SudokuWidget.hpp"
#include "Cell.hpp"

#include <QHeaderView>
#include <QResizeEvent>
#include <QMessageBox>
#include <QFile>

SudokuWidget::SudokuWidget(QWidget *parent) : QTableWidget(parent), selectedNumber_{std::nullopt}
{
    setItemPrototype(new Cell);
    setSelectionMode(QAbstractItemView::SingleSelection);

    for (int i = 0; i < 9; ++i)
    {
        insertRow(i);
        insertColumn(i);
    }
    setMinimumSize(450, 450);

    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setCornerButtonEnabled(false);
    setSortingEnabled(false);
    showGrid();

    connect(this, &QTableWidget::cellClicked, this, &SudokuWidget::SetCellValue);
}

void SudokuWidget::ChangeSelectedNumber(int newNumber)
{
    selectedNumber_ = newNumber;
}

void SudokuWidget::SetCellValue(int x, int y)
{
    auto *cell = item(x, y);

    if (!cell)
    {
        cell = itemPrototype()->clone();
        setItem(x, y, cell);
    }
    if (selectedNumber_.has_value())
        cell->setData(Qt::EditRole, selectedNumber_.value());
}


bool SudokuWidget::WriteTo(QDataStream &out)
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            auto *cell = item(i, j);
            if (cell)
            {
                out << quint16(i) << quint16(j);
                cell->write(out);
            }
        }
    }
    return true;
}

bool SudokuWidget::ReadFrom(QDataStream &in)
{
    quint16 i, j;
    while (!in.atEnd())
    {
        in >> i >> j;
        auto cell = new Cell();
        cell->read(in);
        setItem(i, j, cell);
    }
    return true;
}

QString SudokuWidget::GetStringBoard() const
{
    QString result;
    QTextStream oss;
    oss.setString(&result);

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            auto *cell = item(i, j);
            if (cell)
                oss << cell->data(Qt::DisplayRole).toString();
            else
                oss << "-";
            oss << "\t";
        }
        oss << "\n";
    }
    return result;
}

void SudokuWidget::DrawGridLines()
{

}
