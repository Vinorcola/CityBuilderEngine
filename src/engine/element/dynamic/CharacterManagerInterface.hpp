#ifndef CHARACTERMANAGERINTERFACE_HPP
#define CHARACTERMANAGERINTERFACE_HPP

class Character;

class CharacterManagerInterface
{
    public:
        virtual ~CharacterManagerInterface() {};

        virtual void clearCharacter(Character& character) = 0;
};

#endif // CHARACTERMANAGERINTERFACE_HPP
