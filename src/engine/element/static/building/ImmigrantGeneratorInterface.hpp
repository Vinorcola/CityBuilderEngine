#ifndef IMMIGRANTGENERATORINTERFACE_HPP
#define IMMIGRANTGENERATORINTERFACE_HPP

class HouseBuilding;

class ImmigrantGeneratorInterface
{
    public:
        virtual ~ImmigrantGeneratorInterface() {};

        /**
         * @brief Request an immigrant generation.
         *
         * The immigrant will be generated at a random moment.
         */
        virtual void requestImmigrant(HouseBuilding& requester) = 0;
};

#endif // IMMIGRANTGENERATORINTERFACE_HPP
