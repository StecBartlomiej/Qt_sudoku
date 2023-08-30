#ifndef QT_SUDOKU_SUDOKUBOARD_HPP
#define QT_SUDOKU_SUDOKUBOARD_HPP

#include <QTableWidget>

class Cell;

class SudokuBoard : public QTableWidget
{
    Q_OBJECT
public:
    explicit SudokuBoard(QWidget *parent);

    bool WriteTo(QDataStream &out);
    bool ReadFrom(QDataStream &in);
    [[nodiscard]] QString GetStringBoard() const;

public slots:
    void ChangeSelectedNumber(int newNumber);
    void SetCellValue(int x, int y);

private:
    void DrawGridLines();
    // TODO - Draw Sudoku Grid
    // TODO - Add solver

private:
    std::optional<int> selectedNumber_;
};


#endif //QT_SUDOKU_SUDOKUBOARD_HPP
