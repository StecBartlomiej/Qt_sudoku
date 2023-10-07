#ifndef QT_SUDOKU_MAINWINDOW_HPP
#define QT_SUDOKU_MAINWINDOW_HPP

#include <QMainWindow>

class QButtonGroup;
class SudokuView;
class QHBoxLayout;

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

    void SaveToFile(const QString &fileName);
    void OpenFromFile(const QString &fileName);

signals:
    void UpdateTitle();

public slots:
    void Save();
    void SaveAs();
    void Open();
    void CopyToClipboard();
    void ClearSudoku();

private:
    static void SetupStyleSheet();
    void SetupCentralWidget();
    void SetupActions();
    void SetupMenuBar();

public:
    static constexpr int qtVersion = QDataStream::Version::Qt_6_0;

private:
    SudokuView *sudokuView_;
    QButtonGroup *buttonGroup_;

    QString fileName_;

    QAction *save_{};
    QAction *saveAs_{};
    QAction *open_{};
    QAction *copy_{};

    QAction *solveSudoku_{};
    QAction *clearSudoku_{};
};


#endif //QT_SUDOKU_MAINWINDOW_HPP
