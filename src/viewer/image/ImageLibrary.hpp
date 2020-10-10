#ifndef IMAGELIBRARY_HPP
#define IMAGELIBRARY_HPP

#include <QtCore/QHash>

class BuildingImage;
class BuildingInformation;
class CharacterImage;
class CharacterInformation;
class Conf;
class NatureElementImage;
class NatureElementInformation;

class ImageLibrary
{
    private:
        QHash<const BuildingInformation*, BuildingImage*> buildingImages;
        QHash<const CharacterInformation*, CharacterImage*> characterImages;
        QHash<const NatureElementInformation*, NatureElementImage*> natureElementImages;

    public:
        ImageLibrary(const Conf& conf);

        ~ImageLibrary();

        BuildingImage& getBuildingImage(const BuildingInformation& buildingConf) const;

        CharacterImage& getCharacterImage(const CharacterInformation& characterConf) const;

        NatureElementImage& getNatureElementImage(const NatureElementInformation& natureElementConf) const;
};

#endif // IMAGELIBRARY_HPP
