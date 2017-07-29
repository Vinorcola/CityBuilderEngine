#include "CycleDate.hpp"



CycleDate::CycleDate() :
    cycles(0)
{

}



void CycleDate::operator++()
{
    ++cycles;
}



bool CycleDate::operator==(const CycleDate& other) const
{
    return cycles == other.cycles;
}



void CycleDate::add(const int numberOfCycles)
{
    cycles += numberOfCycles;
}



QString CycleDate::toString() const
{
    return QString::number(cycles);
}
