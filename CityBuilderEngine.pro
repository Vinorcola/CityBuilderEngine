
QT += core gui widgets

TARGET = CityBuilderEngine
CONFIG += c++14

TEMPLATE = app

SOURCES += \
    src/engine/element/dynamic/Character.cpp \
    src/engine/element/dynamic/MotionHandler.cpp \
    src/engine/element/static/behavior/AbstractActivityBehavior.cpp \
    src/engine/element/static/behavior/AbstractBehavior.cpp \
    src/engine/element/static/behavior/AbstractWalkerGenerator.cpp \
    src/engine/element/static/behavior/BehaviorFactory.cpp \
    src/engine/element/static/behavior/ConditionalRandomWalkerGenerator.cpp \
    src/engine/element/static/behavior/DeliverymanGenerator.cpp \
    src/engine/element/static/behavior/FarmBehavior.cpp \
    src/engine/element/static/behavior/InhabitantContainer.cpp \
    src/engine/element/static/behavior/ItemStorage.cpp \
    src/engine/element/static/behavior/QueuedWalkerGenerator.cpp \
    src/engine/element/static/behavior/RandomWalkerGenerator.cpp \
    src/engine/element/static/behavior/TargetedWalkerGenerator.cpp \
    src/engine/element/static/Building.cpp \
    src/engine/element/static/CityEntryPoint.cpp \
    src/engine/element/static/NatureElement.cpp \
    src/engine/element/static/ProcessableBuilding.cpp \
    src/engine/element/static/Road.cpp \
    src/engine/map/path/RandomRoadPath.cpp \
    src/engine/map/path/TargetedPath.cpp \
    src/engine/map/pathFinder/PathFinder.cpp \
    src/engine/map/pathFinder/PathFinderNode.cpp \
    src/engine/map/pathFinder/ProcessedPathFinderNodeList.cpp \
    src/engine/map/pathFinder/UnprocessedPathFinderNodeList.cpp \
    src/engine/map/roadGraph/pathFinder/RoadPathFinder.cpp \
    src/engine/map/roadGraph/pathFinder/RoadPathFinderNode.cpp \
    src/engine/map/roadGraph/pathFinder/RoadPathFinderNodeList.cpp \
    src/engine/map/roadGraph/pathFinder/RoadPathFinderOrderedNodeList.cpp \
    src/engine/map/roadGraph/RoadGraph.cpp \
    src/engine/map/roadGraph/RoadGraphNode.cpp \
    src/engine/map/searchEngine/BuildingSearchCriteria.cpp \
    src/engine/map/searchEngine/SearchEngine.cpp \
    src/engine/map/CityStatus.cpp \
    src/engine/map/Map.cpp \
    src/engine/map/MapArea.cpp \
    src/engine/map/MapCoordinates.cpp \
    src/engine/map/MapLoader.cpp \
    src/engine/map/MapSize.cpp \
    src/engine/map/RoadLocationCache.cpp \
    src/engine/map/TraversableLocationCache.cpp \
    src/engine/processing/AbstractProcessable.cpp \
    src/engine/processing/BuildingProcessor.cpp \
    src/engine/processing/CharacterProcessor.cpp \
    src/engine/processing/CycleDate.cpp \
    src/engine/processing/TimeCycleProcessor.cpp \
    src/engine/random.cpp \
    src/exceptions/BadConfigurationException.cpp \
    src/exceptions/EngineException.cpp \
    src/exceptions/Exception.cpp \
    src/exceptions/InvalidMapElementException.cpp \
    src/exceptions/NotImplementedException.cpp \
    src/exceptions/OutOfRangeException.cpp \
    src/exceptions/UnexpectedException.cpp \
    src/global/conf/BehaviorInformation.cpp \
    src/global/conf/BuildingAreaPartDescription.cpp \
    src/global/conf/BuildingInformation.cpp \
    src/global/conf/BuildingSearchCriteriaDescription.cpp \
    src/global/conf/CharacterInformation.cpp \
    src/global/conf/Conf.cpp \
    src/global/conf/ControlPanelElementInformation.cpp \
    src/global/conf/ItemInformation.cpp \
    src/global/conf/NatureElementInformation.cpp \
    src/ui/controlPanel/BuildingButton.cpp \
    src/ui/controlPanel/ControlPanel.cpp \
    src/ui/InformationWidget.cpp \
    src/ui/MainWindow.cpp \
    src/viewer/DynamicElement.cpp \
    src/viewer/MapScene.cpp \
    src/viewer/MapViewer.cpp \
    src/viewer/SelectionElement.cpp \
    src/viewer/StaticElement.cpp \
    src/viewer/Tile.cpp \
    src/main.cpp

HEADERS += \
    src/engine/element/dynamic/Character.hpp \
    src/engine/element/dynamic/MotionHandler.hpp \
    src/engine/element/static/behavior/AbstractActivityBehavior.hpp \
    src/engine/element/static/behavior/AbstractBehavior.hpp \
    src/engine/element/static/behavior/AbstractWalkerGenerator.hpp \
    src/engine/element/static/behavior/BehaviorFactory.hpp \
    src/engine/element/static/behavior/ConditionalRandomWalkerGenerator.hpp \
    src/engine/element/static/behavior/DeliverymanGenerator.hpp \
    src/engine/element/static/behavior/FarmBehavior.hpp \
    src/engine/element/static/behavior/InhabitantContainer.hpp \
    src/engine/element/static/behavior/ItemStorage.hpp \
    src/engine/element/static/behavior/QueuedWalkerGenerator.hpp \
    src/engine/element/static/behavior/RandomWalkerGenerator.hpp \
    src/engine/element/static/behavior/TargetedWalkerGenerator.hpp \
    src/engine/element/static/Building.hpp \
    src/engine/element/static/CityEntryPoint.hpp \
    src/engine/element/static/NatureElement.hpp \
    src/engine/element/static/ProcessableBuilding.hpp \
    src/engine/element/static/Road.hpp \
    src/engine/map/path/MapDetailsInterface.hpp \
    src/engine/map/path/PathInterface.hpp \
    src/engine/map/path/RandomRoadPath.hpp \
    src/engine/map/path/TargetedPath.hpp \
    src/engine/map/pathFinder/PathFinder.hpp \
    src/engine/map/pathFinder/PathFinderNode.hpp \
    src/engine/map/pathFinder/ProcessedPathFinderNodeList.hpp \
    src/engine/map/pathFinder/UnprocessedPathFinderNodeList.hpp \
    src/engine/map/roadGraph/pathFinder/RoadPathFinder.hpp \
    src/engine/map/roadGraph/pathFinder/RoadPathFinderNode.hpp \
    src/engine/map/roadGraph/pathFinder/RoadPathFinderNodeList.hpp \
    src/engine/map/roadGraph/pathFinder/RoadPathFinderOrderedNodeList.hpp \
    src/engine/map/roadGraph/RoadGraph.hpp \
    src/engine/map/roadGraph/RoadGraphNode.hpp \
    src/engine/map/searchEngine/BuildingSearchCriteria.hpp \
    src/engine/map/searchEngine/SearchEngine.hpp \
    src/engine/map/CityStatus.hpp \
    src/engine/map/Map.hpp \
    src/engine/map/MapArea.hpp \
    src/engine/map/MapCoordinates.hpp \
    src/engine/map/MapLoader.hpp \
    src/engine/map/MapSize.hpp \
    src/engine/map/RoadLocationCache.hpp \
    src/engine/map/TraversableLocationCache.hpp \
    src/engine/processing/AbstractProcessable.hpp \
    src/engine/processing/BuildingProcessor.hpp \
    src/engine/processing/CharacterProcessor.hpp \
    src/engine/processing/CycleDate.hpp \
    src/engine/processing/TimeCycleProcessor.hpp \
    src/engine/random.hpp \
    src/exceptions/BadConfigurationException.hpp \
    src/exceptions/EngineException.hpp \
    src/exceptions/Exception.hpp \
    src/exceptions/InvalidMapElementException.hpp \
    src/exceptions/NotImplementedException.hpp \
    src/exceptions/OutOfRangeException.hpp \
    src/exceptions/UnexpectedException.hpp \
    src/global/conf/BehaviorInformation.hpp \
    src/global/conf/BuildingAreaPartDescription.hpp \
    src/global/conf/BuildingInformation.hpp \
    src/global/conf/BuildingSearchCriteriaDescription.hpp \
    src/global/conf/CharacterInformation.hpp \
    src/global/conf/Conf.hpp \
    src/global/conf/ControlPanelElementInformation.hpp \
    src/global/conf/ItemInformation.hpp \
    src/global/conf/NatureElementInformation.hpp \
    src/global/yamlLibraryEnhancement.hpp \
    src/ui/controlPanel/BuildingButton.hpp \
    src/ui/controlPanel/ControlPanel.hpp \
    src/ui/InformationWidget.hpp \
    src/ui/MainWindow.hpp \
    src/viewer/DynamicElement.hpp \
    src/viewer/MapScene.hpp \
    src/viewer/MapViewer.hpp \
    src/viewer/SelectionElement.hpp \
    src/viewer/StaticElement.hpp \
    src/viewer/Tile.hpp \
    src/defines.hpp

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
