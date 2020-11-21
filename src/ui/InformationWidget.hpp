#ifndef INFORMATIONWIDGET_HPP
#define INFORMATIONWIDGET_HPP

#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

#include "src/engine/state/CityState.hpp"

class InformationWidget : public QWidget
{
        Q_OBJECT

    private:
        int budget;
        int population;
        int year;
        int month;
        QLabel* budgetLabel;
        QLabel* populationLabel;
        QLabel* clockLabel;

    public:
        InformationWidget(
            QWidget* parent,
            const int budget = 0,
            const int population = 0,
            const int year = 0,
            const int month = 1
        );

        void updateState(const CityState& state);

    private:
        QString resolveBudgetText();

        QString resolvePopulationText();

        QString resolveDateText();
};

#endif // INFORMATIONWIDGET_HPP
