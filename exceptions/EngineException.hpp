#ifndef ENGINEEXCEPTION_HPP
#define ENGINEEXCEPTION_HPP


#include <QException>




class EngineException : public QException
{
    private:
        QString message;
        
        
        
    public:
        EngineException(const QString& message);
        
        
        
        const QString& getMessage() const;
};

#endif // ENGINEEXCEPTION_HPP
