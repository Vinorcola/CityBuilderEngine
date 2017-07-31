#include "ControlPanel.hpp"

#include <QTabWidget>

#include "ui/controlPanel/BuildingPage.hpp"



ControlPanel::ControlPanel() :
    QDockWidget(),
    buttonList()
{
    // Dock configuration.
    setAllowedAreas(Qt::RightDockWidgetArea);
    setFeatures(QDockWidget::NoDockWidgetFeatures);

    // Content creation.
    QTabWidget* content(new QTabWidget);
    content->setTabPosition(QTabWidget::West);

    BuildingPage* buildingPage(new BuildingPage(*this));
    content->addTab(buildingPage, tr("Buildings"));

    setWidget(content);
}



BuildingButton* ControlPanel::createButton(const QString& text, StaticElementInformation::Type type)
{
    BuildingButton* currentButton(new BuildingButton(text, type));
    buttonList.append(currentButton);
    connect(currentButton, &BuildingButton::clicked, [this, currentButton]() {
        emit buildingRequested(currentButton->getAssociatedType());
    });

    return currentButton;
}
