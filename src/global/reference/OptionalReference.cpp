#include "OptionalReference.hpp"

#include <cassert>

#include "src/global/reference/Referencable.hpp"



template<typename Target>
OptionalReference<Target>::OptionalReference() :
    valid(false),
    target(nullptr),
    onDuplicate(),
    onDelete()
{

}



template<typename Target>
OptionalReference<Target>::OptionalReference(Target& target, OnDuplicateCallback onDuplicate, OnDeleteCallback onDelete) :
    valid(true),
    target(&target),
    onDuplicate(onDuplicate),
    onDelete(onDelete)
{

}



template<typename Target>
OptionalReference<Target>::OptionalReference(const OptionalReference<Target>& other) :
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
OptionalReference<Target>::OptionalReference(const OptionalReference<Target>&& other) :
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
OptionalReference<Target>::~OptionalReference()
{
    if (target && valid) {
        onDelete(this);
    }
}



template<typename Target>
bool OptionalReference<Target>::isNull() const
{
    return target != nullptr;
}



template<typename Target>
bool OptionalReference<Target>::isValid() const
{
    return target && valid;
}



template<typename Target>
Target& OptionalReference<Target>::get() const
{
    assert(target != nullptr);

    return *target;
}



template<typename Target>
void OptionalReference<Target>::reassign(Target& target)
{
    if (isValid()) {
        onDelete(this);
    }

    auto newRef(static_cast<Referencable&>(target).getOptionalReference<Target>());
    valid = true;
    this->target = &target;
    onDuplicate = newRef.onDuplicate;
    onDelete = newRef.onDelete;
}



template<typename Target>
void OptionalReference<Target>::clear()
{
    if (isValid()) {
        onDelete(this);
    }

    valid = false;
    target = nullptr;
}



template<typename Target>
void OptionalReference<Target>::unreference()
{
    valid = false;
}
