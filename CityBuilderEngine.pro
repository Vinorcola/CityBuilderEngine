
QT += core gui widgets

TARGET = CityBuilderEngine
CONFIG += c++14

TEMPLATE = app

SOURCES += \
    engine/element/dynamic/AbstractDynamicMapElement.cpp \
    engine/element/dynamic/RandomWalker.cpp \
    engine/element/dynamic/TargetedWalker.cpp \
    engine/element/static/behavior/AbstractStaticElementBehavior.cpp \
    engine/element/static/behavior/ConditionalRandomWalkerGenerator.cpp \
    engine/element/static/behavior/RandomWalkerGenerator.cpp \
    engine/element/static/behavior/TargetedWalkerGenerator.cpp \
    engine/element/static/AbstractProcessableStaticMapElement.cpp \
    engine/element/static/AbstractStaticMapElement.cpp \
    engine/element/static/CityEntryPoint.cpp \
    engine/element/static/CultureBuilding.cpp \
    engine/element/static/HousingBuilding.cpp \
    engine/element/static/Road.cpp \
    engine/element/static/ServiceBuilding.cpp \
    engine/element/AbstractMapElement.cpp \
    engine/map/roadGraph/RoadGraph.cpp \
    engine/map/roadGraph/RoadGraphNode.cpp \
    engine/map/roadGraph/RoadPathFinder.cpp \
    engine/map/roadGraph/RoadPathFinderNode.cpp \
    engine/map/roadGraph/RoadPathFinderNodeList.cpp \
    engine/map/roadGraph/RoadPathFinderOrderedNodeList.cpp \
    engine/map/searchEngine/SearchEngine.cpp \
    engine/map/searchEngine/StaticSearchCriteria.cpp \
    engine/map/CityStatus.cpp \
    engine/map/Map.cpp \
    engine/map/MapArea.cpp \
    engine/map/MapCoordinates.cpp \
    engine/map/MapLoader.cpp \
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
    global/conf/ControlPanelElementInformation.cpp \
    global/conf/DynamicElementInformation.cpp \
    global/conf/StaticElementAreaPartDescription.cpp \
    global/conf/StaticElementInformation.cpp \
    global/conf/StaticSearchCriteriaDescription.cpp \
    ui/controlPanel/BuildingButton.cpp \
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
    engine/element/static/behavior/AbstractStaticElementBehavior.hpp \
    engine/element/static/behavior/ConditionalRandomWalkerGenerator.hpp \
    engine/element/static/behavior/RandomWalkerGenerator.hpp \
    engine/element/static/behavior/TargetedWalkerGenerator.hpp \
    engine/element/static/AbstractProcessableStaticMapElement.hpp \
    engine/element/static/AbstractStaticMapElement.hpp \
    engine/element/static/CityEntryPoint.hpp \
    engine/element/static/CultureBuilding.hpp \
    engine/element/static/HousingBuilding.hpp \
    engine/element/static/Road.hpp \
    engine/element/static/ServiceBuilding.hpp \
    engine/element/AbstractMapElement.hpp \
    engine/map/roadGraph/RoadGraph.hpp \
    engine/map/roadGraph/RoadGraphNode.hpp \
    engine/map/roadGraph/RoadPathFinder.hpp \
    engine/map/roadGraph/RoadPathFinderNode.hpp \
    engine/map/roadGraph/RoadPathFinderNodeList.hpp \
    engine/map/roadGraph/RoadPathFinderOrderedNodeList.hpp \
    engine/map/searchEngine/SearchEngine.hpp \
    engine/map/searchEngine/StaticSearchCriteria.hpp \
    engine/map/CityStatus.hpp \
    engine/map/Map.hpp \
    engine/map/MapArea.hpp \
    engine/map/MapCoordinates.hpp \
    engine/map/MapLoader.hpp \
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
    global/conf/ControlPanelElementInformation.hpp \
    global/conf/DynamicElementInformation.hpp \
    global/conf/StaticElementAreaPartDescription.hpp \
    global/conf/StaticElementInformation.hpp \
    global/conf/StaticSearchCriteriaDescription.hpp \
    ui/controlPanel/BuildingButton.hpp \
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
    assets/save/testing.yml \
    assets/conf.yml \
    README.md

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += yaml-cpp

win32: INCLUDEPATH += vendor/include
win32: DEPENDPATH += vendor/include
win32: LIBS += -L$$PWD/vendor/yaml-cpp/ -lyaml-cpp
