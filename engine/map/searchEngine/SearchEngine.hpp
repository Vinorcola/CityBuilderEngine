#ifndef SEARCHENGINE_HPP
#define SEARCHENGINE_HPP

#include <QtCore/QLinkedList>
#include <QtCore/QObject>

#include "engine/element/static/AbstractStaticMapElement.hpp"
#include "engine/map/searchEngine/StaticSearchCriteria.hpp"

/**
 * @brief The search engine fetch existing static elements according to criteria.
 */
class SearchEngine : public QObject
{
        Q_OBJECT

    private:
        const QLinkedList<AbstractStaticMapElement*>& staticElements;

    public:
        SearchEngine(QObject* parent, const QLinkedList<AbstractStaticMapElement*>& staticElements);

        /**
         * @brief Search a static element into the list of existing elements.
         */
        QList<AbstractStaticMapElement*> search(const StaticSearchCriteria& criteria) const;
};

#endif // SEARCHENGINE_HPP
