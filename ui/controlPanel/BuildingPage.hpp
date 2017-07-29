#ifndef BUILDINGPAGE_HPP
#define BUILDINGPAGE_HPP

#include <QWidget>

#include "engine/map/Map.hpp"
#include "ui/controlPanel/ControlPanel.hpp"

class BuildingPage : public QWidget
{
        Q_OBJECT

    public:
        BuildingPage(ControlPanel& buttonCreator);
};

#endif // BUILDINGPAGE_HPP
