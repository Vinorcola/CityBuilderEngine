#ifndef TARGETEDWALKERPOOL_HPP
#define TARGETEDWALKERPOOL_HPP

#include "engine/element/WalkerPool.hpp"
#include "engine/map/searchEngine/SearchEngine.hpp"

class TargetedWalkerPool : public WalkerPool
{
        Q_OBJECT

    private:
        const SearchEngine* searchEngine;
        StaticSearchCriteria targetSearchCriteria;

    public:
        TargetedWalkerPool(
            QObject* parent,
            const SearchEngine* searchEngine,
            const DynamicElementInformation* elementConf,
            const int generationInterval,
            const StaticSearchCriteria& targetSearchCriteria,
            const int max = 1
        );

        virtual void process(const CycleDate& date);

    protected:
        void processTargetedWalkerGeneration(const CycleDate& currentDate, AbstractProcessableStaticMapElement* target);
};

#endif // TARGETEDWALKERPOOL_HPP
