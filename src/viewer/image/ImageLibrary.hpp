#ifndef IMAGELIBRARY_HPP
#define IMAGELIBRARY_HPP

#include <QtCore/QHash>

class BuildingImage;
class BuildingInformation;
class Conf;
class NatureElementImage;
class NatureElementInformation;

class ImageLibrary
{
    private:
        QHash<const BuildingInformation*, BuildingImage*> buildingImages;
        QHash<const NatureElementInformation*, NatureElementImage*> natureElementImages;

    public:
        ImageLibrary(const Conf& conf);

        ~ImageLibrary();

        BuildingImage& getBuildingImage(const BuildingInformation& buildingConf) const;

        NatureElementImage& getNatureElementImage(const NatureElementInformation& natureElementConf) const;
};

#endif // IMAGELIBRARY_HPP
