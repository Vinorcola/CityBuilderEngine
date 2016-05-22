#include "MapScene.hpp"

#include <QDebug>



const QSizeF BASE_TILE_SIZE(58, 30);





MapScene::MapScene(const Map& map) :
    QGraphicsScene(),
    tileList()
{
    // Load the test images.
    QPixmap buildingImage("assets/img/building.png");
    QPixmap roadImage("assets/img/road");
    QPixmap grassImage("assets/img/grass.png");

    // Create the tiles and their graphics item.
    int x(0);
    int y(0);
    const QSize& mapSize(map.getSize());
    while (y + x < mapSize.width())
    {
        while (x <= y && y + x < mapSize.width())
        {
            Tile* tile(new Tile(MapCoordinates(x, y), BASE_TILE_SIZE, this));
            StaticElementGraphicsItem* graphicsItem(new StaticElementGraphicsItem(BASE_TILE_SIZE, MapSize(1), grassImage));
            tile->pushGraphicsItem(graphicsItem);

            addItem(graphicsItem);
            tileList.append(tile);

            ++x;
        }

        // Go to next line
        ++y;
        x = -y;
        if (y - x > mapSize.height() - 1)
        {
            x = -mapSize.height() + 1 + y;
        }
    }
}
