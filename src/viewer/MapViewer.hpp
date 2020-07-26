#ifndef MAPVIEWER_HPP
#define MAPVIEWER_HPP

#include <QtWidgets/QGraphicsView>

class BuildingInformation;
class Map;

class MapViewer : public QGraphicsView
{
        Q_OBJECT

    public:
        explicit MapViewer(Map& map, QWidget* parent = nullptr);

    public slots:
        void buildingRequest(const BuildingInformation* elementConf);
};

#endif // MAPVIEWER_HPP
