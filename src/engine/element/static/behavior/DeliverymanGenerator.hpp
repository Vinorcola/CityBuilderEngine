#ifndef DELIVERYMANGENERATOR_HPP
#define DELIVERYMANGENERATOR_HPP

#include <QtCore/QObject>

#include "src/engine/element/static/behavior/AbstractWalkerGenerator.hpp"

class CharacterInformation;
class CycleDate;
class ItemInformation;
class ProcessableBuilding;

class DeliverymanGenerator : public AbstractWalkerGenerator
{
        Q_OBJECT

    public:
        DeliverymanGenerator(ProcessableBuilding* issuer, const CharacterInformation* walkerConf);
};

#endif // DELIVERYMANGENERATOR_HPP
