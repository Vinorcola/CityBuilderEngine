#include "MainWindow.hpp"

#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>

#include "src/engine/map/Map.hpp"
#include "src/engine/map/MapLoader.hpp"
#include "src/engine/processing/TimeCycleProcessor.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/viewer/MapViewer.hpp"
#include "src/ui/controlPanel/ControlPanel.hpp"
#include "src/ui/InformationWidget.hpp"



MainWindow::MainWindow() :
    QMainWindow(),
    conf(new Conf(this, "assets/conf.yaml")),
    controlPanel(new ControlPanel(conf)),
    currentMap(nullptr),
    pauseAction(new QAction(tr("Pause"), this)),
    speedAction(new QAction(tr("Speed"), this)),
#ifdef DEBUG_TOOLS
    processAction(new QAction("Process next step", this)),
#endif
    informationWidget(new InformationWidget(this))
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
    speedAction->setEnabled(true);
    pauseAction->setChecked(false);
    connect(pauseAction, &QAction::toggled, currentMap, &Map::pause);
    connect(this, &MainWindow::requestSpeedRatioChange, currentMap, &Map::setProcessorSpeedRatio);
#ifdef DEBUG_TOOLS
    connect(processAction, &QAction::triggered, currentMap->getProcessor(), &TimeCycleProcessor::forceNextProcess);
#endif

    // Setup information display
    informationWidget->updateBudget(currentMap->getCurrentBudget());
    informationWidget->updatePopulation(currentMap->getCurrentPopulation());
    auto currentDate(currentMap->getCurrentDate());
    informationWidget->updateDate(currentDate.getYear(), currentDate.getMonth());
    connect(currentMap, &Map::budgetChanged, informationWidget, &InformationWidget::updateBudget);
    connect(currentMap, &Map::populationChanged, informationWidget, &InformationWidget::updatePopulation);
    connect(currentMap, &Map::dateChanged, informationWidget, &InformationWidget::updateDate);

    MapViewer* viewer(new MapViewer(*currentMap));
    setCentralWidget(viewer);
    connect(controlPanel, &ControlPanel::buildingRequested, viewer, &MapViewer::buildingRequest);
}



void MainWindow::openSpeedDialog()
{
    bool isPaused(pauseAction->isChecked());
    if (!isPaused) {
        pauseAction->trigger();
    }
    int initialSpeed(currentMap->getProcessor()->getSpeedRatio() * 100.0);
    int speed(QInputDialog::getInt(this, tr("Speed"), tr("Game speed"), initialSpeed, 10, 200, 10));
    if (speed != initialSpeed) {
        emit requestSpeedRatioChange(speed / 100.0);
    }
    if (!isPaused) {
        pauseAction->trigger();
    }
}

