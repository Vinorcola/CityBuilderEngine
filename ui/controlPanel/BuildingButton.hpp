#ifndef BUILDINGBUTTON_HPP
#define BUILDINGBUTTON_HPP

#include <QPushButton>

#include "engine/map/Map.hpp"

class BuildingButton : public QPushButton
{
        Q_OBJECT

    private:
        AbstractStaticMapElement::Type type;

    public:
        BuildingButton(const QString& text, AbstractStaticMapElement::Type type);

        AbstractStaticMapElement::Type getAssociatedType() const;
};

#endif // BUILDINGBUTTON_HPP
