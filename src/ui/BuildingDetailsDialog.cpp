#include "BuildingDetailsDialog.hpp"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

#include "src/engine/state/BuildingState.hpp"
#include "src/global/conf/BuildingInformation.hpp"



BuildingDetailsDialog::BuildingDetailsDialog(const BuildingState& state) :
    QDialog()
{
    auto title(new QLabel(state.type.getTitle(), this));

    auto workers(new QLabel(this));
    if (state.type.getMaxWorkers() > 0) {
        workers->setText("Workers: " + QString::number(state.workers) + "/" + QString::number(state.type.getMaxWorkers()));
    }

    // Layout
    auto layout(new QVBoxLayout);
    layout->addWidget(title);
    layout->addWidget(workers);

    setLayout(layout);
    setMinimumHeight(120);
    setMinimumWidth(320);
}
