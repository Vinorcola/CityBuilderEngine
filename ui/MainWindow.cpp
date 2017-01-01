#include "MainWindow.hpp"

#include <QMenuBar>

#include "viewer/MapViewer.hpp"
#include "ui/controlPanel/ControlPanel.hpp"





MainWindow::MainWindow() :
    QMainWindow(),
    controlPanel(new ControlPanel),
    currentMap(nullptr)
{
    // Menus.
    QMenu* gameMenu(menuBar()->addMenu(tr("Game")));

    QAction* quitAction(new QAction(tr("Close the game"), this));
    quitAction->setShortcut(QKeySequence::Quit);
    gameMenu->addAction(quitAction);

    connect(quitAction, &QAction::triggered, this, &MainWindow::close);

    // Control panel.
    addDockWidget(Qt::RightDockWidgetArea, controlPanel);
}





MainWindow::~MainWindow()
{
    if (currentMap)
    {
        delete currentMap;
    }
}





void MainWindow::createMap(const QSize& size)
{
    if (currentMap)
    {
        delete currentMap;
    }
    currentMap = new Map(size, "assets/conf.yml");

    MapViewer* viewer(new MapViewer(*currentMap));
    setCentralWidget(viewer);
    connect(controlPanel, &ControlPanel::buildingRequested, viewer, &MapViewer::buildingRequest);

    // Roads
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(3, 4)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(2, 4)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(1, 4)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(0, 4)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(3, 5)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(4, 5)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(5, 5)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(3, 6)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(3, 7)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(3, 8)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(3, 9)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(3, 10)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(4, 10)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(5, 10)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(6, 10)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(7, 10)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(2, 10)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(1, 10)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(0, 10)));
    currentMap->createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(-4, 12)));

    // Buildings
    currentMap->createStaticElement(Map::StaticElementType::Maintenance, MapArea(MapCoordinates(1, 5), MapSize(2)));
}

