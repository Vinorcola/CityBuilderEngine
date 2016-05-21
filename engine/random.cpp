#include "random.hpp"

#include <qglobal.h>





int randomInt(const int min, const int max)
{
    return qrand() % ((max + 1) - min) + min;
}
