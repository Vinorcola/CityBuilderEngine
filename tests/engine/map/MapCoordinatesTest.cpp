#include <QtTest>

#include "engine/map/MapCoordinates.cpp"
#include "exceptions/EngineException.cpp"
#include "exceptions/Exception.cpp"
#include "exceptions/UnexpectedException.cpp"

class MapCoordinatesTest : public QObject
{
        Q_OBJECT

    private slots:
        void test_get_north_coordinates_with_rounded_coordinates()
        {
            // Given
            MapCoordinates origin(2.0, 6.0);

            // When
            auto north(origin.getNorth());

            // Then
            QCOMPARE(north.getX(), 2.0);
            QCOMPARE(north.getY(), 5.0);
        }



        void test_get_east_coordinates_with_rounded_coordinates()
        {
            // Given
            MapCoordinates origin(2.0, 6.0);

            // When
            auto north(origin.getEast());

            // Then
            QCOMPARE(north.getX(), 3.0);
            QCOMPARE(north.getY(), 6.0);
        }



        void test_get_south_coordinates_with_rounded_coordinates()
        {
            // Given
            MapCoordinates origin(2.0, 6.0);

            // When
            auto north(origin.getSouth());

            // Then
            QCOMPARE(north.getX(), 2.0);
            QCOMPARE(north.getY(), 7.0);
        }



        void test_get_west_coordinates_with_rounded_coordinates()
        {
            // Given
            MapCoordinates origin(2.0, 6.0);

            // When
            auto north(origin.getWest());

            // Then
            QCOMPARE(north.getX(), 1.0);
            QCOMPARE(north.getY(), 6.0);
        }
};

QTEST_MAIN(MapCoordinatesTest)
#include "MapCoordinatesTest.moc"
