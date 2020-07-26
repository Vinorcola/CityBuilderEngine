#ifndef ENGINEEXCEPTION_HPP
#define ENGINEEXCEPTION_HPP

#include "src/exceptions/Exception.hpp"

class EngineException : public Exception
{
    public:
        EngineException(const QString& message);
};

#endif // ENGINEEXCEPTION_HPP
