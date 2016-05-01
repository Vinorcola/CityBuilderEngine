#include "RandomlyWalker.hpp"

#include <QDebug>





RandomlyWalker::RandomlyWalker(Map* map, const int lifeTime) :
    AbstractCharacter(map),
    lifePoints(lifeTime)
{
    
}





void RandomlyWalker::process()
{
    if (--lifePoints == 0)
    {
        qDebug() << "  - Walker killed!";
        kill();
    }
}
