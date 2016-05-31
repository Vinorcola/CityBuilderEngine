#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "engine/map/Map.hpp"





class MainWindow : public QMainWindow
{
        Q_OBJECT


    private:
        Map* currentMap;



    public:
        MainWindow();
        virtual ~MainWindow();



        void createMap(const QSize& size);
};

#endif // MAINWINDOW_HPP
