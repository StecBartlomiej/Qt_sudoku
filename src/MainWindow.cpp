#include "MainWindow.hpp"
#include "SudokuView.hpp"

#include <QApplication>
#include <QFileDialog>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QClipboard>


MainWindow::MainWindow() : sudokuView_{new SudokuView(this)}, buttonGroup_{new QButtonGroup(this)}, fileName_{}
{
    setAttribute(Qt::WA_DeleteOnClose);

    resize(800, 850);
    setWindowTitle(fileName_);

    SetupStyleSheet();
    SetupActions();
    SetupCentralWidget();
    SetupMenuBar();
}

void MainWindow::SetupStyleSheet()
{
    QFile file("../stylesheet.qss");
    if (!file.open(QIODevice::ReadOnly))
        return ;

    QString styleSheet = file.readAll();
    qApp->setStyleSheet(styleSheet);

}

void MainWindow::SetupActions()
{
    for (int i = 1; i <= 9; ++i)
    {
        auto button = new QPushButton();
        button->setCheckable(true);
        button->setText(QString::number(i));

        buttonGroup_->addButton(button, i);
    }
    connect(buttonGroup_, &QButtonGroup::idToggled, sudokuView_, &SudokuView::ChangeSelectedNumber);

    connect(this, &MainWindow::UpdateTitle, [=](){ setWindowTitle(fileName_); });

    saveAs_ = new QAction(tr("S&ave As"));
    saveAs_->setShortcut(QKeySequence::SaveAs);
    saveAs_->setStatusTip(tr("Save to file"));
    connect(saveAs_, &QAction::triggered, this, &MainWindow::SaveAs);

    save_ = new QAction(tr("&Save"));
    save_->setShortcut(QKeySequence::Save);
    save_->setStatusTip(tr("Save progress"));
    connect(save_, &QAction::triggered, this, &MainWindow::Save);

    open_ = new QAction(tr("Open"));
    open_->setShortcut(QKeySequence::Open);
    open_->setStatusTip(tr("Open sudoku file"));
    connect(open_, &QAction::triggered, this, &MainWindow::Open);

    copy_ = new QAction(tr("Copy"));
    copy_->setShortcut(QKeySequence::Copy);
    copy_->setStatusTip(tr("Copy text representation of board clipboard"));
    connect(copy_, &QAction::triggered, this, &MainWindow::CopyToClipboard);

    solveSudoku_ = new QAction(tr("Solve"));
    solveSudoku_->setStatusTip(tr("Solves sudoku"));
    connect(solveSudoku_, &QAction::triggered, sudokuView_, &SudokuView::SolveSudoku);

    clearSudoku_ = new QAction(tr("Clear"));
    clearSudoku_->setStatusTip(tr("Clears sudoku"));
    // TODO
//    connect(clearSudoku_, &QAction::triggered, this, &MainWindow::ClearSudoku);
}

void MainWindow::SetupCentralWidget()
{
    auto buttonLayout = new QHBoxLayout();

    // QT does not allow for partial selection in buttonGroup
    // TODO - create custom Button Group class with partial, exclusive selection
    buttonGroup_->setExclusive(true);

    for (int i = 1; i <= 9; ++i)
        buttonLayout->addWidget(buttonGroup_->button(i));


    auto mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(20, 20, 20, 20);

    mainLayout->addWidget(sudokuView_);
    mainLayout->addLayout(buttonLayout);

    auto mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
}

void MainWindow::SetupMenuBar()
{
    auto fileMenu = menuBar()->addMenu(tr("&File"));

    fileMenu->addAction(open_);
    fileMenu->addAction(save_);
    fileMenu->addAction(saveAs_);

    auto barMenu = menuBar()->addMenu(tr("&Edit"));
    barMenu->addAction(copy_);

    menuBar()->addAction(solveSudoku_);
    menuBar()->addAction(clearSudoku_);
}

void MainWindow::SaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Sudoku Game"),
                                                    ".",
                                                    tr("Sudoku Game (*.sud);;All Files (*)"));
    if (!fileName.isEmpty())
        SaveToFile(fileName);
}

void MainWindow::Save()
{
    if (!fileName_.isEmpty())
        SaveToFile(fileName_);
    else
        SaveAs();
}

void MainWindow::Open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Sudoku Game"),
                                                    ".",
                                                    tr("Sudoku Game (*.sud);;All Files (*)"));
    if (!fileName.isEmpty())
        OpenFromFile(fileName);
}

void MainWindow::SaveToFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::OpenModeFlag::WriteOnly))
    {
        QMessageBox::warning(this, tr("Save File"), tr("Cannot write file %1::\n%2").arg(file.fileName()).arg(file.errorString()));
        return;
    }
    QDataStream out(&file);
    out.setVersion(qtVersion);

    bool success = sudokuView_->WriteTo(out);

    if (success)
    {
        fileName_ = fileName;
        emit UpdateTitle();
        statusBar()->showMessage(tr("%1 file was saved").arg(fileName_));
    }
    else
        QMessageBox::warning(this, tr("Save File"), tr("Failed to save %1 file").arg(fileName_));
}

void MainWindow::OpenFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::OpenModeFlag::ReadOnly))
    {
        QMessageBox::warning(this, tr("Open File"), tr("Cannot read file %1::\n%2").arg(file.fileName()).arg(file.errorString()));
        return;
    }
    QDataStream in(&file);
    in.setVersion(qtVersion);

    bool success = sudokuView_->ReadFrom(in);

    if (success)
    {
        fileName_ = fileName;
        emit UpdateTitle();
        statusBar()->showMessage(tr("%1 file was successfully opened").arg(fileName_));
    }
    else
        QMessageBox::warning(this, tr("Open File"), tr("Failed to open %1 file").arg(fileName_));
}

void MainWindow::CopyToClipboard()
{
    QApplication::clipboard()->setText(sudokuView_->GetStringBoard());
}

