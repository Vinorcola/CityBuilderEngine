#ifndef MAPVIEWER_HPP
#define MAPVIEWER_HPP

#include <QtWidgets/QGraphicsView>

#include "src/viewer/image/ImageLibrary.hpp"

class BuildingInformation;
class Conf;
class Map;

class MapViewer : public QGraphicsView
{
        Q_OBJECT

    private:
        ImageLibrary imageLibrary;

    public:
        MapViewer(const Conf& conf, const Map& map, QWidget* parent = nullptr);

    public slots:
        void buildingRequest(const BuildingInformation* elementConf);
};

#endif // MAPVIEWER_HPP
