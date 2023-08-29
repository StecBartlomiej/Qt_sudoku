#ifndef QT_SUDOKU_SUDOKUBOARD_HPP
#define QT_SUDOKU_SUDOKUBOARD_HPP

#include <QTableWidget>

class Cell;

class SudokuBoard : public QTableWidget
{
    Q_OBJECT
public:
    explicit SudokuBoard(QWidget *parent);

    friend QDataStream& operator<<(QDataStream& out, const SudokuBoard &sudoku);

    void SaveToFile(const QString &name) const;

public slots:
    void ChangeSelectedNumber(int newNumber);
    void SetCellValue(int w, int h);

    // TODO - Add Serialization/Deserialization
    // TODO - Draw Sudoku Grid
    // TODO - Add solver
private:
    std::optional<uint8_t> selectedNumber_;
};


#endif //QT_SUDOKU_SUDOKUBOARD_HPP
