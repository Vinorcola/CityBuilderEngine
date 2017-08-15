#ifndef BUILDINGBUTTON_HPP
#define BUILDINGBUTTON_HPP

#include <QtWidgets/QPushButton>

class StaticElementInformation;

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
