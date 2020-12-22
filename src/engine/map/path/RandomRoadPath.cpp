#include "RandomRoadPath.hpp"

#include <QtCore/QList>
#include <QtCore/QRandomGenerator>

#include "src/engine/map/Tile.hpp"



RandomRoadPath::RandomRoadPath(const Tile& initialLocation, const int wanderingCredits) :
    previousTile(&initialLocation),
    currentTile(&initialLocation),
    wanderingCredits(wanderingCredits),
    obsolete(false)
{

}



bool RandomRoadPath::isObsolete() const
{
    return obsolete;
}



bool RandomRoadPath::isCompleted() const
{
    return wanderingCredits <= 0;
}



bool RandomRoadPath::isNextTileValid() const
{
    return !obsolete && wanderingCredits <= 0;
}



const Tile& RandomRoadPath::getNextTile()
{
    auto nextTile(getNextRandomTile());

    previousTile = currentTile;
    if (!nextTile) {
        obsolete = true;
    }
    else {
        currentTile = nextTile;
        --wanderingCredits;
    }

    return *currentTile;
}



optional<const Tile*> RandomRoadPath::getNextRandomTile() const
{
    QList<const Tile*> roadNeighbours;
    for (auto neighbour : currentTile->relatives().straightNeighbours) {
        if (neighbour->isRoad()) {
            roadNeighbours.append(neighbour);
        }
    }

    if (roadNeighbours.size() == 0) {
        // Character is on a single road tile.
        return nullptr;
    }
    if (roadNeighbours.size() == 1) {
        // Dead end, must go back.
        return roadNeighbours.first();
    }

    // We remove the previous node to avoid going back on a bifurcation.
    if (previousTile != currentTile) {
        roadNeighbours.removeOne(previousTile);
    }

    if (roadNeighbours.size() == 1) {
        // Only one choice left
        return roadNeighbours.first();
    }

    // Choose random.
    return roadNeighbours.at(QRandomGenerator::global()->bounded(0, roadNeighbours.size()));
}
