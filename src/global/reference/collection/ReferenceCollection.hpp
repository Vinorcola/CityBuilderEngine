#ifndef REFERENCECOLLECTION_HPP
#define REFERENCECOLLECTION_HPP

#include <QtCore/QHash>

#include "src/global/reference/Referencable.hpp"
#include "src/global/reference/Reference.hpp"

/**
 * @brief An unordered and unique collection of references.
 *
 * Unicity is done on reference's target.
 */
template<typename Target>
class ReferenceCollection
{
        Q_DISABLE_COPY_MOVE(ReferenceCollection)

        static_assert (std::is_base_of<Referencable, Target>::value, "Target must extend Referencable.");
        using Iterator = typename QHash<Target*, Reference<Target>>::const_iterator;

    private:
        QHash<Target*, Reference<Target>> references;

    public:
        ReferenceCollection();

        void append(const Reference<Target>& reference);
        void append(const Target& target);
        void remove(const Reference<Target>& reference);
        void remove(const Target& target);
        void moveAllContentTo(const ReferenceCollection<Target>& other);
        void cleanAllInvalids();

        Iterator begin() const;
        Iterator end() const;

        int length() const;
        bool isEmpty() const;
        bool contains(const Reference<Target>& reference) const;
        bool contains(const Target& target) const;
};

#endif // REFERENCECOLLECTION_HPP
