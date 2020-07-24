#ifndef SEARCHENGINE_HPP
#define SEARCHENGINE_HPP

#include <QtCore/QLinkedList>
#include <QtCore/QObject>

class Building;
class StaticSearchCriteria;

/**
 * @brief The search engine fetch existing static elements according to criteria.
 */
class SearchEngine : public QObject
{
        Q_OBJECT

    private:
        const QLinkedList<Building*>& staticElements;

    public:
        SearchEngine(QObject* parent, const QLinkedList<Building*>& staticElements);

        /**
         * @brief Search a static element into the list of existing elements.
         */
        QList<Building*> search(const StaticSearchCriteria& criteria) const;
};

#endif // SEARCHENGINE_HPP
