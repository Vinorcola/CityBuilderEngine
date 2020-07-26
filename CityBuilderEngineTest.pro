
QT += core testlib
QT -= gui

TARGET = CityBuilderEngineTest
CONFIG += c++14 qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += tests/engine/map/MapCoordinatesTest.cpp
