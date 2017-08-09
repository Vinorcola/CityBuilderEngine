#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtWidgets/QMainWindow>

#include "engine/map/Map.hpp"
#include "ui/controlPanel/ControlPanel.hpp"
#include "defines.hpp"

class MainWindow : public QMainWindow
{
        Q_OBJECT

    private:
        const Conf* conf;
        ControlPanel* controlPanel;
        Map* currentMap;
        QAction* pauseAction;
        QAction* speedAction;
#ifdef DEBUG_TOOLS
        QAction* processAction;
#endif

    public:
        MainWindow();

        virtual ~MainWindow();

    public slots:
        void loadMap(const QString& filePath);

        void openSpeedDialog();

    signals:
        void requestSpeedRatioChange(const qreal speedRatio);
};

#endif // MAINWINDOW_HPP
