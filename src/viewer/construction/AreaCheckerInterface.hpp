#ifndef AREACHECKERINTERFACE_HPP
#define AREACHECKERINTERFACE_HPP

class TileArea;

class AreaCheckerInterface
{
    public:
        virtual ~AreaCheckerInterface() {};

        virtual bool isConstructible(const TileArea& area) const = 0;
};

#endif // AREACHECKERINTERFACE_HPP
