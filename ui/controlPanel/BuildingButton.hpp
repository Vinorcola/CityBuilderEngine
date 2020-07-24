#ifndef BUILDINGBUTTON_HPP
#define BUILDINGBUTTON_HPP

#include <QtWidgets/QPushButton>

class BuildingInformation;

class BuildingButton : public QPushButton
{
        Q_OBJECT

    private:
        const BuildingInformation* elementConf;

    public:
        BuildingButton(const BuildingInformation* elementConf);

        const BuildingInformation* getAssociatedBuilding() const;
};

#endif // BUILDINGBUTTON_HPP
