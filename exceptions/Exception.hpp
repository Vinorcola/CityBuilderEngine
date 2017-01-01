#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <QException>





class Exception : public QException
{
    private:
        QString message;



    public:
        Exception(const QString& message);



        const QString& getMessage() const;
};

#endif // EXCEPTION_HPP
