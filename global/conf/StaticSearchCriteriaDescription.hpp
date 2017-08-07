#ifndef STATICSEARCHCRITERIADESCRIPTION_HPP
#define STATICSEARCHCRITERIADESCRIPTION_HPP

#include <QtCore/QObject>
#include <yaml-cpp/node/node.h>

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
