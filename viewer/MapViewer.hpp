#ifndef MAPVIEWER_HPP
#define MAPVIEWER_HPP

#include <QtWidgets/QGraphicsView>

class Map;
class StaticElementInformation;

class MapViewer : public QGraphicsView
{
        Q_OBJECT

    public:
        explicit MapViewer(Map& map, QWidget* parent = nullptr);

    public slots:
        void buildingRequest(const StaticElementInformation* elementConf);
};

#endif // MAPVIEWER_HPP
