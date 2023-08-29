#include "MainWindow.hpp"
#include "SudokuBoard.hpp"

#include <QFileDialog>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QMessageBox>


MainWindow::MainWindow() : sudokuBoard_{new SudokuBoard(this)}, buttonGroup_{new QButtonGroup(this)}
{
    resize(1200, 800);
    setWindowTitle(tr("Sudoku"));

    SetupCentralWidget();
    SetupActions();
}

void MainWindow::SetupActions()
{
    connect(buttonGroup_, &QButtonGroup::idToggled, sudokuBoard_, &SudokuBoard::ChangeSelectedNumber);

    saveAs_ = new QAction("&Save");
    saveAs_->setStatusTip(tr("Saves current game"));
    connect(saveAs_, &QAction::toggled, this, &MainWindow::SaveAs);

}

void MainWindow::SetupCentralWidget()
{
    auto buttonLayout = CreateButtonLayout();

    auto mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(20, 20, 20, 20);

    mainLayout->addWidget(sudokuBoard_);
    mainLayout->addLayout(buttonLayout);

    auto mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
}

QHBoxLayout *MainWindow::CreateButtonLayout()
{
    auto buttonLayout = new QHBoxLayout();
    buttonGroup_->setExclusive(true);

    for (int i = 1; i <= 9; ++i)
    {
        auto button = new QPushButton();
        button->setCheckable(true);
        button->setText(QString::number(i));

        buttonGroup_->addButton(button, i);
        buttonLayout->addWidget(button);
    }
    return buttonLayout;
}

void MainWindow::SaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save sudoku game")),
                                                    tr("Sudoku Game (*.sud);;All Files (*)");
    if (fileName.isEmpty())
        return;
//    sudokuBoard_->SaveToFile(fileName);
}

