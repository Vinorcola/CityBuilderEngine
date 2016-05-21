#ifndef UNEXPECTEDEXCEPTION_HPP
#define UNEXPECTEDEXCEPTION_HPP

#include "exceptions/EngineException.hpp"





class UnexpectedException : public EngineException
{
    public:
        UnexpectedException(const QString& message);
};

#endif // UNEXPECTEDEXCEPTION_HPP
