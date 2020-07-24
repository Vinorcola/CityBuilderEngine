#include "SearchEngine.hpp"

#include "engine/element/static/Building.hpp"
#include "engine/map/searchEngine/StaticSearchCriteria.hpp"



SearchEngine::SearchEngine(QObject* parent, const QLinkedList<Building*>& staticElements) :
    QObject(parent),
    staticElements(staticElements)
{

}



QList<Building*> SearchEngine::search(const StaticSearchCriteria& criteria) const
{
    QList<Building*> results;
    for (auto element : staticElements) {
        if (element->getConf() == criteria.getConf()) {
            results.append(element);
        }
    }

    return results;
}
