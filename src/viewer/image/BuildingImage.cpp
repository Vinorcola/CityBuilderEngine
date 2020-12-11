#include "BuildingImage.hpp"

#include "src/global/conf/BuildingInformation.hpp"
#include "src/viewer/image/BuildingAreaPartImage.hpp"



BuildingImage::BuildingImage(const BuildingInformation& buildingConf, const QBrush& constructionBrush) :
    areaParts()
{
    for (auto orientation : buildingConf.getAvailableOrientations()) {
        QList<const BuildingAreaPartImage*> areaParts;
        for (auto areaPartConf : buildingConf.getAreaParts(orientation)) {
            areaParts.append(new BuildingAreaPartImage(areaPartConf->graphics, constructionBrush));
        }
        this->areaParts.insert(orientation, areaParts);
    }
}



const BuildingAreaPartImage& BuildingImage::getAreaPartImage(Direction orientation, int areaIndex) const
{
    return *areaParts.value(orientation).at(areaIndex);
}
