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
        QString toString() const;
};

#endif // CYCLEDATE_HPP
