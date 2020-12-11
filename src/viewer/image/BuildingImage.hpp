#ifndef BUILDINGIMAGE_HPP
#define BUILDINGIMAGE_HPP

#include <QtCore/QHash>

#include "src/global/Direction.hpp"
#include "src/defines.hpp"

class BuildingAreaPartImage;
class BuildingInformation;
class QBrush;

/**
 * @brief Handles all the images required to display a building.
 */
class BuildingImage
{
        Q_DISABLE_COPY_MOVE(BuildingImage)

    private:
        QHash<Direction, QList<owner<const BuildingAreaPartImage*>>> areaParts;

    public:
        BuildingImage(const BuildingInformation& buildingConf, const QBrush& constructionBrush);

        const BuildingAreaPartImage& getAreaPartImage(Direction orientation, int areaIndex) const;
};

#endif // BUILDINGIMAGE_HPP
