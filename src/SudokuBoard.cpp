#include "SudokuBoard.hpp"
#include "Cell.hpp"

#include <QHeaderView>
#include <QResizeEvent>
#include <QMessageBox>
#include <QFile>

SudokuBoard::SudokuBoard(QWidget *parent) : QTableWidget(parent), selectedNumber_{std::nullopt}
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

    connect(this, &QTableWidget::cellClicked, this, &SudokuBoard::SetCellValue);
}

void SudokuBoard::ChangeSelectedNumber(int newNumber)
{
    selectedNumber_ = newNumber;
}

void SudokuBoard::SetCellValue(int x, int y)
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


bool SudokuBoard::WriteTo(QDataStream &out)
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

bool SudokuBoard::ReadFrom(QDataStream &in)
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
