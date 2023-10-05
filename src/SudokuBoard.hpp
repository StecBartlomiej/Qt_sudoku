#ifndef QT_SUDOKU_SUDOKUBOARD_HPP
#define QT_SUDOKU_SUDOKUBOARD_HPP

#include <cinttypes>
#include <array>
#include <optional>
#include <bitset>


class Cell
{
public:
    using ValueT = uint8_t;

    Cell(): optionalValue_{std::nullopt}, isModifiable_{true} {}
    explicit Cell(ValueT value, bool isModifiable = false): optionalValue_{value}, isModifiable_{isModifiable} {}

    [[nodiscard]] bool HasValue() const { return optionalValue_.has_value(); }

    [[nodiscard]] ValueT Value() const { return optionalValue_.value(); }
    void SetValue(ValueT value);
    void RemoveValue();

    [[nodiscard]] bool IsModifiable() const { return isModifiable_; }

private:
    std::optional<ValueT> optionalValue_;
    bool isModifiable_;
};


class SudokuRules
{
public:
    using Digits = std::bitset<9>;
    using GroupDigits = std::array<Digits, 9>;

    [[nodiscard]] constexpr static int GetGroupIdx(int x, int y) { return (y / 3) * 3 + (x / 3); }

    void SetValue(int x, int y, uint8_t cellValue);
    void RemoveValue(int x, int y, uint8_t cellValue);

    [[nodiscard]] bool IsAllowed(int x, int y, uint8_t cellValue) const;

private:
    GroupDigits rows_;
    GroupDigits columns_;
    GroupDigits group_;
};


class SudokuBoard
{
public:
    using Array = std::array<Cell, 9>;
    using Array2D = std::array<Array, 9>;

    void SetValue(int x, int y, Cell::ValueT value);
    [[nodiscard]] bool IsAllowed(int x, int y, Cell::ValueT value) const;
    void RemoveValue(int x, int y);

    const Array& operator[](std::size_t i) const { return table_[i]; };

private:
    Array2D table_;
    SudokuRules rules_;
};


#endif //QT_SUDOKU_SUDOKUBOARD_HPP
