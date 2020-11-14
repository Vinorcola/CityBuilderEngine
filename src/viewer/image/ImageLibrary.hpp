#ifndef IMAGELIBRARY_HPP
#define IMAGELIBRARY_HPP

#include <QtCore/QHash>
#include <QtGui/QBrush>

class BuildingImage;
class BuildingInformation;
class CharacterImage;
class CharacterInformation;
class Conf;
class NatureElementImage;
class NatureElementInformation;

/**
 * @brief A library that load all the images needed to display anything on the map.
 */
class ImageLibrary
{
        Q_DISABLE_COPY_MOVE(ImageLibrary)

    public:
        static const QBrush GREEN_BRUSH;
        static const QBrush ORANGE_BRUSH;
        static const QBrush RED_BRUSH;

    private:
        QHash<const BuildingInformation*, const BuildingImage*> buildingImages;
        QHash<const CharacterInformation*, const CharacterImage*> characterImages;
        QHash<const NatureElementInformation*, const NatureElementImage*> natureElementImages;

    public:
        ImageLibrary(const Conf& conf);

        ~ImageLibrary();

        const BuildingImage& getBuildingImage(const BuildingInformation& buildingConf) const;

        const CharacterImage& getCharacterImage(const CharacterInformation& characterConf) const;

        const NatureElementImage& getNatureElementImage(const NatureElementInformation& natureElementConf) const;
};

#endif // IMAGELIBRARY_HPP
