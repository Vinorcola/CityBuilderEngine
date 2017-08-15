#ifndef CONTROLPANEL_HPP
#define CONTROLPANEL_HPP

#include <QtCore/QList>
#include <QtWidgets/QDockWidget>

class BuildingButton;
class Conf;
class ControlPanelElementInformation;
class StaticElementInformation;

class ControlPanel : public QDockWidget
{
        Q_OBJECT

    private:
        QList<BuildingButton*> buttonList;

    public:
        ControlPanel(const Conf* conf);

    private:
        BuildingButton* createButton(const ControlPanelElementInformation* elementConf);

    signals:
        void buildingRequested(const StaticElementInformation* elementConf);
};

#endif // CONTROLPANEL_HPP
