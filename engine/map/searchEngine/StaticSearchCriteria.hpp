#ifndef STATICSEARCHCRITERIA_HPP
#define STATICSEARCHCRITERIA_HPP

class StaticElementInformation;

/**
 * @brief Criteria for searching a static element in the search engine.
 */
class StaticSearchCriteria
{
    private:
        const StaticElementInformation* elementConf;

    public:
        explicit StaticSearchCriteria(const StaticElementInformation* elementConf);

        const StaticElementInformation* getConf() const;
};

#endif // STATICSEARCHCRITERIA_HPP
