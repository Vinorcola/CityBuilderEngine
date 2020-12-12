#include "BuildingAreaInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "src/global/conf/ImageSequenceInformation.hpp"
#include "src/global/conf/ModelReader.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"



BuildingAreaInformation::Graphics::~Graphics()
{
    for (auto animation : animations) {
        qDeleteAll(animation);
    }
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
    if (imageNode["active"]) {
        AnimationImages animationImages;
        for (auto animationImageNode : imageNode["active"]) {
            animationImages.append(new ImageSequenceInformation(
                graphicsBasePath + animationImageNode["file"].as<QString>(),
                animationImageNode["position"].as<QPoint>()
            ));
        }
        graphics.animations.insert(BuildingStatus::Active, animationImages);
    }
    if (imageNode["working"]) {
        AnimationImages animationImages;
        for (auto animationImageNode : imageNode["working"]) {
            animationImages.append(new ImageSequenceInformation(
                graphicsBasePath + animationImageNode["file"].as<QString>(),
                animationImageNode["position"].as<QPoint>()
            ));
        }
        graphics.animations.insert(BuildingStatus::Working, animationImages);
    }
}



BuildingAreaInformation::BuildingAreaInformation(const QString& configDirectoryPath, const ModelReader& model) :
    sizes(),
    area()
{
    QString graphicsBasePath(configDirectoryPath + "/images/static/building/" + model.getKey() + "/");
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
        sizes.insert(Direction::West, MapSize(model.getInt("size")));
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
            sizes.insert(Direction::West, resolveSize(areaParts));
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
                sizes.insert(resolveDirection(orientationKey), resolveSize(areaParts));
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



MapSize BuildingAreaInformation::getSize(Direction orientation) const
{
    return sizes.value(orientation);
}



MapSize BuildingAreaInformation::resolveSize(const QList<const BuildingAreaInformation::AreaPart*>& areaParts)
{
    int maxX(0);
    int maxY(0);

    for (auto areaPart : areaParts) {
        int x(areaPart->position.x() + areaPart->size.getWidth());
        if (x > maxX) {
            maxX = x;
        }
        int y(areaPart->position.y() + areaPart->size.getHeight());
        if (y > maxY) {
            maxY = y;
        }
    }

    return MapSize(maxX, maxY);
}
