#ifndef QT_SUDOKU_SUDOKUMODEL_HPP
#define QT_SUDOKU_SUDOKUMODEL_HPP

#include <QAbstractTableModel>
#include <optional>
#include <array>
#include <bitset>


class Cell
{
public:
    Cell() = default;
    explicit Cell(std::optional<quint8> value, bool isModifiable = false): optionalValue_{value}, isModifiable_{isModifiable} {}
    Cell(const Cell &other) = default;
    Cell(Cell &&other) noexcept = default;
    Cell& operator=(const Cell &other) = default;

    [[nodiscard]] inline bool has_value() const { return optionalValue_.has_value(); }

    [[nodiscard]] inline quint8 value() const { return optionalValue_.value(); }
    void setValue(quint8 value);
    void deleteValue();

    [[nodiscard]] inline bool isModifiable() const { return isModifiable_; }


    friend QDataStream& operator<<(QDataStream &out, const Cell &cell);
    friend QDataStream& operator>>(QDataStream &in, Cell &cell);

private:
    std::optional<quint8> optionalValue_;  // Maybe QVariant ??
    bool isModifiable_;
};


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
    using Array2D = std::array<std::array<Cell, 9>, 9>;

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
