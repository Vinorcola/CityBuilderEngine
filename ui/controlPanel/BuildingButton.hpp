#ifndef BUILDINGBUTTON_HPP
#define BUILDINGBUTTON_HPP

#include <QPushButton>

#include "engine/map/Map.hpp"

class BuildingButton : public QPushButton
{
        Q_OBJECT

    private:
        StaticElementInformation::Type type;

    public:
        BuildingButton(const QString& text, StaticElementInformation::Type type);

        StaticElementInformation::Type getAssociatedType() const;
};

#endif // BUILDINGBUTTON_HPP
