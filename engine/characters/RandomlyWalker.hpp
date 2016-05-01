#ifndef RANDOMLYWALKER_HPP
#define RANDOMLYWALKER_HPP

#include "engine/characters/AbstractCharacter.hpp"





class RandomlyWalker : public AbstractCharacter
{
        Q_OBJECT
        
    private:
        int walkPoints;
        
        
        
    public:
        RandomlyWalker(Map* map, const int walkPoints);
        
        
        
        virtual void process();
};

#endif // RANDOMLYWALKER_HPP
