#ifndef FILENOTFOUNDEXCEPTION_HPP
#define FILENOTFOUNDEXCEPTION_HPP

#include "src/exceptions/Exception.hpp"

class FileNotFoundException : public Exception
{
    public:
        FileNotFoundException(const QString& filePath);
};

#endif // FILENOTFOUNDEXCEPTION_HPP
