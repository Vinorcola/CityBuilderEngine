#include "MainWindow.hpp"

#include <QtWidgets/QInputDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QShortcut>

#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/ui/controlPanel/ControlPanel.hpp"
#include "src/ui/InformationWidget.hpp"
#include "src/viewer/MapScene.hpp"



MainWindow::MainWindow() :
    QMainWindow(),
    conf("assets/conf.yaml"),
    engine(conf),
    viewerScene(nullptr),
    viewer(nullptr),
    controlPanel(new ControlPanel(conf)),
    pauseAction(new QAction(tr("Pause"), this)),
    speedAction(new QAction(tr("Speed"), this)),
#ifdef DEBUG_TOOLS
    processAction(new QAction("Process next step", this)),
#endif
    rotateAction(new QShortcut(Qt::Key_R, this)),
    informationWidget(new InformationWidget(this)),
    currentDialog(nullptr)
{
    // Game menu.
    QMenu* gameMenu(menuBar()->addMenu(tr("Game")));

    pauseAction->setShortcuts({ Qt::Key_P, Qt::Key_Pause });
    pauseAction->setCheckable(true);
    gameMenu->addAction(pauseAction);

    QAction* quitAction(new QAction(tr("Close the game"), this));
    quitAction->setShortcut(QKeySequence::Quit);
    gameMenu->addAction(quitAction);
    connect(quitAction, &QAction::triggered, this, &MainWindow::close);

    // Options menu.
    QMenu* optionsMenu(menuBar()->addMenu(tr("Options")));

    speedAction->setDisabled(true);
    optionsMenu->addAction(speedAction);
    connect(speedAction, &QAction::triggered, this, &MainWindow::openSpeedDialog);

#ifdef DEBUG_TOOLS
    // Debug menu.
    QMenu* debugMenu(menuBar()->addMenu("Debug"));

    processAction->setShortcut(Qt::Key_Space);
    processAction->setDisabled(true);
    connect(pauseAction, &QAction::toggled, processAction, [this](bool pause) {
        processAction->setDisabled(!pause);
    });
    debugMenu->addAction(processAction);
#endif

    // Informaiton widget.
    menuBar()->setCornerWidget(informationWidget);

    // Control panel.
    addDockWidget(Qt::RightDockWidgetArea, controlPanel);

    // Communication with the engine.
    connect(pauseAction, &QAction::triggered, &engine, &Engine::pause);
    connect(this, &MainWindow::requestSpeedRatioChange, &engine, &Engine::setProcessorSpeedRatio);
#ifdef DEBUG_TOOLS
    connect(processAction, &QAction::triggered, &engine, &Engine::forceNextProcess);
#endif
    connect(&engine, &Engine::stateUpdated, this, &MainWindow::updateState);
}



void MainWindow::loadMap(const QString& filePath)
{
    if (viewer) {
        delete viewer;
    }
    if (viewerScene) {
        delete viewerScene;
    }
    engine.loadCity(filePath);
    const auto initialState(engine.getCurrentState());
    informationWidget->updateState(initialState.city);

    viewerScene = new MapScene(conf, engine, engine, *this, engine.getMapState(), initialState);
    viewer = new QGraphicsView(viewerScene);
    setCentralWidget(viewer);
    connect(controlPanel, &ControlPanel::buildingRequested, viewerScene, &MapScene::requestBuildingPositioning);
    connect(rotateAction, &QShortcut::activated, viewerScene, &MapScene::requestBuildingRotation);
    connect(viewerScene, &MapScene::buildingCreationRequested, &engine, &Engine::createBuilding);

    speedAction->setEnabled(true);
    pauseAction->setChecked(false);
    engine.pause(false);
}



void MainWindow::openSpeedDialog()
{
    bool isPaused(pauseAction->isChecked());
    if (!isPaused) {
        pauseAction->trigger();
    }
    int initialSpeed(engine.getProcessorSpeedRatio() * 100.0);
    int speed(QInputDialog::getInt(this, tr("Speed"), tr("Game speed"), initialSpeed, 10, 200, 10));
    if (speed != initialSpeed) {
        emit requestSpeedRatioChange(speed / 100.0);
    }
    if (!isPaused) {
        pauseAction->trigger();
    }
}



void MainWindow::displayDialog(QDialog& dialog)
{
    bool isPaused(pauseAction->isChecked());
    if (!isPaused) {
        pauseAction->trigger();
    }

    currentDialog = &dialog;
    dialog.setParent(this);
    dialog.setWindowFlag(Qt::Popup);
    dialog.exec();

    if (!isPaused) {
        pauseAction->trigger();
    }
}



void MainWindow::updateState(State state)
{
    informationWidget->updateState(state.city);
    viewerScene->refresh(state);
}
