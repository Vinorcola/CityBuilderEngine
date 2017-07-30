#include "BuildingPage.hpp"

#include <QVBoxLayout>

#include "ui/controlPanel/BuildingButton.hpp"



BuildingPage::BuildingPage(ControlPanel& buttonCreator) :
    QWidget()
{
    QVBoxLayout* layout(new QVBoxLayout);

    layout->addWidget(buttonCreator.createButton(tr("Maintenance"), AbstractStaticMapElement::Type::Maintenance));
    layout->addWidget(buttonCreator.createButton(tr("House"), AbstractStaticMapElement::Type::House));
    layout->addWidget(buttonCreator.createButton(tr("Road"), AbstractStaticMapElement::Type::Road));

    layout->addStretch();
    setLayout(layout);
}
