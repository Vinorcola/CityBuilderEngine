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

        BuildingButton* createButton(const QString& text, AbstractStaticMapElement::Type type);

    signals:
        void buildingRequested(AbstractStaticMapElement::Type type);
};

#endif // CONTROLPANEL_HPP
