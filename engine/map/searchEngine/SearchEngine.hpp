#ifndef SEARCHENGINE_HPP
#define SEARCHENGINE_HPP

#include <QtCore/QLinkedList>

class AbstractStaticMapElement;
class StaticSearchCriteria;

/**
 * @brief The search engine fetch existing static elements according to criteria.
 */
class SearchEngine
{
    private:
        const QLinkedList<AbstractStaticMapElement*>& staticElements;

    public:
        SearchEngine(const QLinkedList<AbstractStaticMapElement*>& staticElements);

        /**
         * @brief Search a static element into the list of existing elements.
         */
        QList<AbstractStaticMapElement*> search(const StaticSearchCriteria& criteria) const;
};

#endif // SEARCHENGINE_HPP
