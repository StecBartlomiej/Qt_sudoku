#include <QApplication>
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app{argc, argv};

    auto mainWindow = new MainWindow();
    mainWindow->show();

    return app.exec();
}
