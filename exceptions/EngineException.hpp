#ifndef ENGINEEXCEPTION_HPP
#define ENGINEEXCEPTION_HPP

#include "exceptions/Exception.hpp"





class EngineException : public Exception
{
    public:
        EngineException(const QString& message);
};

#endif // ENGINEEXCEPTION_HPP
