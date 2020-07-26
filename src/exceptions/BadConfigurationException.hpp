#ifndef BADCONFIGURATIONEXCEPTION_HPP
#define BADCONFIGURATIONEXCEPTION_HPP

#include "src/exceptions/Exception.hpp"

class BadConfigurationException : public Exception
{
    public:
        BadConfigurationException(const QString& message);
};

#endif // BADCONFIGURATIONEXCEPTION_HPP
