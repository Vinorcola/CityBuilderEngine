#ifndef MAPSIZE_HPP
#define MAPSIZE_HPP





class MapSize
{
    private:
        int value;



    public:
        MapSize();
        explicit MapSize(const int value);



        int getValue() const;
};

#endif // MAPSIZE_HPP
