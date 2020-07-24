#include "StaticSearchCriteria.hpp"

#include "global/conf/BuildingInformation.hpp"
#include "global/conf/Conf.hpp"



StaticSearchCriteria::StaticSearchCriteria(const BuildingInformation* staticElementConf) :
    elementConf(staticElementConf)
{

}



const BuildingInformation* StaticSearchCriteria::getConf() const
{
    return elementConf;
}
