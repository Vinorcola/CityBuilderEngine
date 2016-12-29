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
        ControlPanel();



        BuildingButton* createButton(const QString& text, Map::StaticElementType type);



    signals:
        void buildingRequested(Map::StaticElementType type);
};

#endif // CONTROLPANEL_HPP
