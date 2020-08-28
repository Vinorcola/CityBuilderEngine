#include "CharacterInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "src/exceptions/BadConfigurationException.hpp"
#include "src/global/conf/ModelReader.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"
#include "src/defines.hpp"

CharacterInformation::CharacterInformation(QObject* parent, const ModelReader& model) :
    QObject(parent),
    key(model.getKey()),
    title(model.getString("title")),
#ifdef SLOW_MOTION
    speed(model.getReal("speed") / CYCLE_PER_SECOND / 8.0),
#else
    speed(model.getReal("speed") / CYCLE_PER_SECOND),
#endif
    wanderingCredits(model.getOptionalInt("wanderingCredits", 0)),
    image("assets/img/dynamic/character/" + key + ".png")
{

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



const QPixmap& CharacterInformation::getImage() const
{
    return image;
}



void CharacterInformation::checkModel(const QString& key, const YAML::Node& model)
{
    if (!model["type"]) {
        throw BadConfigurationException("Missing \"type\" parameter in configuration for node \"" + key + "\".");
    }
}
