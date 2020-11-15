#ifndef VIEWERINTERFACE_HPP
#define VIEWERINTERFACE_HPP

#include <QtCore/QObject>

class AbstractBuilding;
class BuildingInformation;
class Character;
class MapArea;
class NatureElement;

class ViewerInterface : public QObject
{
        Q_OBJECT

    public:
        ViewerInterface();

    public slots:
        /**
         * @brief Set (or unset) the pause mode.
         */
        void pause(const bool pause = true);

        /**
         * @brief Set the time-cycle processor speed ratio.
         */
        void setProcessorSpeedRatio(const qreal speedRatio);

        /**
         * @brief Create a building on the map.
         *
         * If the area is not free, the element is not created. For now, we just log with qDebug(). But this fail should
         * be kept silent because it could eventually append in real condition when a static element creation request
         * append while the area get "unfree" during the last time cycle process.
         *
         * @param conf The conf for the new building to create.
         * @param area The location of the element on the map.
         * @throw UnexpectedException Try to create a static element of type None.
         */
        void createBuilding(const BuildingInformation& conf, const MapArea& area);

        /**
         * @brief Update the total population of the given delta.
         */
        void changePopulation(const int populationDelta);

    signals:
        void buildingCreated(QSharedPointer<const AbstractBuilding> building);
        void characterCreated(QSharedPointer<const Character> character);
        void natureElementCreated(NatureElement& natureElement);
        void dateChanged(const int year, const int month);
};

#endif // VIEWERINTERFACE_HPP
