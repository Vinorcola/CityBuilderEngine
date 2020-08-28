
QT += core testlib
QT -= gui

TARGET = MapCoordinatesTest
CONFIG += c++14 qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../..

SOURCES += \
    ../../../../src/engine/map/MapCoordinates.cpp \
    ../../../../src/exceptions/EngineException.cpp \
    ../../../../src/exceptions/Exception.cpp \
    ../../../../src/exceptions/UnexpectedException.cpp \
    MapCoordinatesTest.cpp
