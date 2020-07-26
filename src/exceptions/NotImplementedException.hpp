#ifndef NOTIMPLEMENTEDEXCEPTION_HPP
#define NOTIMPLEMENTEDEXCEPTION_HPP

#include "src/exceptions/Exception.hpp"

class NotImplementedException : public Exception
{
    public:
        NotImplementedException();
};

#endif // NOTIMPLEMENTEDEXCEPTION_HPP
