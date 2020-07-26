#ifndef OUTOFRANGEEXCEPTION_HPP
#define OUTOFRANGEEXCEPTION_HPP

#include "src/exceptions/EngineException.hpp"

class OutOfRangeException : public EngineException
{
    public:
        OutOfRangeException(const QString& message);
};

#endif // OUTOFRANGEEXCEPTION_HPP
