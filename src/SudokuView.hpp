#ifndef QT_SUDOKU_SUDOKUVIEW_HPP
#define QT_SUDOKU_SUDOKUVIEW_HPP

#include <QTableView>

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

    void SolveSudoku();
    void ClearSudoku();

private:
    void paintEvent(QPaintEvent *event) override;

private:
    SudokuModel *sudokuModel_;
    QVariant selectedNumber_;
};


#endif //QT_SUDOKU_SUDOKUVIEW_HPP
