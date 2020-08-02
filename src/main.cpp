#include <QApplication>
#include <QDateTime>

#include "src/ui/MainWindow.hpp"



int main(int argc, char* argv[])
{
    QApplication application(argc, argv);

    MainWindow* window(new MainWindow);
    window->loadMap("assets/save/testing-b.yaml");
    window->showMaximized();

    return application.exec();
}
