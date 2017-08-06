#ifndef CYCLEDATE_HPP
#define CYCLEDATE_HPP

#include <QtCore/QString>

/**
 * @brief Represent a date for the time cycle processor.
 *
 * Currently, the date is simply an integer starting at 1 and incrementing at each cycle. But in the future, it could
 * become something more sophisticated.
 */
class CycleDate
{
    private:
        int cycles;

    public:
        CycleDate();

        CycleDate(const CycleDate& other);

        /**
         * @brief Increment the date to the next date (pass 1 cycle).
         */
        void operator++();

        /**
         * @brief Compare 2 dates to check if they are equals or not.
         */
        bool operator==(const CycleDate& other) const;

        /**
         * @brief Compare 2 dates to check if other is strictly later than the current date.
         */
        bool operator<(const CycleDate& other) const;

        /**
         * @brief Compare 2 dates to check if other is strictly earlier than the current date.
         */
        bool operator>(const CycleDate& other) const;

        /**
         * @brief Compare 2 dates to check if other is later than the current date.
         */
        bool operator<=(const CycleDate& other) const;

        /**
         * @brief Compare 2 dates to check if other is earlier than the current date.
         */
        bool operator>=(const CycleDate& other) const;

        /**
         * @brief Copy the ither cycle date.
         */
        void operator=(const CycleDate& other);

        /**
         * @brief Add a certain amount of cycles to the date.
         *
         * @param numberOfCycles
         */
        void add(const int numberOfCycles);

        // DEBUG //
        QString toString() const;
};

#endif // CYCLEDATE_HPP
