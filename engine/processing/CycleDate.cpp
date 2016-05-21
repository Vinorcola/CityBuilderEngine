#include "CycleDate.hpp"





CycleDate::CycleDate() :
    cycles(0)
{

}





void CycleDate::operator++()
{
    ++cycles;
}





QString CycleDate::toString() const
{
    return QString::number(cycles);
}
