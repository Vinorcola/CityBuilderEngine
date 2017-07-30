#include "BuildingButton.hpp"



BuildingButton::BuildingButton(const QString& text, AbstractStaticMapElement::Type type) :
    QPushButton(text),
    type(type)
{

}



AbstractStaticMapElement::Type BuildingButton::getAssociatedType() const
{
    return type;
}
