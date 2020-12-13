#ifndef IMMIGRANTGENERATORINTERFACE_HPP
#define IMMIGRANTGENERATORINTERFACE_HPP

#include <QtCore/QWeakPointer>

class AbstractProcessableBuilding;

class ImmigrantGeneratorInterface
{
    public:
        virtual ~ImmigrantGeneratorInterface() {};

        /**
         * @brief Request an immigrant generation.
         *
         * The immigrant will be generated at a random moment.
         */
        virtual void requestImmigrant(const QWeakPointer<AbstractProcessableBuilding>& requester) = 0;
};

#endif // IMMIGRANTGENERATORINTERFACE_HPP
