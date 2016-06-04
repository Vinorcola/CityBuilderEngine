#ifndef BUILDINGBUTTON_HPP
#define BUILDINGBUTTON_HPP

#include <QPushButton>

#include "engine/map/Map.hpp"





class BuildingButton : public QPushButton
{
        Q_OBJECT


    private:
        Map::StaticElementType type;



    public:
        BuildingButton(const QString& text, Map::StaticElementType type);



        Map::StaticElementType getAssociatedType() const;
};

#endif // BUILDINGBUTTON_HPP
