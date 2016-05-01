#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "engine/Processable.hpp"





class AbstractCharacter : public Processable
{
        Q_OBJECT
        
    private:
        bool alive;
        
        
        
    public:
        AbstractCharacter(Map* map);
        
        
        
        /**
         * @brief Indicate if the character is alive or not.
         */
        bool isAlive() const;
        
        
        
        /**
         * @brief Kill the character.
         */
        void kill();
};

#endif // CHARACTER_HPP
