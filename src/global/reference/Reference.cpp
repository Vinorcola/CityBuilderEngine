#include "Reference.hpp"

#include "src/global/reference/Referencable.hpp"



template<typename Target>
Reference<Target>::Reference(Target& target, OnDuplicateCallback onDuplicate, OnDeleteCallback onDelete) :
    valid(true),
    target(&target),
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
void Reference<Target>::operator=(const Reference<Target>& other)
{
    if (valid) {
        onDelete(this);
    }

    valid = other.valid;
    this->target = other.target;
    onDuplicate = other.onDuplicate;
    onDelete = other.onDelete;

    if (valid) {
        onDuplicate(this);
    }
}



template<typename Target>
bool Reference<Target>::isValid() const
{
    return valid;
}



template<typename Target>
bool Reference<Target>::matches(const Referencable& target) const
{
    return this->target == &target;
}



template<typename Target>
Target& Reference<Target>::get() const
{
    return *target;
}



template<typename Target>
void Reference<Target>::reassign(Target& target)
{
    if (valid) {
        onDelete(this);
    }

    auto newRef(static_cast<Referencable&>(target).getReference<Target>());
    valid = true;
    this->target = &target;
    onDuplicate = newRef.onDuplicate;
    onDelete = newRef.onDelete;

    if (valid) {
        onDuplicate(this);
    }
}



template<typename Target>
void Reference<Target>::unreference()
{
    valid = false;
}
