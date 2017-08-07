#include "StaticSearchCriteria.hpp"

#include "global/conf/Conf.hpp"
#include "global/conf/StaticElementInformation.hpp"



StaticSearchCriteria::StaticSearchCriteria(const StaticElementInformation* staticElementConf) :
    elementConf(staticElementConf)
{

}



const StaticElementInformation* StaticSearchCriteria::getConf() const
{
    return elementConf;
}
