#include <QCoreApplication>

#include "engine/Map.hpp"





int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    
    Map map({ 30, 30 });
    
    return a.exec();
}
