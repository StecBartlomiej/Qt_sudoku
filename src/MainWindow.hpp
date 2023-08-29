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

private:
    void SetupCentralWidget();
    [[nodiscard]] QHBoxLayout* CreateButtonLayout();
    void SetupActions();
//    void Save();
    void SaveAs();

    // TODO - add save, open actions and menus
private:
    SudokuBoard *sudokuBoard_;
    QButtonGroup *buttonGroup_;

    QAction *save_{};
    QAction *saveAs_{};
    QAction *open_{};
};


#endif //QT_SUDOKU_MAINWINDOW_HPP
