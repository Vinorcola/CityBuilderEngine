#ifndef RANDOMLYWALKER_HPP
#define RANDOMLYWALKER_HPP

#include "engine/characters/AbstractCharacter.hpp"





class RandomlyWalker : public AbstractCharacter
{
        Q_OBJECT
        
    private:
        int lifePoints;
        
        
        
    public:
        RandomlyWalker(Map* map, const int lifeTime);
        
        
        
        virtual void process();
};

#endif // RANDOMLYWALKER_HPP
