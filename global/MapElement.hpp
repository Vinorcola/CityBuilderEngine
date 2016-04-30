#ifndef MAPELEMENT_HPP
#define MAPELEMENT_HPP

#include <QPoint>
#include <QSize>





class MapSize
{
    private:
        int size;
        
        
        
    public:
        MapSize() : size(1) {}
        explicit MapSize(int size) : size(size) {}
        
        int getSize() const { return size; }
};





class MapCoordinates
{
    private:
        QPoint coordinates;
        
        
        
    public:
        MapCoordinates() : coordinates() {}
        MapCoordinates(int x, int y) : coordinates(x, y) {}
        
        bool operator== (const MapCoordinates& other) const;
        bool operator!= (const MapCoordinates& other) const;
        
        int getX() const;
        int getY() const;
};





class MapArea
{
    private:
        MapSize size;
        MapCoordinates left;
        MapCoordinates right;
        
        
        
    public:
        MapArea();
        MapArea(const MapCoordinates& left, const MapSize& size);
        
        const MapSize getSize() const;
        const MapCoordinates& getLeft() const;
        bool isInside(const MapCoordinates& coordinates) const;
};

#endif // MAPELEMENT_HPP
