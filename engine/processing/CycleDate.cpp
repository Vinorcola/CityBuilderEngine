#include "CycleDate.hpp"



CycleDate::CycleDate() :
    cycles(0)
{

}



CycleDate::CycleDate(const CycleDate& other) :
    cycles(other.cycles)
{

}



void CycleDate::operator =(const CycleDate& other)
{
    cycles = other.cycles;
}



void CycleDate::operator =(const CycleDate&& other)
{
    cycles = other.cycles;
}



CycleDate::operator bool()
{
    return cycles != 0;
}



void CycleDate::operator ++()
{
    ++cycles;
}



bool CycleDate::operator ==(const CycleDate& other) const
{
    return cycles == other.cycles;
}



bool CycleDate::operator !=(const CycleDate& other) const
{
    return cycles != other.cycles;
}



bool CycleDate::operator <(const CycleDate& other) const
{
    return cycles < other.cycles;
}



bool CycleDate::operator >(const CycleDate& other) const
{
    return cycles > other.cycles;
}



bool CycleDate::operator <=(const CycleDate& other) const
{
    return cycles <= other.cycles;
}



bool CycleDate::operator >=(const CycleDate& other) const
{
    return cycles >= other.cycles;
}



int CycleDate::operator -(const CycleDate& other) const
{
    return cycles - other.cycles;
}



void CycleDate::reassign(const CycleDate& other, const int addInterval)
{
    cycles = other.cycles + addInterval;
}



void CycleDate::reset()
{
    cycles = 0;
}



QString CycleDate::toString() const
{
    return QString::number(cycles);
}
