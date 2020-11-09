#ifndef AREACHECKER_HPP
#define AREACHECKER_HPP

class MapArea;

class AreaChecker
{
    public:
        virtual ~AreaChecker() {};

        virtual bool isConstructible(const MapArea& area) const = 0;
};

#endif // AREACHECKER_HPP
