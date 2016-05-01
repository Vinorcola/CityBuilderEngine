#include "Processable.hpp"





Processable::Processable(Map* map) :
    QObject(map),
    map(map)
{
    
}





Processable::~Processable()
{
    map->removeProcessable(this);
}
