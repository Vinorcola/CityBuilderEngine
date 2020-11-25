#ifndef WALKERGENERATIONBEHAVIOR_HPP
#define WALKERGENERATIONBEHAVIOR_HPP

/**
 * @brief Handles the walker generation logic for a building.
 */
class WalkerGenerationBehavior
{
    private:
        const int MAX_WORKERS;
        const int GENERATION_INTERVAL;
        const int POSTPONE_INTERVAL;
        int generationCountDown;

    public:
        WalkerGenerationBehavior(int maxWorkers, int generationInterval);

        bool isReadyToGenerateWalker() const;

        void process(int currentWorkers);
        void postpone();
        void reset();
};

#endif // WALKERGENERATIONBEHAVIOR_HPP
