
QT += core gui widgets

TARGET = CityBuilderEngine
CONFIG += c++14

TEMPLATE = app

SOURCES += \
    engine/element/dynamic/AbstractDynamicMapElement.cpp \
    engine/element/dynamic/RandomWalker.cpp \
    engine/element/dynamic/TargetedWalker.cpp \
    engine/element/static/AbstractProcessableStaticMapElement.cpp \
    engine/element/static/AbstractStaticMapElement.cpp \
    engine/element/static/CityEntryPoint.cpp \
    engine/element/static/HousingBuilding.cpp \
    engine/element/static/MaintenanceBuilding.cpp \
    engine/element/static/Road.cpp \
    engine/element/AbstractMapElement.cpp \
    engine/map/roadGraph/RoadGraph.cpp \
    engine/map/roadGraph/RoadGraphNode.cpp \
    engine/map/roadGraph/RoadPathFinder.cpp \
    engine/map/roadGraph/RoadPathFinderNode.cpp \
    engine/map/roadGraph/RoadPathFinderNodeList.cpp \
    engine/map/roadGraph/RoadPathFinderOrderedNodeList.cpp \
    engine/map/CityStatus.cpp \
    engine/map/Map.cpp \
    engine/map/MapArea.cpp \
    engine/map/MapCoordinates.cpp \
    engine/map/MapSize.cpp \
    engine/processing/AbstractProcessable.cpp \
    engine/processing/CycleDate.cpp \
    engine/processing/TimeCycleProcessor.cpp \
    engine/random.cpp \
    exceptions/BadConfigurationException.cpp \
    exceptions/EngineException.cpp \
    exceptions/Exception.cpp \
    exceptions/InvalidMapElementException.cpp \
    exceptions/OutOfRangeException.cpp \
    exceptions/UnexpectedException.cpp \
    global/conf/Conf.cpp \
    global/conf/DynamicElementInformation.cpp \
    global/conf/StaticElementAreaPartDescription.cpp \
    global/conf/StaticElementInformation.cpp \
    ui/controlPanel/BuildingButton.cpp \
    ui/controlPanel/BuildingPage.cpp \
    ui/controlPanel/ControlPanel.cpp \
    ui/MainWindow.cpp \
    viewer/DynamicElement.cpp \
    viewer/MapScene.cpp \
    viewer/MapViewer.cpp \
    viewer/SelectionElement.cpp \
    viewer/StaticElement.cpp \
    viewer/Tile.cpp \
    main.cpp

HEADERS += \
    engine/element/dynamic/AbstractDynamicMapElement.hpp \
    engine/element/dynamic/RandomWalker.hpp \
    engine/element/dynamic/TargetedWalker.hpp \
    engine/element/static/AbstractProcessableStaticMapElement.hpp \
    engine/element/static/AbstractStaticMapElement.hpp \
    engine/element/static/CityEntryPoint.hpp \
    engine/element/static/HousingBuilding.hpp \
    engine/element/static/MaintenanceBuilding.hpp \
    engine/element/static/Road.hpp \
    engine/element/AbstractMapElement.hpp \
    engine/map/roadGraph/RoadGraph.hpp \
    engine/map/roadGraph/RoadGraphNode.hpp \
    engine/map/roadGraph/RoadPathFinder.hpp \
    engine/map/roadGraph/RoadPathFinderNode.hpp \
    engine/map/roadGraph/RoadPathFinderNodeList.hpp \
    engine/map/roadGraph/RoadPathFinderOrderedNodeList.hpp \
    engine/map/CityStatus.hpp \
    engine/map/Map.hpp \
    engine/map/MapArea.hpp \
    engine/map/MapCoordinates.hpp \
    engine/map/MapSize.hpp \
    engine/processing/AbstractProcessable.hpp \
    engine/processing/CycleDate.hpp \
    engine/processing/TimeCycleProcessor.hpp \
    engine/random.hpp \
    exceptions/BadConfigurationException.hpp \
    exceptions/EngineException.hpp \
    exceptions/Exception.hpp \
    exceptions/InvalidMapElementException.hpp \
    exceptions/OutOfRangeException.hpp \
    exceptions/UnexpectedException.hpp \
    global/conf/Conf.hpp \
    global/conf/DynamicElementInformation.hpp \
    global/conf/StaticElementAreaPartDescription.hpp \
    global/conf/StaticElementInformation.hpp \
    ui/controlPanel/BuildingButton.hpp \
    ui/controlPanel/BuildingPage.hpp \
    ui/controlPanel/ControlPanel.hpp \
    ui/MainWindow.hpp \
    viewer/DynamicElement.hpp \
    viewer/MapScene.hpp \
    viewer/MapViewer.hpp \
    viewer/SelectionElement.hpp \
    viewer/StaticElement.hpp \
    viewer/Tile.hpp \
    defines.hpp

DISTFILES += \
    assets/conf.yml \
    README.md

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += yaml-cpp
