#include "BuildingButton.hpp"



BuildingButton::BuildingButton(const QString& text, StaticElementInformation::Type type) :
    QPushButton(text),
    type(type)
{

}



StaticElementInformation::Type BuildingButton::getAssociatedType() const
{
    return type;
}
