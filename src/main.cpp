#include <QApplication>

#include "src/ui/MainWindow.hpp"



int main(int argc, char* argv[])
{
    QApplication application(argc, argv);

    auto window(new MainWindow("assets/zeus"));
    window->loadMap("assets/zeus/maps/testing-with-houses.yaml");
    window->showMaximized();

    return application.exec();
}
