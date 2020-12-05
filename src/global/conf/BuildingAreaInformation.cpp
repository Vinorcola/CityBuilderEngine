#include "BuildingAreaInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "src/global/conf/ModelReader.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"



BuildingAreaInformation::AreaPart::AreaPart(
    const MapCoordinates& position,
    const MapSize& size,
    BuildingAreaInformation::Type type,
    int altitude
) :
    position(position),
    size(size),
    type(type),
    altitude(altitude)
{

}



BuildingAreaInformation::BuildingAreaInformation(const ModelReader& model) :
    area()
{
    if (model.has("size")) {
        // This is a simple squared building.
        QList<AreaPart*> areaParts;
        areaParts.append(new AreaPart(
            {0, 0},
            MapSize(model.getInt("size"))
        ));
        area.insert(Direction::West, areaParts);
    }
    else {
        auto node = model.getNode();
        if (node["area"].IsSequence()) {
            // This is a composed squared building.
            QList<AreaPart*> areaParts;
            for (auto partModel : node["area"]) {
                areaParts.append(new AreaPart(
                    partModel["position"].as<MapCoordinates>(),
                    MapSize(partModel["size"].as<int>())
                ));
            }
            area.insert(Direction::West, areaParts);
        }
        else {
            // This is a composed area.
            for (auto orientation : node["area"]) {
                QList<AreaPart*> areaParts;
                for (auto partModel : orientation.second) {
                    areaParts.append(new AreaPart(
                        partModel["position"].as<MapCoordinates>(),
                        MapSize(partModel["size"].as<int>())
                    ));
                }
                area.insert(resolveDirection(orientation.first.as<QString>()), areaParts);
            }
        }
    }
}



BuildingAreaInformation::~BuildingAreaInformation()
{
    for (auto& areaParts : area) {
        qDeleteAll(areaParts);
    }
}



const MapSize& BuildingAreaInformation::getSize() const
{
    return area.value(Direction::West).first()->size;
}
