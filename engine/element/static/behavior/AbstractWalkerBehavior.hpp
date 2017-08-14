#ifndef ABSTRACTWALKERBEHAVIOR_HPP
#define ABSTRACTWALKERBEHAVIOR_HPP

#include "engine/element/static/behavior/AbstractStaticElementBehavior.hpp"

class AbstractWalkerBehavior : public AbstractStaticElementBehavior
{
        Q_OBJECT

    protected:
        AbstractProcessableStaticMapElement* issuer;

    public:
        AbstractWalkerBehavior(AbstractProcessableStaticMapElement* issuer);

        virtual void clean() = 0;

    signals:
        void requestDynamicElementCreation(
            const DynamicElementInformation* elementConf,
            AbstractProcessableStaticMapElement* issuer,
            std::function<void(AbstractDynamicMapElement*)> afterCreation
        );

        void requestDynamicElementDestruction(
            AbstractDynamicMapElement* element,
            std::function<void()> afterDestruction
        );
};

#endif // ABSTRACTWALKERBEHAVIOR_HPP
