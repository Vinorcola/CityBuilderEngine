#include <QApplication>
#include <QDateTime>

#include "ui/MainWindow.hpp"





int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    qsrand(QDateTime::currentDateTime().toTime_t());

    MainWindow* window(new MainWindow);
    window->loadMap("assets/save/testing.yaml");
    window->showMaximized();

    return a.exec();
}
