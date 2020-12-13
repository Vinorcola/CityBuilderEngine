#include "CycleDate.hpp"

#include <cassert>

#include "src/defines.hpp"

const int CYCLES_PER_MONTH(20 * CYCLES_PER_SECOND);
const int BUILDING_CYCLES_PER_MONTH(20 * BUILDING_CYCLES_PER_SECOND);
const int CYCLES_BETWEEN_BUILDING_PROCESSES(CYCLES_PER_SECOND / BUILDING_CYCLES_PER_SECOND);
const int MONTHS_PER_YEAR(12);



CycleDate::CycleDate() :
    valid(false),
    year(0),
    month(0),
    cycles(0)
{

}



CycleDate::CycleDate(const int year, const int month, const int cycles) :
    valid(true),
    year(year),
    month(month),
    cycles(cycles)
{
    assert(month >= 1);
    assert(month <= 12);
    assert(cycles >= 0);
    assert(cycles <= CYCLES_PER_MONTH);
}



CycleDate::CycleDate(const CycleDate& other) :
    valid(other.valid),
    year(other.year),
    month(other.month),
    cycles(other.cycles)
{

}



void CycleDate::operator =(const CycleDate& other)
{
    valid = other.valid;
    year = other.year;
    month = other.month;
    cycles = other.cycles;
}



CycleDate::operator bool()
{
    return valid;
}



bool CycleDate::operator !()
{
    return !valid;
}



void CycleDate::operator ++()
{
    if (valid) {
        ++cycles;
        if (cycles % CYCLES_PER_MONTH == 0) {
            cycles = 0;
            ++month;
            if (month % MONTHS_PER_YEAR == 1) {
                month = 1;
                ++year;
            }
        }
    }
}



bool CycleDate::operator ==(const CycleDate& other) const
{
    return valid == other.valid && year == other.year && month == other.month && cycles == other.cycles;
}



bool CycleDate::operator !=(const CycleDate& other) const
{
    return valid != other.valid || year != other.year || month == other.month || cycles != other.cycles;
}



bool CycleDate::operator <(const CycleDate& other) const
{
    // Truth table:
    // T\O |    V    |   I   |
    // ----+---------+-------+
    //   V | Compare | false |
    // ----+---------+-------+
    //   I |  true   | false |

    if (!valid) {
        // If I'm invalid, I'm only lower if other is valid.
        return other.valid;
    }
    if (!other.valid) {
        // If I'm valid and other is invalid, I'm greater.
        return false;
    }

    return
        year < other.year || (
            year == other.year && (
                month < other.month || (
                    month == other.month && cycles < other.cycles
                )
            )
        );
}



bool CycleDate::operator >(const CycleDate& other) const
{
    // Truth table:
    // T\O |    V    |   I   |
    // ----+---------+-------+
    //   V | Compare | true  |
    // ----+---------+-------+
    //   I |  false  | false |

    if (!valid) {
        // I'm invalid, I'm lower.
        return false;
    }
    if (!other.valid) {
        // I'm valid and other is invalid. I'm greater.
        return true;
    }

    return
        year > other.year || (
            year == other.year && (
                month > other.month || (
                    month == other.month && cycles > other.cycles
                )
            )
        );
}



bool CycleDate::operator <=(const CycleDate& other) const
{
    // Truth table:
    // T\O |    V    |   I   |
    // ----+---------+-------+
    //   V | Compare | false |
    // ----+---------+-------+
    //   I |  true   | false |

    if (!valid) {
        // If I'm invalid, I'm only lower if other is valid.
        return other.valid;
    }
    if (!other.valid) {
        // If I'm valid and other is invalid, I'm greater.
        return false;
    }

    return
        year < other.year || (
            year == other.year && (
                month < other.month || (
                    month == other.month && cycles <= other.cycles
                )
            )
        );
}



bool CycleDate::operator >=(const CycleDate& other) const
{
    // Truth table:
    // T\O |    V    |   I   |
    // ----+---------+-------+
    //   V | Compare | true  |
    // ----+---------+-------+
    //   I |  false  | false |

    if (!valid) {
        // I'm invalid, I'm lower.
        return false;
    }
    if (!other.valid) {
        // I'm valid and other is invalid. I'm greater.
        return true;
    }

    return
        year > other.year || (
            year == other.year && (
                month > other.month || (
                    month == other.month && cycles >= other.cycles
                )
            )
        );
}



int CycleDate::operator -(const CycleDate& other) const
{
    if (!valid || !other.valid) {
        return 0;
    }

    return
        cycles - other.cycles
        + CYCLES_PER_MONTH * (month - other.month)
        + CYCLES_PER_MONTH * MONTHS_PER_YEAR * (year - other.year);
}



void CycleDate::reassign(const CycleDate& other, const int addInterval)
{
    if (other.valid) {
        valid = true;
        cycles = other.cycles + addInterval;
        month = other.month;
        year = other.year;
        while (cycles >= CYCLES_PER_MONTH) {
            cycles -= CYCLES_PER_MONTH;
            ++month;
        }
        while (month >= MONTHS_PER_YEAR) {
            month -= MONTHS_PER_YEAR;
            ++year;
        }
    } else {
        reset();
    }
}



void CycleDate::reset()
{
    valid = false;
    year = 0;
    month = 0;
    cycles = 0;
}



int CycleDate::getYear() const
{
    return year;
}



int CycleDate::getMonth() const
{
    return month;
}



bool CycleDate::isFirstCycleOfMonth() const
{
    return cycles == 0;
}



bool CycleDate::isBuildingCycle() const
{
    return (cycles % CYCLES_BETWEEN_BUILDING_PROCESSES) == 0;
}



QString CycleDate::toString() const
{
    if (!valid) {
        return "Invalid date";
    }

    return QString::number(year) + '-' + (month < 10 ? "0" : "") + QString::number(month) + '-' + QString::number(cycles);
}



int CycleDate::getCyclesPerYear()
{
    return CYCLES_PER_MONTH * MONTHS_PER_YEAR;
}



int CycleDate::getBuildingCyclesPerYear()
{
    return BUILDING_CYCLES_PER_MONTH * MONTHS_PER_YEAR;
}
