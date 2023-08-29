#include "SudokuBoard.hpp"
#include "Cell.hpp"

#include <QHeaderView>
#include <QResizeEvent>


SudokuBoard::SudokuBoard(QWidget *parent) : QTableWidget(parent), selectedNumber_{std::nullopt}
{
    setItemPrototype(new Cell{});
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

void SudokuBoard::SetCellValue(int w, int h)
{
    auto cell = itemAt(w, h);

    if (!cell)
    {
        cell = itemPrototype()->clone();
        setItem(w, h, cell);
    }
    if (selectedNumber_.has_value())
        cell->setData(Qt::EditRole, selectedNumber_.value());
}

QDataStream &operator<<(QDataStream &out, const SudokuBoard &sudoku)
{
    for (int i = 0; i < 9; ++i)
    {
        out << "\n";
        for (int j = 0; j < 9; ++j)
        {
            auto cell =
        }
    }
}
