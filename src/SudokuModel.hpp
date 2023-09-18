#ifndef QT_SUDOKU_SUDOKUMODEL_HPP
#define QT_SUDOKU_SUDOKUMODEL_HPP

#include <QAbstractTableModel>
#include <optional>
#include <array>
#include <bitset>

class SudokuRules
{
public:
    using Digits = std::bitset<9>;
    using GroupDigits = std::array<Digits, 9>;

    [[nodiscard]] inline static int GetGroupIdx(int x, int y) { return (y / 3) * 3 + (x / 3); }

    void SetValue(int x, int y, int cellValue);
    void RemoveValue(int x, int y, int cellValue);

    [[nodiscard]] bool IsAllowed(int x, int y, int cellValue) const;

private:
    GroupDigits rows_;
    GroupDigits columns_;
    GroupDigits group_;
};

class SudokuModel: public QAbstractTableModel
{
public:
    // TODO - make custom bounded value
    using CellValue = std::optional<quint8>;
    using Array2D = std::array<std::array<CellValue, 9>, 9>;

    explicit SudokuModel(QObject *parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override { return 9; }
    [[nodiscard]] int columnCount(const QModelIndex &parent) const override { return 9; }

    [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    [[nodiscard]] bool Solve();

private:
    Array2D table_;
    SudokuRules rules_;
};


#endif //QT_SUDOKU_SUDOKUMODEL_HPP
