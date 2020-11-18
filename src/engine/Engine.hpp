#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <QtCore/QString>

#include "src/defines.hpp"

class City;
class Conf;

class Engine
{
    private:
        const Conf& conf;
        owner<City*> city;

    public:
        explicit Engine(const Conf& conf);
        ~Engine();

        void loadCity(const QString& cityFilePath);
};

#endif // ENGINE_HPP
