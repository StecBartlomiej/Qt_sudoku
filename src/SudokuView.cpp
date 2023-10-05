#include "SudokuView.hpp"
#include "SudokuModel.hpp"
#include "SudokuSolver.hpp"

#include <QHeaderView>
#include <QResizeEvent>
#include <QMessageBox>
#include <QFile>


SudokuView::SudokuView(QWidget *parent) : QTableView(parent), sudokuModel_{new SudokuModel(NaiveSudokuSolver, parent)}, selectedNumber_{}
{
    QTableView::setModel(sudokuModel_);
    setSelectionMode(QAbstractItemView::SingleSelection);

    setMinimumSize(450, 450);

    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setCornerButtonEnabled(false);
    setSortingEnabled(false);
    showGrid();

    connect(this, &QTableView::clicked, this, [&](const QModelIndex &index){sudokuModel_->setData(index, selectedNumber_);});
}

void SudokuView::ChangeSelectedNumber(int newNumber)
{
    selectedNumber_ = newNumber;
}

bool SudokuView::WriteTo(QDataStream &out)
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            auto idx = sudokuModel_->index(j, i);
            auto cellValue = sudokuModel_->data(idx);
            if (cellValue.isValid())
            {
                out << quint16(i) << quint16(j) << cellValue;
            }
        }
    }
    return true;
}

bool SudokuView::ReadFrom(QDataStream &in)
{
    quint16 i, j;
    QVariant cellValue;
    while (!in.atEnd())
    {
        in >> i >> j >> cellValue;
        auto idx = sudokuModel_->index(j, i);
        sudokuModel_->setData(idx, cellValue);
    }
    return true;
}

QString SudokuView::GetStringBoard() const
{
    QString result;
    QTextStream oss;
    oss.setString(&result);

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            auto idx = sudokuModel_->index(j, i);
            auto cellValue = sudokuModel_->data(idx);
            if (cellValue.isValid())
                oss << cellValue.toString();
            else
                oss << "-";
            oss << "\t";
        }
        oss << "\n";
    }
    return result;
}

void SudokuView::DrawGridLines()
{

}
