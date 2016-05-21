QT += core
QT -= gui

TARGET = CityBuilderEngine
CONFIG += console
CONFIG += c++14
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    engine/element/building/AbstractBuilding.cpp \
    engine/element/building/AbstractProcessableBuilding.cpp \
    engine/element/building/MaintenanceBuilding.cpp \
    engine/element/building/Road.cpp \
    engine/element/character/AbstractCharacter.cpp \
    engine/element/character/RandomWalker.cpp \
    engine/element/AbstractDynamicMapElement.cpp \
    engine/element/AbstractStaticMapElement.cpp \
    engine/map/Map.cpp \
    engine/map/MapArea.cpp \
    engine/map/MapCoordinates.cpp \
    engine/map/MapSize.cpp \
    engine/map/RoadGraph.cpp \
    engine/map/RoadGraphNode.cpp \
    engine/processing/AbstractProcessable.cpp \
    engine/processing/CycleDate.cpp \
    engine/processing/TimeCycleProcessor.cpp \
    exceptions/EngineException.cpp \
    exceptions/InvalidMapElementException.cpp \
    exceptions/OutOfRangeException.cpp \
    exceptions/UnexpectedException.cpp \
    main.cpp

HEADERS += \
    engine/element/building/AbstractBuilding.hpp \
    engine/element/building/AbstractProcessableBuilding.hpp \
    engine/element/building/MaintenanceBuilding.hpp \
    engine/element/building/Road.hpp \
    engine/element/character/AbstractCharacter.hpp \
    engine/element/character/RandomWalker.hpp \
    engine/element/AbstractDynamicMapElement.hpp \
    engine/element/AbstractStaticMapElement.hpp \
    engine/map/Map.hpp \
    engine/map/MapArea.hpp \
    engine/map/MapCoordinates.hpp \
    engine/map/MapSize.hpp \
    engine/map/RoadGraph.hpp \
    engine/map/RoadGraphNode.hpp \
    engine/processing/AbstractProcessable.hpp \
    engine/processing/CycleDate.hpp \
    engine/processing/TimeCycleProcessor.hpp \
    exceptions/EngineException.hpp \
    exceptions/InvalidMapElementException.hpp \
    exceptions/OutOfRangeException.hpp \
    exceptions/UnexpectedException.hpp

