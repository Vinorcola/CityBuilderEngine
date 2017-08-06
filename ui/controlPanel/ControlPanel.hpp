#ifndef CONTROLPANEL_HPP
#define CONTROLPANEL_HPP

#include <QDockWidget>

#include "engine/map/Map.hpp"
#include "ui/controlPanel/BuildingButton.hpp"

class ControlPanel : public QDockWidget
{
        Q_OBJECT

    private:
        QList<BuildingButton*> buttonList;

    public:
        ControlPanel(const Conf* conf);

    private:
        BuildingButton* createButton(const StaticElementInformation* elementConf);

    signals:
        void buildingRequested(const StaticElementInformation* elementConf);
};

#endif // CONTROLPANEL_HPP
