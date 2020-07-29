#ifndef ABSTRACTWALKERGENERATOR_HPP
#define ABSTRACTWALKERGENERATOR_HPP

#include <functional>
#include <QtCore/QList>
#include <QtCore/QPointer>

#include "src/engine/element/dynamic/Character.hpp"
#include "src/engine/element/static/behavior/AbstractActivityBehavior.hpp"
#include "src/engine/processing/CycleDate.hpp"

class Character;
class CharacterInformation;
class ProcessableBuilding;

/**
 * @brief The base class for behavior generating walkers (dynamic elements).
 *
 * Such behavior usually generates a certain number of walker every interval of time, based on the activity ratio and
 * the max number of walkers supported.
 */
class AbstractWalkerGenerator : public AbstractActivityBehavior
{
        Q_OBJECT

    protected:
        ProcessableBuilding* issuer;
        const CharacterInformation& walkerConf;
        const int generationInterval;
        const int maxWalkers;
        bool needToSetupNextGenerationDate;
        CycleDate nextGenerationDate;
        QList<QPointer<Character>> walkers;

    public:
        AbstractWalkerGenerator(
            ProcessableBuilding* issuer,
            const CharacterInformation& walkerConf,
            const int generationInterval,
            const int maxWalkers = 1
        );

        /**
         * @brief Indicate if the walker belongs to this walker generator.
         * @param walker
         */
        bool contains(const Character* walker) const;

        /**
         * @brief Clean the list of walkers by removing deleted walkers.
         */
        virtual void clean();

        /**
         * @brief Change the generation speed ratio.
         *
         * The current date is needed in order to calculate the next generation date according to the new generation
         * speed ratio. Note that a ratio of 0 will reset the next generation date.
         *
         * @param ratio
         * @param currentDate
         */
        virtual void setActivitySpeedRatio(qreal ratio, const CycleDate& currentDate) override;

        virtual bool acceptItem(const ItemInformation& itemType) const override;

        virtual void process(const CycleDate& date) override;

        virtual bool processInteraction(const CycleDate& date, Character* actor) override;

    protected:
        virtual bool canSetupNextGenerationDate(const CycleDate& currentDate) const;

        void setupNextGenerationDate(const CycleDate& currentDate);

        virtual void generate();

    signals:
        void requestDynamicElementCreation(
            const CharacterInformation& elementConf,
            ProcessableBuilding* issuer,
            std::function<void(Character*)> afterCreation
        );

        void requestDynamicElementDestruction(
            Character* element,
            std::function<void()> afterDestruction
        );
};

#endif // ABSTRACTWALKERGENERATOR_HPP
