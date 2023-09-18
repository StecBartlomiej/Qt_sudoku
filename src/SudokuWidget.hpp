#ifndef QT_SUDOKU_SUDOKUWIDGET_HPP
#define QT_SUDOKU_SUDOKUWIDGET_HPP

#include <QTableWidget>

class Cell;

class SudokuWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit SudokuWidget(QWidget *parent);

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


#endif //QT_SUDOKU_SUDOKUWIDGET_HPP
