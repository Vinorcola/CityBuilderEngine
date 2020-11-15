#ifndef OPTIONALREFERENCE_HPP
#define OPTIONALREFERENCE_HPP

#include <functional>
#include <QtCore/QtGlobal>

class  Referencable;

template<typename Target>
class OptionalReference
{
        static_assert (std::is_base_of<Referencable, Target>::value, "Target must extend Referencable.");
        friend Referencable;

        typedef std::function<void(OptionalReference<Target>*)> OnDuplicateCallback;
        typedef std::function<void(OptionalReference<Target>*)> OnDeleteCallback;

    private:
        bool valid;
        Target* target;

    protected:
        OnDuplicateCallback onDuplicate;
        OnDeleteCallback onDelete;

    public:
        OptionalReference();
        OptionalReference(Target& target, OnDuplicateCallback onDuplicate, OnDeleteCallback onDelete);
        OptionalReference(const OptionalReference<Target>& other);
        OptionalReference(const OptionalReference<Target>&& other);
        ~OptionalReference();

        void operator= (const OptionalReference<Target>& other) = delete;
        void operator= (const OptionalReference<Target>&& other) = delete;

        bool isNull() const;
        bool isValid() const;
        Target& get() const;

        void reassign(Target& target);
        void clear();

    private:
        void unreference();
};

#endif // OPTIONALREFERENCE_HPP
