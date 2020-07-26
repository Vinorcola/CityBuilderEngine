#ifndef BUILDINGSEARCHCRITERIA_HPP
#define BUILDINGSEARCHCRITERIA_HPP

#include <QtCore/QList>

class BuildingInformation;
class ItemInformation;

/**
 * @brief Criteria for searching a building in the search engine.
 */
class BuildingSearchCriteria
{
    private:
        QList<const BuildingInformation*> allowedBuildingTypes;
        const ItemInformation* acceptingItem;

    public:
        explicit BuildingSearchCriteria(
            const QList<const BuildingInformation*>& allowedBuildingTypes,
            const ItemInformation* acceptingItem = nullptr
        );

        const QList<const BuildingInformation*>& getAllowedBuildingTypes() const;

        const ItemInformation* getAcceptingItem() const;
};

#endif // BUILDINGSEARCHCRITERIA_HPP
