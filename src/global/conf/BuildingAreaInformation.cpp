#include "BuildingAreaInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "src/global/conf/ImageSequenceInformation.hpp"
#include "src/global/conf/ModelReader.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"



BuildingAreaInformation::Graphics::~Graphics()
{
    qDeleteAll(activeAnimation);
}



BuildingAreaInformation::AreaPart::AreaPart(
    const QPoint& position,
    const MapSize& size,
    const QString& graphicsBasePath,
    YAML::Node imageNode,
    BuildingAreaInformation::Type type,
    int altitude
) :
    position(position),
    size(size),
    type(type),
    altitude(altitude),
    graphics()
{
    graphics.mainImagePath = graphicsBasePath + imageNode["file"].as<QString>();
    if (imageNode["animation"]) {
        QString animationPath(graphicsBasePath + "animation/");
        for (auto animationImageNode : imageNode["animation"]) {
            graphics.activeAnimation.append(new ImageSequenceInformation(
                animationPath + animationImageNode["file"].as<QString>(),
                animationImageNode["position"].as<QPoint>()
            ));
        }
    }
}



BuildingAreaInformation::BuildingAreaInformation(const ModelReader& model) :
    area()
{
    QString graphicsBasePath("assets/img/static/building/" + model.getKey() + "/");
    QString graphicsManifestPath(graphicsBasePath + "manifest.yaml");
    YAML::Node graphicsManifestRootNode(YAML::LoadFile(graphicsManifestPath.toStdString()));

    if (model.has("size")) {
        // This is a simple squared building.
        QList<const AreaPart*> areaParts;
        areaParts.append(new AreaPart(
            {0, 0},
            MapSize(model.getInt("size")),
            graphicsBasePath,
            graphicsManifestRootNode["building"]
        ));
        area.insert(Direction::West, areaParts);
    }
    else {
        auto node = model.getNode();
        if (node["area"].IsSequence()) {
            // This is a composed squared building.
            QList<const AreaPart*> areaParts;
            for (auto partModel : node["area"]) {
                auto index(areaParts.length());
                areaParts.append(new AreaPart(
                    partModel["position"].as<QPoint>(),
                    MapSize(partModel["size"].as<int>()),
                    graphicsBasePath,
                    graphicsManifestRootNode["building"][index]
                ));
            }
            area.insert(Direction::West, areaParts);
        }
        else {
            // This is a composed area.
            for (auto orientation : node["area"]) {
                auto orientationKey(orientation.first.as<QString>());
                QList<const AreaPart*> areaParts;
                for (auto partModel : orientation.second) {
                    auto index(areaParts.length());
                    areaParts.append(new AreaPart(
                        partModel["position"].as<QPoint>(),
                        MapSize(partModel["size"].as<int>()),
                        graphicsBasePath,
                        graphicsManifestRootNode["building"][orientationKey][index]
                    ));
                }
                area.insert(resolveDirection(orientationKey), areaParts);
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



QList<Direction> BuildingAreaInformation::getAvailableOrientations() const
{
    return area.keys();
}



QList<const BuildingAreaInformation::AreaPart*> BuildingAreaInformation::getAreaParts(Direction orientation) const
{
    return area.value(orientation);
}



const MapSize& BuildingAreaInformation::getSize() const
{
    return area.value(Direction::West).first()->size;
}
