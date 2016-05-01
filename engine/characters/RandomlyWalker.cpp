#include "RandomlyWalker.hpp"

#include <QDebug>





RandomlyWalker::RandomlyWalker(Map* map, const int walkPoints) :
    AbstractCharacter(map, 1, 5),
    walkPoints(walkPoints)
{
    
}





void RandomlyWalker::process()
{
    if (--walkPoints == 0)
    {
        qDebug() << "  - Walk terminate, let's go back!";
        kill();
    }
}
