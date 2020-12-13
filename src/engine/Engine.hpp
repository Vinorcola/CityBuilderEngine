#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <QtCore/QObject>
#include <QtCore/QString>

#include "src/engine/state/CityState.hpp"
#include "src/engine/state/State.hpp"
#include "src/viewer/construction/AreaCheckerInterface.hpp"
#include "src/viewer/construction/RoadPathGeneratorInterface.hpp"
#include "src/defines.hpp"

class BuildingInformation;
class City;
class Conf;
class MapArea;
class MapState;
class QSize;

class Engine : public QObject, public AreaCheckerInterface, public RoadPathGeneratorInterface
{
        Q_OBJECT

    private:
        const Conf& conf;
        optional<owner<City*>> city;

    public:
        Engine(const Conf& conf);
        ~Engine();

        void loadCity(const QString& cityFilePath);

        MapState getMapState() const;
        State getCurrentState() const;

        virtual bool isConstructible(const MapArea& area) const override;
        virtual QList<MapCoordinates> getShortestPathForRoad(
            const MapCoordinates& origin,
            const MapCoordinates& target
        ) const override;

    public slots:
        /**
         * @brief Set (or unset) the pause mode.
         */
        void pause(const bool pause = true);

        /**
         * @brief Set the time-cycle processor speed ratio.
         */
        void setProcessorSpeedRatio(const qreal speedRatio);
        qreal getProcessorSpeedRatio() const;

        /**
         * @brief Force the next process to occur.
         *
         * This is only for debug prupose. The process will only be triggered if the processor have been paused.
         */
        void forceNextProcess();

        /**
         * @brief Create a building on the map.
         *
         * If the area is not free, the element is not created. For now, we just log with qDebug(). But this fail should
         * be kept silent because it could eventually append in real condition when a static element creation request
         * append while the area get "unfree" during the last time cycle process.
         *
         * @param type        The conf for the new building to create.
         * @param leftCorner  The location of the left corner of the construction area.
         * @param orientation The orientation of the building.
         * @throw UnexpectedException Try to create a static element of type None.
         */
        void createBuilding(const BuildingInformation& type, const MapCoordinates& leftCorner, Direction orientation);

    signals:
        void stateUpdated(State);


};

#endif // ENGINE_HPP
