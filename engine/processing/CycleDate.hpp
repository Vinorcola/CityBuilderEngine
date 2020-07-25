#ifndef CYCLEDATE_HPP
#define CYCLEDATE_HPP

#include <QtCore/QString>

/**
 * @brief Represent a date of the time-cycle processor.
 *
 * Currently, the date is simply an integer starting at 1 and incrementing at each cycle. But in the future, it could
 * become something more sophisticated.
 */
class CycleDate
{
    private:
        bool valid;
        int year;
        int month;
        int cycles;

    public:
        CycleDate();

        CycleDate(const int year, const int month, const int cycles = 0);

        /**
         * @brief Copy a date and optionally add an interval.
         */
        CycleDate(const CycleDate& other);

        /**
         * @brief Copy the other cycle date.
         */
        void operator =(const CycleDate& other);

        /**
         * @brief Indicate if the date is valid.
         *
         * An empty date (initialized from the empty constructor) is invalid.
         */
        operator bool();

        /**
         * @brief Indicate if the date is invlid.
         */
        bool operator !();

        /**
         * @brief Increment the date to the next date (pass 1 cycle).
         */
        void operator ++();

        /**
         * @brief Compare 2 dates to check if they are equals or not.
         */
        bool operator ==(const CycleDate& other) const;

        /**
         * @brief Compare 2 dates to check if they are different or not.
         */
        bool operator !=(const CycleDate& other) const;

        /**
         * @brief Compare 2 dates to check if other is strictly later than the current date.
         */
        bool operator <(const CycleDate& other) const;

        /**
         * @brief Compare 2 dates to check if other is strictly earlier than the current date.
         */
        bool operator >(const CycleDate& other) const;

        /**
         * @brief Compare 2 dates to check if other is later than the current date.
         */
        bool operator <=(const CycleDate& other) const;

        /**
         * @brief Compare 2 dates to check if other is earlier than the current date.
         */
        bool operator >=(const CycleDate& other) const;

        /**
         * @brief Return the difference between the 2 dates.
         */
        int operator -(const CycleDate& other) const;

        /**
         * @brief Reassign the date according to another date, and add an interval.
         */
        void reassign(const CycleDate& other, const int addInterval);

        /**
         * @brief Reset a date.
         */
        void reset();

        int getYear() const;

        int getMonth() const;

        // DEBUG //
        QString toString() const;
};

#endif // CYCLEDATE_HPP
