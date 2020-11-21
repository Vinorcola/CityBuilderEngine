#ifndef ITEMINFORMATION_HPP
#define ITEMINFORMATION_HPP

#include <QtCore/QString>

namespace YAML {
    class Node;
}

class ItemInformation
{
        Q_DISABLE_COPY_MOVE(ItemInformation)

    private:
        QString key;
        QString title;

    public:
        ItemInformation(const QString& key, const YAML::Node& model);

        const QString& getKey() const;

        const QString& getTitle() const;

        static void checkModel(const QString& key, const YAML::Node& model);
};

#endif // ITEMINFORMATION_HPP
