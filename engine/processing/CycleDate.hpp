#ifndef CYCLEDATE_HPP
#define CYCLEDATE_HPP

#include <QString>





class CycleDate
{
    private:
        int cycles;



    public:
        CycleDate();



        void operator++();
        bool operator==(const CycleDate& other) const;
        void add(const int numberOfCycles);
        QString toString() const;
};

#endif // CYCLEDATE_HPP
