
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
    src/engine/element/dynamic/character/Character.cpp \
    src/engine/element/dynamic/character/DeliveryManCharacter.cpp \
    src/engine/element/dynamic/character/ImmigrantCharacter.cpp \
    src/engine/element/dynamic/character/MinerCharacter.cpp \
    src/engine/element/dynamic/character/StudentCharacter.cpp \
    src/engine/element/dynamic/character/WanderingCharacter.cpp \
    src/engine/element/dynamic/DynamicElementHandler.cpp \
    src/engine/element/dynamic/MotionHandler.cpp \
    src/engine/element/static/building/AbstractBuilding.cpp \
    src/engine/element/static/building/AbstractProcessableBuilding.cpp \
    src/engine/element/static/building/BuildingSearchEngine.cpp \
    src/engine/element/static/building/CivilianEntryPoint.cpp \
    src/engine/element/static/building/FarmBuilding.cpp \
    src/engine/element/static/building/HouseBuilding.cpp \
    src/engine/element/static/building/LaboratoryBuilding.cpp \
    src/engine/element/static/building/ProducerBuilding.cpp \
    src/engine/element/static/building/Road.cpp \
    src/engine/element/static/building/SanityBuilding.cpp \
    src/engine/element/static/building/SchoolBuilding.cpp \
    src/engine/element/static/building/StorageBuilding.cpp \
    src/engine/element/static/natureElement/NatureElement.cpp \
    src/engine/element/static/natureElement/NatureElementSearchEngine.cpp \
    src/engine/element/static/path/closestPath/ClosestPathFinder.cpp \
    src/engine/element/static/path/closestPath/PathNode.cpp \
    src/engine/element/static/path/closestPath/ProcessedPathNodeList.cpp \
    src/engine/element/static/path/closestPath/UnprocessedPathNodeList.cpp \
    src/engine/element/static/path/shortestPath/AStarNode.cpp \
    src/engine/element/static/path/shortestPath/ProcessedAStarNodeList.cpp \
    src/engine/element/static/path/shortestPath/ShortestPathFinder.cpp \
    src/engine/element/static/path/shortestPath/UnprocessedAStarNodeList.cpp \
    src/engine/element/static/path/PathGenerator.cpp \
    src/engine/element/static/path/RandomRoadPath.cpp \
    src/engine/element/static/path/TargetedPath.cpp \
    src/engine/element/static/StaticElementHandler.cpp \
    src/engine/loader/CityLoader.cpp \
    src/engine/map/Map.cpp \
    src/engine/map/MapArea.cpp \
    src/engine/map/MapCoordinates.cpp \
    src/engine/map/MapSize.cpp \
    src/engine/processing/AbstractProcessable.cpp \
    src/engine/processing/BuildingProcessor.cpp \
    src/engine/processing/CharacterProcessor.cpp \
    src/engine/processing/CycleDate.cpp \
    src/engine/processing/TimeCycleProcessor.cpp \
    src/exceptions/BadConfigurationException.cpp \
    src/exceptions/EngineException.cpp \
    src/exceptions/Exception.cpp \
    src/exceptions/FileNotFoundException.cpp \
    src/exceptions/InvalidMapElementException.cpp \
    src/exceptions/NotImplementedException.cpp \
    src/exceptions/OutOfRangeException.cpp \
    src/exceptions/UnexpectedException.cpp \
    src/global/conf/BuildingAreaPartDescription.cpp \
    src/global/conf/BuildingInformation.cpp \
    src/global/conf/CharacterInformation.cpp \
    src/global/conf/Conf.cpp \
    src/global/conf/ControlPanelElementInformation.cpp \
    src/global/conf/ImageSequenceInformation.cpp \
    src/global/conf/ItemInformation.cpp \
    src/global/conf/ModelReader.cpp \
    src/global/conf/NatureElementInformation.cpp \
    src/global/reference/collection/ReferenceCollection.cpp \
    src/global/reference/OptionalReference.cpp \
    src/global/reference/Referencable.cpp \
    src/global/reference/Reference.cpp \
    src/global/Direction.cpp \
    src/ui/controlPanel/BuildingButton.cpp \
    src/ui/controlPanel/ControlPanel.cpp \
    src/ui/InformationWidget.cpp \
    src/ui/MainWindow.cpp \
    src/viewer/construction/ConstructionCursor.cpp \
    src/viewer/element/graphics/DynamicElement.cpp \
    src/viewer/element/graphics/StaticElement.cpp \
    src/viewer/element/BuildingView.cpp \
    src/viewer/element/CharacterView.cpp \
    src/viewer/image/BuildingImage.cpp \
    src/viewer/image/CharacterImage.cpp \
    src/viewer/image/Image.cpp \
    src/viewer/image/ImageLibrary.cpp \
    src/viewer/image/ImageSequence.cpp \
    src/viewer/image/NatureElementImage.cpp \
    src/viewer/MapScene.cpp \
    src/viewer/Positioning.cpp \
    src/viewer/Tile.cpp \
    src/main.cpp

HEADERS += \
    src/engine/Engine.hpp \
    src/engine/city/City.hpp \
    src/engine/city/PopulationHandler.hpp \
    src/engine/city/PopulationRegistryInterface.hpp \
    src/engine/element/dynamic/character/Character.hpp \
    src/engine/element/dynamic/character/DeliveryManCharacter.hpp \
    src/engine/element/dynamic/character/ImmigrantCharacter.hpp \
    src/engine/element/dynamic/character/MinerCharacter.hpp \
    src/engine/element/dynamic/character/StudentCharacter.hpp \
    src/engine/element/dynamic/character/WanderingCharacter.hpp \
    src/engine/element/dynamic/CharacterFactoryInterface.hpp \
    src/engine/element/dynamic/CharacterManagerInterface.hpp \
    src/engine/element/dynamic/DynamicElementHandler.hpp \
    src/engine/element/dynamic/MotionHandler.hpp \
    src/engine/element/dynamic/PathGeneratorInterface.hpp \
    src/engine/element/static/building/AbstractBuilding.hpp \
    src/engine/element/static/building/AbstractProcessableBuilding.hpp \
    src/engine/element/static/building/BuildingSearchEngine.hpp \
    src/engine/element/static/building/CivilianEntryPoint.hpp \
    src/engine/element/static/building/FarmBuilding.hpp \
    src/engine/element/static/building/HouseBuilding.hpp \
    src/engine/element/static/building/ImmigrantGeneratorInterface.hpp \
    src/engine/element/static/building/LaboratoryBuilding.hpp \
    src/engine/element/static/building/ProducerBuilding.hpp \
    src/engine/element/static/building/Road.hpp \
    src/engine/element/static/building/SanityBuilding.hpp \
    src/engine/element/static/building/SchoolBuilding.hpp \
    src/engine/element/static/building/StorageBuilding.hpp \
    src/engine/element/static/natureElement/NatureElement.hpp \
    src/engine/element/static/natureElement/NatureElementSearchEngine.hpp \
    src/engine/element/static/path/closestPath/ClosestPathFinder.hpp \
    src/engine/element/static/path/closestPath/PathNode.hpp \
    src/engine/element/static/path/closestPath/ProcessedPathNodeList.hpp \
    src/engine/element/static/path/closestPath/UnprocessedPathNodeList.hpp \
    src/engine/element/static/path/shortestPath/AStarNode.hpp \
    src/engine/element/static/path/shortestPath/ProcessedAStarNodeList.hpp \
    src/engine/element/static/path/shortestPath/ShortestPathFinder.hpp \
    src/engine/element/static/path/shortestPath/UnprocessedAStarNodeList.hpp \
    src/engine/element/static/path/MapDetailsInterface.hpp \
    src/engine/element/static/path/PathGenerator.hpp \
    src/engine/element/static/path/PathInterface.hpp \
    src/engine/element/static/path/RandomRoadPath.hpp \
    src/engine/element/static/path/TargetedPath.hpp \
    src/engine/element/static/BuildingFactoryInterface.hpp \
    src/engine/element/static/StaticElementHandler.hpp \
    src/engine/loader/CityLoader.hpp \
    src/engine/map/Map.hpp \
    src/engine/map/MapArea.hpp \
    src/engine/map/MapCoordinates.hpp \
    src/engine/map/MapSize.hpp \
    src/engine/processing/AbstractProcessable.hpp \
    src/engine/processing/BuildingProcessor.hpp \
    src/engine/processing/CharacterProcessor.hpp \
    src/engine/processing/CycleDate.hpp \
    src/engine/processing/TimeCycleProcessor.hpp \
    src/engine/state/BuildingState.hpp \
    src/engine/state/CharacterState.hpp \
    src/engine/state/CityState.hpp \
    src/engine/state/MapState.hpp \
    src/engine/state/NatureElementState.hpp \
    src/engine/state/State.hpp \
    src/exceptions/BadConfigurationException.hpp \
    src/exceptions/EngineException.hpp \
    src/exceptions/Exception.hpp \
    src/exceptions/FileNotFoundException.hpp \
    src/exceptions/InvalidMapElementException.hpp \
    src/exceptions/NotImplementedException.hpp \
    src/exceptions/OutOfRangeException.hpp \
    src/exceptions/UnexpectedException.hpp \
    src/global/conf/BuildingAreaPartDescription.hpp \
    src/global/conf/BuildingInformation.hpp \
    src/global/conf/CharacterInformation.hpp \
    src/global/conf/Conf.hpp \
    src/global/conf/ControlPanelElementInformation.hpp \
    src/global/conf/ImageSequenceInformation.hpp \
    src/global/conf/ItemInformation.hpp \
    src/global/conf/ModelReader.hpp \
    src/global/conf/NatureElementInformation.hpp \
    src/global/reference/collection/ReferenceCollection.hpp \
    src/global/reference/OptionalReference.hpp \
    src/global/reference/Referencable.hpp \
    src/global/reference/Reference.hpp \
    src/global/Direction.hpp \
    src/global/yamlLibraryEnhancement.hpp \
    src/ui/controlPanel/BuildingButton.hpp \
    src/ui/controlPanel/ControlPanel.hpp \
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
    src/viewer/image/BuildingImage.hpp \
    src/viewer/image/CharacterImage.hpp \
    src/viewer/image/Image.hpp \
    src/viewer/image/ImageLibrary.hpp \
    src/viewer/image/ImageSequence.hpp \
    src/viewer/image/NatureElementImage.hpp \
    src/viewer/MapScene.hpp \
    src/viewer/Positioning.hpp \
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
