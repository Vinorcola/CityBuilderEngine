#ifndef ITEMINFORMATION_HPP
#define ITEMINFORMATION_HPP

#include <QtCore/QObject>
#include <QtCore/QString>

namespace YAML {
    class Node;
}

class ItemInformation : public QObject
{
        Q_OBJECT

    private:
        QString key;
        QString title;

    public:
        ItemInformation(QObject* parent, const QString& key, const YAML::Node& model);

        const QString& getKey() const;

        const QString& getTitle() const;

        static void checkModel(const QString& key, const YAML::Node& model);
};

#endif // ITEMINFORMATION_HPP
