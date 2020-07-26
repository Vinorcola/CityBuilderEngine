#include "Exception.hpp"



Exception::Exception(const QString& message) :
    QException(),
    message(message),
    stdMessage(message.toStdString())
{

}



const QString& Exception::getMessage() const
{
    return message;
}



const char* Exception::what() const noexcept
{
    return stdMessage.c_str();
}
