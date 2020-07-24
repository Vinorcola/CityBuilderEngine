#include "BuildingSearchCriteria.hpp"

#include "global/conf/BuildingInformation.hpp"
#include "global/conf/Conf.hpp"



BuildingSearchCriteria::BuildingSearchCriteria(const BuildingInformation* conf) :
    conf(conf)
{

}



const BuildingInformation* BuildingSearchCriteria::getConf() const
{
    return conf;
}
