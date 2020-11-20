#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <QtCore/QObject>
#include <QtCore/QString>

#include "src/engine/state/CityState.hpp"
#include "src/engine/state/State.hpp"
#include "src/defines.hpp"

class BuildingInformation;
class City;
class Conf;
class MapArea;
class MapState;
class QSize;

class Engine : public QObject
{
        Q_OBJECT

    private:
        const Conf& conf;
        optional<owner<City*>> city;

    public:
        Engine(const Conf& conf);
        ~Engine();

        void loadCity(const QString& cityFilePath);

        const MapState& getMapState() const;
        State getCurrentState() const;

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

    signals:
        void stateUpdated(State);


};

#endif // ENGINE_HPP
