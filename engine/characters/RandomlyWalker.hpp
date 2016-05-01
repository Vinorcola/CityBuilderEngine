#ifndef RANDOMLYWALKER_HPP
#define RANDOMLYWALKER_HPP

#include "engine/characters/AbstractCharacter.hpp"





class RandomlyWalker : public AbstractCharacter
{
        Q_OBJECT
        
    public:
        RandomlyWalker();
        
        
        
        virtual void process();
};

#endif // RANDOMLYWALKER_HPP
