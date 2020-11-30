#include "BuildingDetailsDialog.hpp"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

#include "src/engine/state/BuildingState.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/ItemInformation.hpp"



BuildingDetailsDialog::BuildingDetailsDialog(const BuildingState& state) :
    QDialog()
{
    auto title(new QLabel(state.type.getTitle(), this));

    auto workers(new QLabel(this));
    if (state.type.getMaxWorkers() > 0) {
        workers->setText("Workers: " + QString::number(state.workers) + "/" + QString::number(state.type.getMaxWorkers()));
    }

    auto specificDetails(new QLabel(this));
    if (state.producer) {
        specificDetails->setText("Stock: " + QString::number(state.producer->rawMaterialStock) + " " + state.type.getProducerConf().producedItemConf.getTitle());
    }
    else if (state.farm) {
        specificDetails->setText("Grownth: " + QString::number(state.farm->growthPercent) + "%");
    }

    // Layout
    auto layout(new QVBoxLayout);
    layout->addWidget(title);
    layout->addWidget(workers);
    layout->addWidget(specificDetails);

    setLayout(layout);
    setMinimumHeight(120);
    setMinimumWidth(320);
}
