#include <QApplication>
#include <QDateTime>

#include "src/ui/MainWindow.hpp"





int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    qsrand(QDateTime::currentDateTime().toTime_t());

    MainWindow* window(new MainWindow);
    window->loadMap("assets/save/testing-b.yaml");
    window->showMaximized();

    return a.exec();
}
