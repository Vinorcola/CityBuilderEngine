#ifndef RANDOMROADPATH_HPP
#define RANDOMROADPATH_HPP

#include "src/engine/map/path/PathInterface.hpp"

class Tile;

class RandomRoadPath : public PathInterface
{
    private:
        const Tile* previousTile;
        const Tile* currentTile;
        int wanderingCredits;
        bool obsolete;

    public:
        RandomRoadPath(const Tile& initialLocation, const int wanderingCredits);

        virtual bool isObsolete() const override;
        virtual bool isCompleted() const override;

        virtual bool isNextTileValid() const override;
        virtual const Tile& getNextTile() override;

    private:
        optional<const Tile*> getNextRandomTile() const;
};

#endif // RANDOMROADPATH_HPP
