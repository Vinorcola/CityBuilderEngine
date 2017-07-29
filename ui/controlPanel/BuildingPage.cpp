#include "BuildingPage.hpp"

#include <QVBoxLayout>

#include "ui/controlPanel/BuildingButton.hpp"



BuildingPage::BuildingPage(ControlPanel& buttonCreator) :
    QWidget()
{
    QVBoxLayout* layout(new QVBoxLayout);

    layout->addWidget(buttonCreator.createButton(tr("Maintenance"), Map::StaticElementType::Maintenance));
    layout->addWidget(buttonCreator.createButton(tr("Road"), Map::StaticElementType::Road));

    layout->addStretch();
    setLayout(layout);
}
