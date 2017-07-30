#include "CycleDate.hpp"



CycleDate::CycleDate() :
    cycles(0)
{

}



CycleDate::CycleDate(const CycleDate& other) :
    cycles(other.cycles)
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



bool CycleDate::operator<(const CycleDate& other) const
{
    return cycles < other.cycles;
}



bool CycleDate::operator>(const CycleDate& other) const
{
    return cycles > other.cycles;
}



bool CycleDate::operator<=(const CycleDate& other) const
{
    return cycles <= other.cycles;
}



bool CycleDate::operator>=(const CycleDate& other) const
{
    return cycles >= other.cycles;
}



void CycleDate::operator=(const CycleDate& other)
{
    cycles = other.cycles;
}



void CycleDate::add(const int numberOfCycles)
{
    cycles += numberOfCycles;
}



QString CycleDate::toString() const
{
    return QString::number(cycles);
}
