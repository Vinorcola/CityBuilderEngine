#ifndef REFERENCE_HPP
#define REFERENCE_HPP

#include <functional>
#include <QtCore/QtGlobal>

class  Referencable;

/**
 * @brief A smart reference that knows if the target has been deleted or not.
 */
template<typename Target>
class Reference
{
        static_assert (std::is_base_of<Referencable, Target>::value, "Target must extend Referencable.");
        friend Referencable;

        typedef std::function<void(Reference<Target>*)> OnDuplicateCallback;
        typedef std::function<void(Reference<Target>*)> OnDeleteCallback;

    private:
        bool valid;
        Target* target;

    protected:
        OnDuplicateCallback onDuplicate;
        OnDeleteCallback onDelete;

    public:
        Reference(Target& target, OnDuplicateCallback onDuplicate, OnDeleteCallback onDelete);
        Reference(const Reference<Target>& other);
        Reference(const Reference<Target>&& other);
        ~Reference();

        void operator=(const Reference<Target>& other);
        void operator=(const Reference<Target>&& other) = delete;

        bool isValid() const;
        bool matches(const Referencable& target) const;
        Target& get() const;

        void reassign(Target& target);

    private:
        void unreference();
};

#endif // REFERENCE_HPP
