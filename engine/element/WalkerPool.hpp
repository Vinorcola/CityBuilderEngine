#ifndef WALKERPOOL_HPP
#define WALKERPOOL_HPP

#include "engine/element/dynamic/TargetedWalker.hpp"
#include "engine/processing/AbstractProcessable.hpp"

class WalkerPool : public AbstractProcessable
{
        Q_OBJECT

    protected:
        const DynamicElementInformation* elementConf;
        const int generationInterval;
        const int max;
        CycleDate nextGenerationDate;
        QList<QPointer<TargetedWalker>> walkers;

    public:
        WalkerPool(
            QObject* parent,
            const DynamicElementInformation* elementConf,
            const int generationInterval,
            const int max = 1
        );

        bool contains(const TargetedWalker* walker) const;

        void clean(const CycleDate& currentDate);

        virtual void init(const CycleDate& date);

        virtual void process(const CycleDate& date);

    protected:
        void setupNextWalkerGenerationDate(const CycleDate& currentDate);

        void processWalkerGeneration(const CycleDate& currentDate);

    signals:
        void requestDynamicElementCreation(
            const DynamicElementInformation* elementConf,
            std::function<void(AbstractDynamicMapElement*)> afterCreation
        );
};

#endif // WALKERPOOL_HPP
