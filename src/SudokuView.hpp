#ifndef QT_SUDOKU_SUDOKUVIEW_HPP
#define QT_SUDOKU_SUDOKUVIEW_HPP

#include <QTableWidget>

class SudokuModel;

class SudokuView: public QTableView
{
    Q_OBJECT
public:
    explicit SudokuView(QWidget *parent);

    bool WriteTo(QDataStream &out);
    bool ReadFrom(QDataStream &in);
    [[nodiscard]] QString GetStringBoard() const;

public slots:
    void ChangeSelectedNumber(int newNumber);

private:
    void DrawGridLines();

private:
    QVariant selectedNumber_;
    SudokuModel *sudokuModel_;
};


#endif //QT_SUDOKU_SUDOKUVIEW_HPP
