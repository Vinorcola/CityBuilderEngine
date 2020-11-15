#ifndef LABORATORYBUILDING_HPP
#define LABORATORYBUILDING_HPP

#include <QtCore/QPointer>

#include "src/engine/element/static/building/ProcessableBuilding.hpp"
#include "src/engine/processing/CycleDate.hpp"

class Character;
class CharacterFactoryInterface;

class LaboratoryBuilding : public ProcessableBuilding
{
        Q_OBJECT

    private:
        CharacterFactoryInterface& characterFactory;
        CycleDate walkerGenerationLimitDate;
        QPointer<Character> scientist;
        CycleDate nextWalkerGenerationDate;

    public:
        LaboratoryBuilding(
            QObject* parent,
            CharacterFactoryInterface& characterFactory,
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        virtual void process(const CycleDate& date) override;

        virtual bool processInteraction(const CycleDate& date, Character& actor) override;

    private:
        /**
         * @brief Indicate if a new miner can be generated.
         */
        bool canGenerateNewWalker() const;

        /**
         * @brief Setup the next miner generation date.
         */
        void setupNextWalkerGenerationDate(const CycleDate& date);
};

#endif // LABORATORYBUILDING_HPP
