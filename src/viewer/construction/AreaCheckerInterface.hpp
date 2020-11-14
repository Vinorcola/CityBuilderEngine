#ifndef AREACHECKERINTERFACE_HPP
#define AREACHECKERINTERFACE_HPP

class MapArea;

class AreaCheckerInterface
{
    public:
        virtual ~AreaCheckerInterface() {};

        virtual bool isConstructible(const MapArea& area) const = 0;
};

#endif // AREACHECKERINTERFACE_HPP
