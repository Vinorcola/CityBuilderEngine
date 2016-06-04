#include "BuildingButton.hpp"





BuildingButton::BuildingButton(const QString& text, Map::StaticElementType type) :
    QPushButton(text),
    type(type)
{
    setCheckable(true);
}





Map::StaticElementType BuildingButton::getAssociatedType() const
{
    return type;
}
