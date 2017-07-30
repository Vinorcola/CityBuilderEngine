#include "MainWindow.hpp"

#include <QMenuBar>

#include "viewer/MapViewer.hpp"
#include "ui/controlPanel/ControlPanel.hpp"



MainWindow::MainWindow() :
    QMainWindow(),
    controlPanel(new ControlPanel),
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
    quitAction->setShortcut(QKeySequence::Quit);
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



void MainWindow::createMap(const QSize& size)
{
    if (currentMap) {
        delete currentMap;
    }
    currentMap = new Map(size, "assets/conf.yml", {0, 0});
    pauseAction->setChecked(false);
    connect(pauseAction, &QAction::toggled, currentMap, &Map::pause);
#ifdef DEBUG_TOOLS
    connect(processAction, &QAction::triggered, currentMap->getProcessor(), &TimeCycleProcessor::forceNextProcess);
#endif

    MapViewer* viewer(new MapViewer(*currentMap));
    setCentralWidget(viewer);
    connect(controlPanel, &ControlPanel::buildingRequested, viewer, &MapViewer::buildingRequest);

    // Roads
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(0, 1)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(0, 2)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(0, 3)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(3, 4)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(2, 4)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(1, 4)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(0, 4)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(3, 5)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(4, 5)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(5, 5)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(3, 6)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(3, 7)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(3, 8)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(3, 9)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(3, 10)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(4, 10)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(5, 10)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(6, 10)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(7, 10)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(2, 10)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(1, 10)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(0, 10)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Road, MapArea(MapCoordinates(-4, 12)));

    // Buildings
    currentMap->createStaticElement(AbstractStaticMapElement::Type::Maintenance, MapArea(MapCoordinates(1, 5), MapSize(2)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::House, MapArea(MapCoordinates(0, 11), MapSize(2)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::House, MapArea(MapCoordinates(2, 11), MapSize(2)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::House, MapArea(MapCoordinates(4, 11), MapSize(2)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::House, MapArea(MapCoordinates(6, 11), MapSize(2)));
    currentMap->createStaticElement(AbstractStaticMapElement::Type::House, MapArea(MapCoordinates(8, 10), MapSize(2)));
}

