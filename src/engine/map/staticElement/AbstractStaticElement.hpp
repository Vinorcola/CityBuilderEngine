#ifndef ABSTRACTSTATICELEMENT_HPP
#define ABSTRACTSTATICELEMENT_HPP

#include <QtCore/QtGlobal>

/**
 * @brief An empty base class for all static elements.
 */
class AbstractStaticElement
{
        Q_DISABLE_COPY_MOVE(AbstractStaticElement)

    public:
        AbstractStaticElement() {};
        virtual ~AbstractStaticElement() {};
};

#endif // ABSTRACTSTATICELEMENT_HPP
