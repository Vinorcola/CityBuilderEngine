#include "SearchEngine.hpp"

#include "engine/element/static/Building.hpp"
#include "engine/map/searchEngine/BuildingSearchCriteria.hpp"



SearchEngine::SearchEngine(QObject* parent, const QLinkedList<Building*>& buildingList) :
    QObject(parent),
    buildingList(buildingList)
{

}



QList<Building*> SearchEngine::search(const BuildingSearchCriteria& criteria) const
{
    QList<Building*> results;
    for (auto building : buildingList) {
        if (building->getConf() == criteria.getConf()) {
            results.append(building);
        }
    }

    return results;
}
