#include "AbstractProcessable.hpp"





AbstractProcessable::AbstractProcessable(TimeCycleProcessor& processor) :
    processor(processor)
{
    processor.registerProcessable(this);
}





AbstractProcessable::~AbstractProcessable()
{
    processor.unregisterProcessable(this);
}
