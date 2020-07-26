
QT += core gui widgets

TARGET = CityBuilderEngine
CONFIG += c++14

TEMPLATE = app

SOURCES += \
    engine/element/dynamic/Character.cpp \
    engine/element/dynamic/MotionHandler.cpp \
    engine/element/static/behavior/AbstractActivityBehavior.cpp \
    engine/element/static/behavior/AbstractBehavior.cpp \
    engine/element/static/behavior/AbstractWalkerGenerator.cpp \
    engine/element/static/behavior/BehaviorFactory.cpp \
    engine/element/static/behavior/ConditionalRandomWalkerGenerator.cpp \
    engine/element/static/behavior/DeliverymanGenerator.cpp \
    engine/element/static/behavior/FarmBehavior.cpp \
    engine/element/static/behavior/InhabitantContainer.cpp \
    engine/element/static/behavior/ItemStorage.cpp \
    engine/element/static/behavior/QueuedWalkerGenerator.cpp \
    engine/element/static/behavior/RandomWalkerGenerator.cpp \
    engine/element/static/behavior/TargetedWalkerGenerator.cpp \
    engine/element/static/Building.cpp \
    engine/element/static/CityEntryPoint.cpp \
    engine/element/static/NatureElement.cpp \
    engine/element/static/ProcessableBuilding.cpp \
    engine/element/static/Road.cpp \
    engine/map/roadGraph/pathFinder/RoadPathFinder.cpp \
    engine/map/roadGraph/pathFinder/RoadPathFinderNode.cpp \
    engine/map/roadGraph/pathFinder/RoadPathFinderNodeList.cpp \
    engine/map/roadGraph/pathFinder/RoadPathFinderOrderedNodeList.cpp \
    engine/map/roadGraph/RoadGraph.cpp \
    engine/map/roadGraph/RoadGraphNode.cpp \
    engine/map/searchEngine/BuildingSearchCriteria.cpp \
    engine/map/searchEngine/SearchEngine.cpp \
    engine/map/CityStatus.cpp \
    engine/map/Map.cpp \
    engine/map/MapArea.cpp \
    engine/map/MapCoordinates.cpp \
    engine/map/MapLoader.cpp \
    engine/map/MapSize.cpp \
    engine/processing/AbstractProcessable.cpp \
    engine/processing/BuildingProcessor.cpp \
    engine/processing/CharacterProcessor.cpp \
    engine/processing/CycleDate.cpp \
    engine/processing/TimeCycleProcessor.cpp \
    engine/random.cpp \
    exceptions/BadConfigurationException.cpp \
    exceptions/EngineException.cpp \
    exceptions/Exception.cpp \
    exceptions/InvalidMapElementException.cpp \
    exceptions/OutOfRangeException.cpp \
    exceptions/UnexpectedException.cpp \
    global/conf/BehaviorInformation.cpp \
    global/conf/BuildingAreaPartDescription.cpp \
    global/conf/BuildingInformation.cpp \
    global/conf/BuildingSearchCriteriaDescription.cpp \
    global/conf/CharacterInformation.cpp \
    global/conf/Conf.cpp \
    global/conf/ControlPanelElementInformation.cpp \
    global/conf/ItemInformation.cpp \
    global/conf/NatureElementInformation.cpp \
    ui/controlPanel/BuildingButton.cpp \
    ui/controlPanel/ControlPanel.cpp \
    ui/InformationWidget.cpp \
    ui/MainWindow.cpp \
    viewer/DynamicElement.cpp \
    viewer/MapScene.cpp \
    viewer/MapViewer.cpp \
    viewer/SelectionElement.cpp \
    viewer/StaticElement.cpp \
    viewer/Tile.cpp \
    main.cpp

HEADERS += \
    engine/element/dynamic/Character.hpp \
    engine/element/dynamic/MotionHandler.hpp \
    engine/element/static/behavior/AbstractActivityBehavior.hpp \
    engine/element/static/behavior/AbstractBehavior.hpp \
    engine/element/static/behavior/AbstractWalkerGenerator.hpp \
    engine/element/static/behavior/BehaviorFactory.hpp \
    engine/element/static/behavior/ConditionalRandomWalkerGenerator.hpp \
    engine/element/static/behavior/DeliverymanGenerator.hpp \
    engine/element/static/behavior/FarmBehavior.hpp \
    engine/element/static/behavior/InhabitantContainer.hpp \
    engine/element/static/behavior/ItemStorage.hpp \
    engine/element/static/behavior/QueuedWalkerGenerator.hpp \
    engine/element/static/behavior/RandomWalkerGenerator.hpp \
    engine/element/static/behavior/TargetedWalkerGenerator.hpp \
    engine/element/static/Building.hpp \
    engine/element/static/CityEntryPoint.hpp \
    engine/element/static/NatureElement.hpp \
    engine/element/static/ProcessableBuilding.hpp \
    engine/element/static/Road.hpp \
    engine/map/roadGraph/pathFinder/RoadPathFinder.hpp \
    engine/map/roadGraph/pathFinder/RoadPathFinderNode.hpp \
    engine/map/roadGraph/pathFinder/RoadPathFinderNodeList.hpp \
    engine/map/roadGraph/pathFinder/RoadPathFinderOrderedNodeList.hpp \
    engine/map/roadGraph/RoadGraph.hpp \
    engine/map/roadGraph/RoadGraphNode.hpp \
    engine/map/searchEngine/BuildingSearchCriteria.hpp \
    engine/map/searchEngine/SearchEngine.hpp \
    engine/map/CityStatus.hpp \
    engine/map/Map.hpp \
    engine/map/MapArea.hpp \
    engine/map/MapCoordinates.hpp \
    engine/map/MapLoader.hpp \
    engine/map/MapSize.hpp \
    engine/processing/AbstractProcessable.hpp \
    engine/processing/BuildingProcessor.hpp \
    engine/processing/CharacterProcessor.hpp \
    engine/processing/CycleDate.hpp \
    engine/processing/TimeCycleProcessor.hpp \
    engine/random.hpp \
    exceptions/BadConfigurationException.hpp \
    exceptions/EngineException.hpp \
    exceptions/Exception.hpp \
    exceptions/InvalidMapElementException.hpp \
    exceptions/OutOfRangeException.hpp \
    exceptions/UnexpectedException.hpp \
    global/conf/BehaviorInformation.hpp \
    global/conf/BuildingAreaPartDescription.hpp \
    global/conf/BuildingInformation.hpp \
    global/conf/BuildingSearchCriteriaDescription.hpp \
    global/conf/CharacterInformation.hpp \
    global/conf/Conf.hpp \
    global/conf/ControlPanelElementInformation.hpp \
    global/conf/ItemInformation.hpp \
    global/conf/NatureElementInformation.hpp \
    global/yamlLibraryEnhancement.hpp \
    ui/controlPanel/BuildingButton.hpp \
    ui/controlPanel/ControlPanel.hpp \
    ui/InformationWidget.hpp \
    ui/MainWindow.hpp \
    viewer/DynamicElement.hpp \
    viewer/MapScene.hpp \
    viewer/MapViewer.hpp \
    viewer/SelectionElement.hpp \
    viewer/StaticElement.hpp \
    viewer/Tile.hpp \
    defines.hpp

DISTFILES += \
    assets/conf.yaml \
    assets/save/testing-a.yaml \
    assets/save/testing-b.yaml \
    README.md

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += yaml-cpp

win32: INCLUDEPATH += vendor/include
win32: DEPENDPATH += vendor/include
win32: LIBS += -L$$PWD/vendor/yaml-cpp/ -lyaml-cpp
