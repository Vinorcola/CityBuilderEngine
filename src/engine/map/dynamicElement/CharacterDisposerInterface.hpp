#ifndef CHARACTERDISPOSERINTERFACE_HPP
#define CHARACTERDISPOSERINTERFACE_HPP

class Character;

class CharacterDisposerInterface
{
    public:
        virtual ~CharacterDisposerInterface() {};

        /**
         * @brief Clear the given character
         *
         * WARNING: the character object will be deleted and must not be used after this call.
         */
        virtual void clearCharacter(Character& character) = 0;
};

#endif // CHARACTERDISPOSERINTERFACE_HPP
