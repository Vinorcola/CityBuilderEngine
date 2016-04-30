#include "EngineException.hpp"





EngineException::EngineException(const QString& message) :
    QException(),
    message(message)
{
    
}





const QString& EngineException::getMessage() const
{
    return message;
}
