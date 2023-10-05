#ifndef SUDOKU_MODEL_HPP
#define SUDOKU_MODEL_HPP

#include "SudokuBoard.hpp"

#include <QAbstractTableModel>
#include <bitset>
#include <functional>


class SudokuBoard;
using SudokuSolver = std::function<bool(SudokuBoard&)>;


class SudokuModel : public QAbstractTableModel
{
public:
    explicit SudokuModel(SudokuSolver solver, QObject *parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex &) const override { return 9; }
    [[nodiscard]] int columnCount(const QModelIndex &) const override { return 9; }

    [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

    [[nodiscard]] bool Solve();

private:
    SudokuBoard board_;
    SudokuSolver solver_;
};


#endif //SUDOKU_MODEL_HPP
