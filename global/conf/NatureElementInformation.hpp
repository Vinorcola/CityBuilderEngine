#ifndef NATUREELEMENTINFORMATION_HPP
#define NATUREELEMENTINFORMATION_HPP

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtGui/QPixmap>

namespace YAML {
    class Node;
}

class NatureElementInformation : public QObject
{
        Q_OBJECT

    public:
        enum class Type {
            Copper,
            Silver,
            Wood
        };

    private:
        Type type;
        QString key;
        QString title;
        bool convertible;
        QPixmap image;

    public:
        NatureElementInformation(QObject* parent, const QString& key, const YAML::Node& model);

        /**
         * @brief Check if the model is valid.
         *
         * @throws BadConfigurationException The model is invalid.
         */
        static void checkModel(const QString& key, const YAML::Node& model);

        const QPixmap& getImage() const;

    private:
        static Type resolveType(const QString& type);
};

#endif // NATUREELEMENTINFORMATION_HPP
