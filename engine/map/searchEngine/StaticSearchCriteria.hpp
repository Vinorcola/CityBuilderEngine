#ifndef STATICSEARCHCRITERIA_HPP
#define STATICSEARCHCRITERIA_HPP

class BuildingInformation;

/**
 * @brief Criteria for searching a static element in the search engine.
 */
class StaticSearchCriteria
{
    private:
        const BuildingInformation* elementConf;

    public:
        explicit StaticSearchCriteria(const BuildingInformation* elementConf);

        const BuildingInformation* getConf() const;
};

#endif // STATICSEARCHCRITERIA_HPP
