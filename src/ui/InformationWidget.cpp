#include "InformationWidget.hpp"

#include <QtWidgets/QHBoxLayout>

const int LABEL_WIDTH(120);



InformationWidget::InformationWidget(
    QWidget* parent,
    const int budget,
    const int population,
    const int year,
    const int month
) :
    QWidget(parent),
    budget(budget),
    population(population),
    year(year),
    month(month),
    budgetLabel(new QLabel(resolveBudgetText(), this)),
    populationLabel(new QLabel(resolvePopulationText(), this)),
    clockLabel(new QLabel(resolveDateText(), this))
{
    auto layout(new QHBoxLayout(this));

    budgetLabel->setMinimumWidth(LABEL_WIDTH);
    layout->addWidget(budgetLabel);

    populationLabel->setMinimumWidth(LABEL_WIDTH);
    layout->addWidget(populationLabel);

    clockLabel->setMinimumWidth(LABEL_WIDTH);
    layout->addWidget(clockLabel);
    setLayout(layout);
}



void InformationWidget::updateState(const CityState& state)
{
    if (state.budget != budget) {
        budget = state.budget;
        budgetLabel->setText(resolveBudgetText());
    }
    if (state.population != population) {
        population = state.population;
        populationLabel->setText(resolvePopulationText());
    }
    if (state.date.year != year || state.date.month != month) {
        year = state.date.year;
        month = state.date.month;
        clockLabel->setText(resolveDateText());
    }
}



QString InformationWidget::resolveBudgetText()
{
    return "$: " + QString::number(budget);
}



QString InformationWidget::resolvePopulationText()
{
    return "Pop: " + QString::number(population);
}



const QString MONTH_TEXTS[13] = {
    QString(), // Unused
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sep",
    "Oct",
    "Nov",
    "Dec"
};

QString InformationWidget::resolveDateText()
{
    if (year < 0) {
        return MONTH_TEXTS[month] + ' ' + QString::number(-year) + " BC";
    }
    else {
        return MONTH_TEXTS[month] + ' ' + QString::number(year);
    }
}
