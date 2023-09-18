#ifndef QT_SUDOKU_SUDOKU_HPP
#define QT_SUDOKU_SUDOKU_HPP

#include <array>
#include <bitset>
#include <ostream>
#include <optional>


class SudokuRules
{
public:
    using Digits = std::bitset<9>;
    using GroupDigits = std::array<Digits, 9>;

    [[nodiscard]] inline static int GetGroupIdx(int x, int y) { return (y / 3) * 3 + (x / 3); }

    void SetValue(int x, int y, int value);
    void RemoveValue(int x, int y, int value);

    [[nodiscard]] bool IsAllowed(int x, int y, int value) const;

private:
    GroupDigits rows_;
    GroupDigits columns_;
    GroupDigits group_;
};


class Sudoku
{
public:
    using ValueT = uint8_t;
    using Array2D = std::array<std::array<std::optional<int>, 9>, 9>;

    void SetValue(int x, int y, int value);
    void RemoveValue(int x, int y);
    [[nodiscard]] std::optional<int> GetValue(int x, int y) const { return board_[y][x]; }

    [[nodiscard]] bool Solve();

    [[nodiscard]] bool IsAllowed(int x, int y, int value) const { return rules_.IsAllowed(x, y, value); }

    friend std::ostream& operator<<(std::ostream& oss, Sudoku& sudoku);

private:
    SudokuRules rules_;
    Array2D board_{};
};


#endif //QT_SUDOKU_SUDOKU_HPP
