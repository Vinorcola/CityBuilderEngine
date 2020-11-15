#include "Reference.hpp"



template<typename Target>
Reference<Target>::Reference(Target& target, OnDuplicateCallback onDuplicate, OnDeleteCallback onDelete) :
    valid(true),
    target(target),
    onDuplicate(onDuplicate),
    onDelete(onDelete)
{

}



template<typename Target>
Reference<Target>::Reference(const Reference<Target>& other) :
    valid(other.valid),
    target(other.target),
    onDuplicate(other.onDuplicate),
    onDelete(other.onDelete)
{
    if (valid) {
        onDuplicate(this);
    }
}



template<typename Target>
Reference<Target>::Reference(const Reference<Target>&& other) :
    valid(other.valid),
    target(other.target),
    onDuplicate(other.onDuplicate),
    onDelete(other.onDelete)
{
    if (valid) {
        onDuplicate(this);
    }
}



template<typename Target>
Reference<Target>::~Reference()
{
    if (valid) {
        onDelete(this);
    }
}



template<typename Target>
bool Reference<Target>::isValid() const
{
    return valid;
}



template<typename Target>
Target& Reference<Target>::get() const
{
    return target;
}



template<typename Target>
void Reference<Target>::unreference()
{
    valid = false;
}
