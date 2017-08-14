#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <QtCore/QException>

class Exception : public QException
{
    private:
        QString message;
        std::string stdMessage;

    public:
        Exception(const QString& message);

        const QString& getMessage() const;

        virtual const char* what() const noexcept override;
};

#endif // EXCEPTION_HPP
