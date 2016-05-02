QT += core
QT -= gui

TARGET = CityBuilderEngine
CONFIG += console
CONFIG += c++14
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    engine/buildings/AbstractBuilding.cpp \
    engine/buildings/MaintenanceBuilding.cpp \
    engine/characters/AbstractCharacter.cpp \
    engine/characters/RandomlyWalker.cpp \
    engine/Map.cpp \
    engine/Processable.cpp \
    engine/RoadGraphNode.cpp \
    exceptions/EngineException.cpp \
    exceptions/InvalidMapElementException.cpp \
    exceptions/OutOfRangeException.cpp \
    global/MapElement.cpp \
    main.cpp

HEADERS += \
    engine/buildings/AbstractBuilding.hpp \
    engine/buildings/MaintenanceBuilding.hpp \
    engine/characters/AbstractCharacter.hpp \
    engine/characters/RandomlyWalker.hpp \
    engine/Map.hpp \
    engine/Processable.hpp \
    engine/RoadGraphNode.hpp \
    exceptions/EngineException.hpp \
    exceptions/InvalidMapElementException.hpp \
    exceptions/OutOfRangeException.hpp \
    global/MapElement.hpp

