#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtWidgets/QMainWindow>

#include "src/engine/Engine.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/ui/DialogDisplayer.hpp"
#include "src/defines.hpp"

class ControlPanel;
class InformationWidget;
class MapScene;
class QAction;
class QGraphicsView;
class QShortcut;

class MainWindow : public QMainWindow, public DialogDisplayer
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
        QShortcut* rotateAction;
        InformationWidget* informationWidget;
        optional<QWidget*> currentDialog;

    public:
        explicit MainWindow(const QString& gameConfigDirectoryPath);

    public slots:
        void loadMap(const QString& filePath);

        void openSpeedDialog();
        virtual void displayDialog(QDialog& dialog) override;

        void updateState(State state);

    signals:
        void requestSpeedRatioChange(const qreal speedRatio);
};

#endif // MAINWINDOW_HPP
