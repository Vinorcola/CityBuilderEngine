#include "ControlPanel.hpp"

#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>

#include "src/global/conf/Conf.hpp"
#include "src/global/conf/ControlPanelElementInformation.hpp"
#include "src/ui/controlPanel/BuildingButton.hpp"



ControlPanel::ControlPanel(const Conf* conf) :
    QDockWidget(),
    buttonList()
{
    // Dock configuration.
    setAllowedAreas(Qt::RightDockWidgetArea);
    setFeatures(QDockWidget::NoDockWidgetFeatures);

    // Content creation.
    auto content(new QWidget);
    auto contentLayout(new QVBoxLayout);
    content->setLayout(contentLayout);

    auto nestedContent(new QTabWidget);
    nestedContent->setTabPosition(QTabWidget::West);
    contentLayout->addWidget(nestedContent);

    // Load control panel elements.
    for (auto element : conf->getControlPanelElements()) {
        switch (element->getType()) {
            case ControlPanelElementInformation::Type::Button:
                contentLayout->addWidget(createButton(element));
                break;

            case ControlPanelElementInformation::Type::Panel: {
                auto page(new QWidget);
                auto pageLayout(new QVBoxLayout);
                page->setLayout(pageLayout);
                for (auto nestedElement : element->getChildren()) {
                    if (nestedElement->getType() == ControlPanelElementInformation::Type::Button) {
                        pageLayout->addWidget(createButton(nestedElement));
                    }
                }
                pageLayout->addStretch();
                nestedContent->addTab(page, element->getTitle());
                break;
            }
        }
    }
    contentLayout->addStretch();

    setWidget(content);
}



BuildingButton* ControlPanel::createButton(const ControlPanelElementInformation* elementConf)
{
    BuildingButton* currentButton(new BuildingButton(elementConf->getStaticElementConf()));
    buttonList.append(currentButton);
    connect(currentButton, &BuildingButton::clicked, [this, currentButton]() {
        emit buildingRequested(currentButton->getAssociatedBuilding());
    });

    return currentButton;
}
