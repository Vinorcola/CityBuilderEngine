#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtCore/QString>
#include <QtWidgets/QAction>
#include <QtWidgets/QMainWindow>

#include "src/defines.hpp"

class Conf;
class ControlPanel;
class InformationWidget;
class Map;

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
        InformationWidget* informationWidget;

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
