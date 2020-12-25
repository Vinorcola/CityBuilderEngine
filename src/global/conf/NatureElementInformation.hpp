#ifndef NATUREELEMENTINFORMATION_HPP
#define NATUREELEMENTINFORMATION_HPP

#include <QtCore/QString>

namespace YAML {
    class Node;
}

class NatureElementInformation
{
    public:
        enum class Type {
            Copper,
            Grass,
            Quarry,
            Silver,
            Wood,
        };

    private:
        Type type;
        QString key;
        QString title;
        bool traversable;
        QString imagePath;

    public:
        NatureElementInformation(const QString& configDirectoryPath, const QString& key, const YAML::Node& model);

        const QString& getTitle() const;

        bool isTraversable() const;

        const QString& getImagePath() const;

        /**
         * @brief Check if the model is valid.
         *
         * @throws BadConfigurationException The model is invalid.
         */
        static void checkModel(const QString& key, const YAML::Node& model);

    private:
        static Type resolveType(const QString& type);
};

#endif // NATUREELEMENTINFORMATION_HPP
