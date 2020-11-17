#include "ReferenceCollection.hpp"



template<typename Target>
ReferenceCollection<Target>::ReferenceCollection() :
    references()
{

}



template<typename Target>
void ReferenceCollection<Target>::append(const Reference<Target>& reference)
{
    references.insert(&reference.get(), reference);
}



template<typename Target>
void ReferenceCollection<Target>::append(const Target& target)
{
    references.insert(&target, static_cast<Referencable&>(target).getReference<Target>());
}



template<typename Target>
void ReferenceCollection<Target>::remove(const Reference<Target>& reference)
{
    references.remove(&reference.get());
}



template<typename Target>
void ReferenceCollection<Target>::remove(const Target& target)
{
    references.remove(&target);
}



template<typename Target>
void ReferenceCollection<Target>::moveAllContentTo(const ReferenceCollection<Target>& other)
{
    other.references.insert(references);
    references.clear();
}



template<typename Target>
void ReferenceCollection<Target>::cleanAllInvalids()
{
    auto iterator(references.begin());
    while (iterator != references.end()) {
        if (!iterator.value().isValid()) {
            iterator = references.erase(iterator);
        }
        else {
            ++iterator;
        }
    }
}



template<typename Target>
typename ReferenceCollection<Target>::Iterator ReferenceCollection<Target>::begin() const
{
    return references.begin();
}



template<typename Target>
typename ReferenceCollection<Target>::Iterator ReferenceCollection<Target>::end() const
{
    return references.end();
}



template<typename Target>
int ReferenceCollection<Target>::length() const
{
    return references.length();
}



template<typename Target>
bool ReferenceCollection<Target>::isEmpty() const
{
    return references.isEmpty();
}



template<typename Target>
bool ReferenceCollection<Target>::contains(const Reference<Target>& reference) const
{
    return references.contains(&reference.get());
}



template<typename Target>
bool ReferenceCollection<Target>::contains(const Target& target) const
{
    return references.contains(&target);
}
