#ifndef SEARCHENGINE_HPP
#define SEARCHENGINE_HPP

#include <QtCore/QLinkedList>
#include <QtCore/QObject>

class Building;
class BuildingInformation;
class BuildingSearchCriteria;

/**
 * @brief The search engine fetch existing buildings according to criteria.
 */
class SearchEngine : public QObject
{
        Q_OBJECT

    private:
        const QLinkedList<Building*>& buildingList;

    public:
        SearchEngine(QObject* parent, const QLinkedList<Building*>& buildingList);

        /**
         * @brief Search a static element into the list of existing elements.
         */
        QList<Building*> search(const BuildingSearchCriteria& criteria) const;

    private:
        bool isBuildingTypeAllowedByCriteria(
            const BuildingInformation* buildingType,
            const BuildingSearchCriteria& criteria
        ) const;

        bool canBuildingAcceptCarriedItem(const Building* building, const BuildingSearchCriteria& criteria) const;
};

#endif // SEARCHENGINE_HPP
