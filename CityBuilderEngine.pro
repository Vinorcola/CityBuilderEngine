
QT += core gui widgets
CONFIG += c++14

TEMPLATE = app
TARGET = CityBuilderEngine
OBJECTS_DIR = objects
MOC_DIR = moc

SOURCES += \
    src/engine/Engine.cpp \
    src/engine/city/City.cpp \
    src/engine/city/PopulationHandler.cpp \
    src/engine/loader/CityLoader.cpp \
    src/engine/map/dynamicElement/character/Character.cpp \
    src/engine/map/dynamicElement/character/DeliveryManCharacter.cpp \
    src/engine/map/dynamicElement/character/ImmigrantCharacter.cpp \
    src/engine/map/dynamicElement/character/MinerCharacter.cpp \
    src/engine/map/dynamicElement/character/StudentCharacter.cpp \
    src/engine/map/dynamicElement/character/WanderingCharacter.cpp \
    src/engine/map/dynamicElement/DynamicElementFactory.cpp \
    src/engine/map/dynamicElement/DynamicElementRegistry.cpp \
    src/engine/map/dynamicElement/MotionHandler.cpp \
    src/engine/map/path/algorithm/PathFinder.cpp \
    src/engine/map/path/algorithm/RegisteredTileBag.cpp \
    src/engine/map/path/PathGenerator.cpp \
    src/engine/map/path/RandomRoadPath.cpp \
    src/engine/map/path/TargetedPath.cpp \
    src/engine/map/staticElement/building/behavior/WalkerGenerationBehavior.cpp \
    src/engine/map/staticElement/building/AbstractBuilding.cpp \
    src/engine/map/staticElement/building/AbstractProcessableBuilding.cpp \
    src/engine/map/staticElement/building/BuildingSearchEngine.cpp \
    src/engine/map/staticElement/building/CivilianEntryPoint.cpp \
    src/engine/map/staticElement/building/FarmBuilding.cpp \
    src/engine/map/staticElement/building/HouseBuilding.cpp \
    src/engine/map/staticElement/building/LaboratoryBuilding.cpp \
    src/engine/map/staticElement/building/ProducerBuilding.cpp \
    src/engine/map/staticElement/building/Road.cpp \
    src/engine/map/staticElement/building/SanityBuilding.cpp \
    src/engine/map/staticElement/building/SchoolBuilding.cpp \
    src/engine/map/staticElement/building/StorageBuilding.cpp \
    src/engine/map/staticElement/natureElement/NatureElement.cpp \
    src/engine/map/staticElement/natureElement/NatureElementSearchEngine.cpp \
    src/engine/map/staticElement/StaticElementFactory.cpp \
    src/engine/map/staticElement/StaticElementRegistry.cpp \
    src/engine/map/Map.cpp \
    src/engine/map/Tile.cpp \
    src/engine/processing/AbstractProcessable.cpp \
    src/engine/processing/CycleDate.cpp \
    src/engine/processing/TimeCycleProcessor.cpp \
    src/exceptions/BadConfigurationException.cpp \
    src/exceptions/EngineException.cpp \
    src/exceptions/Exception.cpp \
    src/exceptions/FileNotFoundException.cpp \
    src/exceptions/NotImplementedException.cpp \
    src/exceptions/OutOfRangeException.cpp \
    src/exceptions/UnexpectedException.cpp \
    src/global/conf/BuildingAreaInformation.cpp \
    src/global/conf/BuildingInformation.cpp \
    src/global/conf/CharacterInformation.cpp \
    src/global/conf/Conf.cpp \
    src/global/conf/ControlPanelElementInformation.cpp \
    src/global/conf/ImageSequenceInformation.cpp \
    src/global/conf/ItemInformation.cpp \
    src/global/conf/ModelReader.cpp \
    src/global/conf/NatureElementInformation.cpp \
    src/global/geometry/DynamicElementCoordinates.cpp \
    src/global/geometry/TileArea.cpp \
    src/global/geometry/TileAreaSize.cpp \
    src/global/geometry/TileCoordinates.cpp \
    src/global/BuildingStatus.cpp \
    src/global/Direction.cpp \
    src/ui/controlPanel/BuildingButton.cpp \
    src/ui/controlPanel/ControlPanel.cpp \
    src/ui/BuildingDetailsDialog.cpp \
    src/ui/InformationWidget.cpp \
    src/ui/MainWindow.cpp \
    src/viewer/construction/ConstructionCursor.cpp \
    src/viewer/element/graphics/DynamicElement.cpp \
    src/viewer/element/graphics/StaticElement.cpp \
    src/viewer/element/BuildingView.cpp \
    src/viewer/element/CharacterView.cpp \
    src/viewer/image/BuildingAreaPartImage.cpp \
    src/viewer/image/BuildingImage.cpp \
    src/viewer/image/CharacterImage.cpp \
    src/viewer/image/Image.cpp \
    src/viewer/image/ImageLibrary.cpp \
    src/viewer/image/ImageSequence.cpp \
    src/viewer/image/NatureElementImage.cpp \
    src/viewer/MapScene.cpp \
    src/viewer/Positioning.cpp \
    src/viewer/TileView.cpp \
    src/main.cpp

HEADERS += \
    src/engine/Engine.hpp \
    src/engine/city/City.hpp \
    src/engine/city/PopulationHandler.hpp \
    src/engine/city/PopulationRegistryInterface.hpp \
    src/engine/city/WorkingPlaceRegistryInterface.hpp \
    src/engine/loader/CityLoader.hpp \
    src/engine/map/dynamicElement/character/Character.hpp \
    src/engine/map/dynamicElement/character/DeliveryManCharacter.hpp \
    src/engine/map/dynamicElement/character/ImmigrantCharacter.hpp \
    src/engine/map/dynamicElement/character/MinerCharacter.hpp \
    src/engine/map/dynamicElement/character/StudentCharacter.hpp \
    src/engine/map/dynamicElement/character/WanderingCharacter.hpp \
    src/engine/map/dynamicElement/CharacterDisposerInterface.hpp \
    src/engine/map/dynamicElement/CharacterGeneratorInterface.hpp \
    src/engine/map/dynamicElement/DynamicElementFactory.hpp \
    src/engine/map/dynamicElement/DynamicElementRegistry.hpp \
    src/engine/map/dynamicElement/MotionHandler.hpp \
    src/engine/map/path/algorithm/PathFinder.hpp \
    src/engine/map/path/algorithm/RegisteredTileBag.hpp \
    src/engine/map/path/PathGenerator.hpp \
    src/engine/map/path/PathGeneratorInterface.hpp \
    src/engine/map/path/PathInterface.hpp \
    src/engine/map/path/RandomRoadPath.hpp \
    src/engine/map/path/TargetedPath.hpp \
    src/engine/map/staticElement/building/behavior/WalkerGenerationBehavior.hpp \
    src/engine/map/staticElement/building/AbstractBuilding.hpp \
    src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp \
    src/engine/map/staticElement/building/BuildingSearchEngine.hpp \
    src/engine/map/staticElement/building/CivilianEntryPoint.hpp \
    src/engine/map/staticElement/building/FarmBuilding.hpp \
    src/engine/map/staticElement/building/HouseBuilding.hpp \
    src/engine/map/staticElement/building/ImmigrantGeneratorInterface.hpp \
    src/engine/map/staticElement/building/LaboratoryBuilding.hpp \
    src/engine/map/staticElement/building/ProducerBuilding.hpp \
    src/engine/map/staticElement/building/Road.hpp \
    src/engine/map/staticElement/building/SanityBuilding.hpp \
    src/engine/map/staticElement/building/SchoolBuilding.hpp \
    src/engine/map/staticElement/building/StorageBuilding.hpp \
    src/engine/map/staticElement/natureElement/NatureElement.hpp \
    src/engine/map/staticElement/natureElement/NatureElementSearchEngine.hpp \
    src/engine/map/staticElement/StaticElementFactory.hpp \
    src/engine/map/staticElement/StaticElementRegistry.hpp \
    src/engine/map/Map.hpp \
    src/engine/map/Tile.hpp \
    src/engine/processing/AbstractProcessable.hpp \
    src/engine/processing/CycleDate.hpp \
    src/engine/processing/TimeCycleProcessor.hpp \
    src/exceptions/BadConfigurationException.hpp \
    src/exceptions/EngineException.hpp \
    src/exceptions/Exception.hpp \
    src/exceptions/FileNotFoundException.hpp \
    src/exceptions/NotImplementedException.hpp \
    src/exceptions/OutOfRangeException.hpp \
    src/exceptions/UnexpectedException.hpp \
    src/global/conf/BuildingAreaInformation.hpp \
    src/global/conf/BuildingInformation.hpp \
    src/global/conf/CharacterInformation.hpp \
    src/global/conf/Conf.hpp \
    src/global/conf/ControlPanelElementInformation.hpp \
    src/global/conf/ImageSequenceInformation.hpp \
    src/global/conf/ItemInformation.hpp \
    src/global/conf/ModelReader.hpp \
    src/global/conf/NatureElementInformation.hpp \
    src/global/geometry/DynamicElementCoordinates.hpp \
    src/global/geometry/GraphicalCoordinates.hpp \
    src/global/geometry/TileArea.hpp \
    src/global/geometry/TileAreaSize.hpp \
    src/global/geometry/TileCoordinates.hpp \
    src/global/pointer/SmartPointerUtils.hpp \
    src/global/state/BuildingState.hpp \
    src/global/state/CharacterState.hpp \
    src/global/state/CityState.hpp \
    src/global/state/MapState.hpp \
    src/global/state/NatureElementState.hpp \
    src/global/state/State.hpp \
    src/global/BuildingStatus.hpp \
    src/global/Direction.hpp \
    src/global/yamlLibraryEnhancement.hpp \
    src/ui/controlPanel/BuildingButton.hpp \
    src/ui/controlPanel/ControlPanel.hpp \
    src/ui/BuildingDetailsDialog.hpp \
    src/ui/DialogDisplayer.hpp \
    src/ui/InformationWidget.hpp \
    src/ui/MainWindow.hpp \
    src/viewer/construction/AreaCheckerInterface.hpp \
    src/viewer/construction/ConstructionCursor.hpp \
    src/viewer/construction/RoadPathGeneratorInterface.hpp \
    src/viewer/element/graphics/DynamicElement.hpp \
    src/viewer/element/graphics/StaticElement.hpp \
    src/viewer/element/BuildingView.hpp \
    src/viewer/element/CharacterView.hpp \
    src/viewer/element/TileLocatorInterface.hpp \
    src/viewer/image/BuildingAreaPartImage.hpp \
    src/viewer/image/BuildingImage.hpp \
    src/viewer/image/CharacterImage.hpp \
    src/viewer/image/Image.hpp \
    src/viewer/image/ImageLibrary.hpp \
    src/viewer/image/ImageSequence.hpp \
    src/viewer/image/NatureElementImage.hpp \
    src/viewer/MapScene.hpp \
    src/viewer/Positioning.hpp \
    src/viewer/TileView.hpp \
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
