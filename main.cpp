#include <QApplication>
#include <QDateTime>

#include "ui/MainWindow.hpp"





int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    qsrand(QDateTime::currentDateTime().toTime_t());

    MainWindow* window(new MainWindow);
    window->createMap({ 23, 23 });
    window->show();

    return a.exec();
}
