#ifndef CONDITIONALRANDOMWALKERGENERATOR_HPP
#define CONDITIONALRANDOMWALKERGENERATOR_HPP

#include "src/engine/element/static/behavior/RandomWalkerGenerator.hpp"
#include "src/engine/processing/CycleDate.hpp"

class Character;
class CharacterInformation;
class ProcessableBuilding;

/**
 * @brief A walker generator based on a conditionnal generation.
 *
 * This behavior generates a walker only when some conditions are fullfuilled.
 */
class ConditionalRandomWalkerGenerator : public RandomWalkerGenerator
{
        Q_OBJECT

    private:
        const CharacterInformation* dependencyWalkerConf;
        const int activityInterval;
        CycleDate canGenarateWalkerUntilDate;

    public:
        ConditionalRandomWalkerGenerator(
            ProcessableBuilding* issuer,
            const CharacterInformation* walkerConf,
            const CharacterInformation* dependencyWalkerConf,
            const int generationInterval,
            const int maxWalkers = 1
        );

        virtual void process(const CycleDate &date) override;

        virtual bool processInteraction(const CycleDate& date, Character* actor) override;

    protected:
        virtual bool canSetupNextGenerationDate(const CycleDate& currentDate) const override;
};

#endif // CONDITIONALRANDOMWALKERGENERATOR_HPP
