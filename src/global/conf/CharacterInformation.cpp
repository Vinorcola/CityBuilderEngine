#include "CharacterInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "src/exceptions/BadConfigurationException.hpp"
#include "src/global/conf/ImageSequenceInformation.hpp"
#include "src/global/conf/ModelReader.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"
#include "src/defines.hpp"



CharacterInformation::Graphics::~Graphics()
{
    for (auto animation : animations) {
        for (auto orientedAnimation : animation) {
            qDeleteAll(orientedAnimation);
        }
    }
}



CharacterInformation::CharacterInformation(const QString& configDirectoryPath, const ModelReader& model) :
    key(model.getKey()),
    title(model.getString("title")),
#ifdef SLOW_MOTION
    speed(model.getReal("speed") / CYCLES_PER_SECOND / 8.0),
#else
    speed(model.getReal("speed") / CYCLES_PER_SECOND),
#endif
    wanderingCredits(model.getOptionalInt("wanderingCredits", 0)),
    actionInterval(model.getOptionalInt("actionInterval", 0) * CYCLES_PER_SECOND),
    graphics()
{
    QString basePath(configDirectoryPath + "/images/dynamic/character/" + key + "/");
    QString manifestPath(basePath + "manifest.yaml");
    YAML::Node manifestRoot(YAML::LoadFile(manifestPath.toStdString()));

    if (manifestRoot["character"]["east"]) {
        // Config node as direction property, so there is only the walking animation.
        OrientedAnimation animation;
        for (auto node : manifestRoot["character"]) {
            auto direction(resolveDirection(node.first.as<QString>()));
            QList<const ImageSequenceInformation*> images;
            for (auto imageNode : node.second) {
                images.append(new ImageSequenceInformation(
                    basePath + imageNode["file"].as<QString>(),
                    imageNode["position"].as<QPoint>()
                ));
            }
            animation.insert(direction, images);
        }
        graphics.animations.insert(CharacterStatus::Walking, animation);
    }
    else {
        for (auto statusNode : manifestRoot["character"]) {
            auto status(resolveCharacterStatus(statusNode.first.as<QString>()));
            OrientedAnimation animation;
            for (auto node : statusNode.second) {
                auto direction(resolveDirection(node.first.as<QString>()));
                QList<const ImageSequenceInformation*> images;
                for (auto imageNode : node.second) {
                    images.append(new ImageSequenceInformation(
                        basePath + imageNode["file"].as<QString>(),
                        imageNode["position"].as<QPoint>()
                    ));
                }
                animation.insert(direction, images);
            }
            graphics.animations.insert(status, animation);
        }
    }
}



const QString& CharacterInformation::getKey() const
{
    return key;
}



const QString& CharacterInformation::getTitle() const
{
    return title;
}



qreal CharacterInformation::getSpeed() const
{
    return speed;
}



int CharacterInformation::getWanderingCredits() const
{
    return wanderingCredits;
}



int CharacterInformation::getActionInterval() const
{
    return actionInterval;
}



const CharacterInformation::Graphics& CharacterInformation::getGraphicsData() const
{
    return graphics;
}
