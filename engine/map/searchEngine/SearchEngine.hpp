#ifndef SEARCHENGINE_HPP
#define SEARCHENGINE_HPP

#include <list>
#include <QtCore/QList>

class AbstractStaticMapElement;
class StaticSearchCriteria;

/**
 * @brief The search engine fetch existing static elements according to criteria.
 */
class SearchEngine
{
    private:
        const std::list<AbstractStaticMapElement*>& staticElements;

    public:
        SearchEngine(const std::list<AbstractStaticMapElement*>& staticElements);

        /**
         * @brief Search a static element into the list of existing elements.
         */
        QList<AbstractStaticMapElement*> search(const StaticSearchCriteria& criteria) const;
};

#endif // SEARCHENGINE_HPP
