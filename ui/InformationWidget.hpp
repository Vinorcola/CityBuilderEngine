#ifndef INFORMATIONWIDGET_HPP
#define INFORMATIONWIDGET_HPP

#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

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

    public slots:
        void updateBudget(const int budget);

        void updatePopulation(const int population);

        void updateDate(const int year, const int month);

    private:
        QString resolveBudgetText();

        QString resolvePopulationText();

        QString resolveDateText();
};

#endif // INFORMATIONWIDGET_HPP
