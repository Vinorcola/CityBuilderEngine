#include "MainWindow.hpp"

#include <QtWidgets/QMenuBar>

#include "viewer/MapViewer.hpp"
#include "ui/controlPanel/ControlPanel.hpp"



MainWindow::MainWindow() :
    QMainWindow(),
    conf(new Conf(this, "assets/conf.yml")),
    controlPanel(new ControlPanel(conf)),
    currentMap(nullptr),
    pauseAction(new QAction(tr("Pause"), this))
#ifdef DEBUG_TOOLS
    ,
    processAction(new QAction("Process next step", this))
#endif
{
    // Menus.
    QMenu* gameMenu(menuBar()->addMenu(tr("Game")));

    pauseAction->setShortcuts({ Qt::Key_P, Qt::Key_Pause });
    pauseAction->setCheckable(true);
    gameMenu->addAction(pauseAction);

    QAction* quitAction(new QAction(tr("Close the game"), this));
    quitAction->setShortcuts({ Qt::CTRL + Qt::Key_Q, QKeySequence::Quit });
    gameMenu->addAction(quitAction);
    connect(quitAction, &QAction::triggered, this, &MainWindow::close);

#ifdef DEBUG_TOOLS
    QMenu* debugMenu(menuBar()->addMenu("Debug"));

    processAction->setShortcut(Qt::Key_Space);
    processAction->setDisabled(true);
    connect(pauseAction, &QAction::toggled, processAction, [this](bool pause) {
        processAction->setDisabled(!pause);
    });
    debugMenu->addAction(processAction);
#endif

    // Control panel.
    addDockWidget(Qt::RightDockWidgetArea, controlPanel);
}



MainWindow::~MainWindow()
{
    if (currentMap) {
        delete currentMap;
    }
}



void MainWindow::loadMap(const QString& filePath)
{
    if (currentMap) {
        delete currentMap;
    }
    currentMap = new Map(conf, MapLoader(filePath));
    pauseAction->setChecked(false);
    connect(pauseAction, &QAction::toggled, currentMap, &Map::pause);
#ifdef DEBUG_TOOLS
    connect(processAction, &QAction::triggered, currentMap->getProcessor(), &TimeCycleProcessor::forceNextProcess);
#endif

    MapViewer* viewer(new MapViewer(*currentMap));
    setCentralWidget(viewer);
    connect(controlPanel, &ControlPanel::buildingRequested, viewer, &MapViewer::buildingRequest);
}

