#ifndef ABSTRACTMAPELEMENT_HPP
#define ABSTRACTMAPELEMENT_HPP

/**
 * @brief The base class for any element that goes on the map.
 *
 * @note Not sure this class is really needed. Right now, static and dynamic element are processed the same, but at some
 * point, this should be changed. Static element can be processed a lot less than dynamic element. This enhancement will
 * be made in order to gain performance.
 */
class AbstractMapElement
{
    public:
        AbstractMapElement();

        virtual ~AbstractMapElement();
};

#endif // ABSTRACTMAPELEMENT_HPP
