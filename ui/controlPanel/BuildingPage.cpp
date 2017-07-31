#include "BuildingPage.hpp"

#include <QVBoxLayout>

#include "ui/controlPanel/BuildingButton.hpp"



BuildingPage::BuildingPage(ControlPanel& buttonCreator) :
    QWidget()
{
    QVBoxLayout* layout(new QVBoxLayout);

    layout->addWidget(buttonCreator.createButton(tr("Maintenance"), StaticElementInformation::Type::Maintenance));
    layout->addWidget(buttonCreator.createButton(tr("House"), StaticElementInformation::Type::House));
    layout->addWidget(buttonCreator.createButton(tr("Road"), StaticElementInformation::Type::Road));

    layout->addStretch();
    setLayout(layout);
}
