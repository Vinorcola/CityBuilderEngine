#ifndef CONTROLPANELELEMENTINFORMATION_HPP
#define CONTROLPANELELEMENTINFORMATION_HPP

#include <QtCore/QObject>
#include <yaml-cpp/node/node.h>

class Conf;
class StaticElementInformation;

class ControlPanelElementInformation : public QObject
{
        Q_OBJECT

    public:
        enum class Type {
            Button,
            Panel,
        };

    private:
        Type type;
        QString title;
        const StaticElementInformation* staticElementConf;
        QList<ControlPanelElementInformation*> children;

    public:
        ControlPanelElementInformation(QObject* parent, Conf* conf, const YAML::Node& model);

        Type getType() const;

        const QString& getTitle() const;

        const StaticElementInformation* getStaticElementConf() const;

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
