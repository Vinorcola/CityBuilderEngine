#ifndef STATICSEARCHCRITERIADESCRIPTION_HPP
#define STATICSEARCHCRITERIADESCRIPTION_HPP

#include <QtCore/QObject>
#include <QtCore/QString>

namespace YAML {
    class Node;
}

/**
 * @brief This class contains information to construct a StaticSearchCriteria object.
 */
class StaticSearchCriteriaDescription : public QObject
{
        Q_OBJECT

    private:
        QString targetKey;

    public:
        StaticSearchCriteriaDescription(QObject* parent, const YAML::Node& model);

        const QString& getTargetKey() const;
};

#endif // STATICSEARCHCRITERIADESCRIPTION_HPP
