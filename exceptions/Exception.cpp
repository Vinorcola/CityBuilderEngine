#include "Exception.hpp"



Exception::Exception(const QString& message) :
    QException(),
    message(message)
{

}



const QString& Exception::getMessage() const
{
    return message;
}
