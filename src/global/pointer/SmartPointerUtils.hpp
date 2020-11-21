#ifndef SMARTPOINTERUTILS_HPP
#define SMARTPOINTERUTILS_HPP

#include <QtCore/QHash>
#include <QtCore/QWeakPointer>

class Character;

template<class Target>
bool matches(const QWeakPointer<Target>& pointer, const Target& target)
{
    return pointer.toStrongRef().get() == &target;
}

template<class Key, class Target>
void cleanInvalids(QHash<Key, QWeakPointer<Target>>& collection)
{
    auto iterator(collection.begin());
    while (iterator != collection.end()) {
        if (!iterator.value().toStrongRef()) {
            iterator = collection.erase(iterator);
        }
        else {
            ++iterator;
        }
    }
}

#endif // SMARTPOINTERUTILS_HPP
