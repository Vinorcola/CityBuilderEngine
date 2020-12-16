#ifndef TILEAREASIZE_HPP
#define TILEAREASIZE_HPP

class QString;

class TileAreaSize
{
    public:
        TileAreaSize(int width);
        TileAreaSize(int width, int height);

        bool isSquare() const;
        int width() const;
        int height() const;

        QString toString() const;

    private:
        int _width;
        int _height;
};

#endif // TILEAREASIZE_HPP
