#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "defines.hpp"
#include "engine/map/Map.hpp"
#include "ui/controlPanel/ControlPanel.hpp"

class MainWindow : public QMainWindow
{
        Q_OBJECT

    private:
        ControlPanel* controlPanel;
        Map* currentMap;
        QAction* pauseAction;
#ifdef DEBUG_TOOLS
        QAction* processAction;
#endif

    public:
        MainWindow();

        virtual ~MainWindow();

        void createMap(const QSize& size);
};

#endif // MAINWINDOW_HPP
