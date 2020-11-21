#ifndef CONTROLPANELELEMENTINFORMATION_HPP
#define CONTROLPANELELEMENTINFORMATION_HPP

#include <QtCore/QList>
#include <QtCore/QString>

#include "src/defines.hpp"

class Conf;
class BuildingInformation;
namespace YAML {
    class Node;
}

class ControlPanelElementInformation
{
        Q_DISABLE_COPY_MOVE(ControlPanelElementInformation)

    public:
        enum class Type {
            Button,
            Panel,
        };

    private:
        Type type;
        QString title;
        optional<const BuildingInformation*> staticElementConf;
        QList<owner<ControlPanelElementInformation*>> children;

    public:
        ControlPanelElementInformation(Conf& conf, const YAML::Node& model);
        ~ControlPanelElementInformation();

        Type getType() const;

        const QString& getTitle() const;

        const BuildingInformation& getStaticElementConf() const;

        const QList<ControlPanelElementInformation*>& getChildren() const;

        /**
         * @brief Check if the model for a control panel item is valid.
         *
         * If the model is invalid, it throws an exception.
         *
         * @param key
         * @param model
         * @throws BadConfigurationException
         */
        static void checkModel(const YAML::Node& model);

    private:
        static Type resolveType(const QString& type);
};

#endif // CONTROLPANELELEMENTINFORMATION_HPP
