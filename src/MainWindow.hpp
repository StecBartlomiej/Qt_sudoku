#ifndef QT_SUDOKU_MAINWINDOW_HPP
#define QT_SUDOKU_MAINWINDOW_HPP

#include <QMainWindow>

class QButtonGroup;
class SudokuBoard;
class QHBoxLayout;

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

signals:
    void UpdateTitle();

public slots:
    void Save();
    void SaveAs();
    void Open();

private:
    void SetupCentralWidget();
    void SetupActions();
    void SetupMenuBar();

    void SaveToFile(const QString &fileName);
    void OpenFromFile(const QString &fileName);

private:
    SudokuBoard *sudokuBoard_;
    QButtonGroup *buttonGroup_;

    QString fileName_;

    QAction *save_{};
    QAction *saveAs_{};
    QAction *open_{};
};


#endif //QT_SUDOKU_MAINWINDOW_HPP
