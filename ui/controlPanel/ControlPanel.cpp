#include "ControlPanel.hpp"

#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>



ControlPanel::ControlPanel(const Conf* conf) :
    QDockWidget(),
    buttonList()
{
    // Dock configuration.
    setAllowedAreas(Qt::RightDockWidgetArea);
    setFeatures(QDockWidget::NoDockWidgetFeatures);

    // Content creation.
    auto content(new QTabWidget);
    content->setTabPosition(QTabWidget::West);

    // TODO: Automate with conf.
    auto page(new QWidget);
    auto pageLayout(new QVBoxLayout);
    pageLayout->addWidget(createButton(conf->getStaticElementConf("maintenance")));
    pageLayout->addWidget(createButton(conf->getStaticElementConf("house")));
    pageLayout->addWidget(createButton(conf->getStaticElementConf("road")));
    pageLayout->addStretch();
    page->setLayout(pageLayout);
    content->addTab(page, "Buildings");

    setWidget(content);
}



BuildingButton* ControlPanel::createButton(const StaticElementInformation* elementConf)
{
    BuildingButton* currentButton(new BuildingButton(elementConf));
    buttonList.append(currentButton);
    connect(currentButton, &BuildingButton::clicked, [this, currentButton]() {
        emit buildingRequested(currentButton->getAssociatedBuilding());
    });

    return currentButton;
}
