#include "Referencable.hpp"



Referencable::~Referencable()
{
    for (auto reference : references) {
        reference->unreference();
    }
    for (auto reference : optionalReferences) {
        reference->unreference();
    }
}



template<typename T>
Reference<T> Referencable::getReference()
{
    references.append({
        *this,
        [this](Reference<T>* reference) {
            if (reference->isValid()) {
                references.append(reference);
            }
        },
        [this](Reference<T>* reference) {
            if (reference->isValid()) {
                references.removeAll(reference);
            }
        }
    });

    return references.last();
}



template<typename T>
OptionalReference<T> Referencable::getOptionalReference()
{
    optionalReferences.append({
        *this,
        [this](OptionalReference<T>* reference) {
            if (reference->isValid()) {
                references.append(reference);
            }
        },
        [this](OptionalReference<T>* reference) {
            if (reference->isValid()) {
                references.removeAll(reference);
            }
        }
    });

    return optionalReferences.last();
}
