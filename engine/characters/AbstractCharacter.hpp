#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "engine/Processable.hpp"





class AbstractCharacter : public Processable
{
        Q_OBJECT
        
    public:
        AbstractCharacter();
};

#endif // CHARACTER_HPP
