#ifndef CHARACTERMANAGERINTERFACE_HPP
#define CHARACTERMANAGERINTERFACE_HPP

class Character;

class CharacterManagerInterface
{
    public:
        virtual ~CharacterManagerInterface() {};

        /**
         * @brief Clear the given character
         *
         * WARNING: the character object will be deleted and must not be used after this call.
         */
        virtual void clearCharacter(Character& character) = 0;
};

#endif // CHARACTERMANAGERINTERFACE_HPP
