#ifndef BUILDINGBUTTON_HPP
#define BUILDINGBUTTON_HPP

#include <QPushButton>

#include "engine/map/Map.hpp"

class BuildingButton : public QPushButton
{
        Q_OBJECT

    private:
        const StaticElementInformation* elementConf;

    public:
        BuildingButton(const StaticElementInformation* elementConf);

        const StaticElementInformation* getAssociatedBuilding() const;
};

#endif // BUILDINGBUTTON_HPP
