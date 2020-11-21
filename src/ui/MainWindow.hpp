#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtCore/QString>
#include <QtWidgets/QMainWindow>

#include "src/engine/Engine.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/defines.hpp"

class ControlPanel;
class InformationWidget;
class MapScene;
class QAciton;
class QGraphicsView;

class MainWindow : public QMainWindow
{
        Q_OBJECT

    private:
        const Conf conf;
        Engine engine;
        MapScene* viewerScene;
        QGraphicsView* viewer;
        ControlPanel* controlPanel;
        QAction* pauseAction;
        QAction* speedAction;
#ifdef DEBUG_TOOLS
        QAction* processAction;
#endif
        InformationWidget* informationWidget;

    public:
        MainWindow();

    public slots:
        void loadMap(const QString& filePath);

        void openSpeedDialog();

        void updateState(State state);

    signals:
        void requestSpeedRatioChange(const qreal speedRatio);
};

#endif // MAINWINDOW_HPP
