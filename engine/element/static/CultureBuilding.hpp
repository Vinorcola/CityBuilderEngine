#ifndef CULTUREBUILDING_HPP
#define CULTUREBUILDING_HPP

#include "engine/element/static/ServiceBuilding.hpp"

class CultureBuilding : public ServiceBuilding
{
        Q_OBJECT

    private:
        WalkerPool* targetedWalkers;

    public:
        CultureBuilding(QObject* parent, const StaticElementInformation* conf, const MapArea& area, const MapCoordinates& entryPoint);

        virtual void init(const CycleDate& date);

        virtual void process(const CycleDate& date);

        virtual void processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor);

    private slots:
        void requestTargetedWalkerCreation(
            const DynamicElementInformation* elementConf,
            std::function<void(AbstractDynamicMapElement*)> afterCreation
        );
};

#endif // CULTUREBUILDING_HPP
