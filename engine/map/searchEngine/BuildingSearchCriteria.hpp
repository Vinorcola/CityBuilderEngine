#ifndef STATICSEARCHCRITERIA_HPP
#define STATICSEARCHCRITERIA_HPP

class BuildingInformation;

/**
 * @brief Criteria for searching a building in the search engine.
 */
class BuildingSearchCriteria
{
    private:
        const BuildingInformation* conf;

    public:
        explicit BuildingSearchCriteria(const BuildingInformation* conf);

        const BuildingInformation* getConf() const;
};

#endif // STATICSEARCHCRITERIA_HPP
