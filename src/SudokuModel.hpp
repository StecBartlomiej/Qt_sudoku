#ifndef QT_SUDOKU_SUDOKUMODEL_HPP
#define QT_SUDOKU_SUDOKUMODEL_HPP

#include <QAbstractTableModel>
#include <optional>
#include <array>


class SudokuModel: public QAbstractTableModel
{
public:
    // TODO - make custom bounded value
    using CellValue = std::optional<uint8_t>;
    using Array2D = std::array<std::array<CellValue, 9>, 9>;

    explicit SudokuModel(QWidget *parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override { return 9; }
    [[nodiscard]] int columnCount(const QModelIndex &parent) const override { return 9; }

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    Array2D table_;
};


#endif //QT_SUDOKU_SUDOKUMODEL_HPP
