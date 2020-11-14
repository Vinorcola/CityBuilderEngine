#ifndef CONTROLPANEL_HPP
#define CONTROLPANEL_HPP

#include <QtCore/QList>
#include <QtWidgets/QDockWidget>

class BuildingButton;
class BuildingInformation;
class Conf;
class ControlPanelElementInformation;

class ControlPanel : public QDockWidget
{
        Q_OBJECT

    private:
        QList<BuildingButton*> buttonList;

    public:
        ControlPanel(const Conf* conf);

    private:
        BuildingButton* createButton(const ControlPanelElementInformation& elementConf);

    signals:
        void buildingRequested(const BuildingInformation& elementConf);
};

#endif // CONTROLPANEL_HPP
