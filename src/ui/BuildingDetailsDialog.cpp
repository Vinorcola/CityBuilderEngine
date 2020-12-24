#include "BuildingDetailsDialog.hpp"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/ItemInformation.hpp"
#include "src/global/state/BuildingState.hpp"



BuildingDetailsDialog::BuildingDetailsDialog(const BuildingState& state) :
    QDialog()
{
    auto title(new QLabel(state.type.getTitle(), this));

    auto workers(new QLabel(this));
    if (state.type.getMaxWorkers() > 0) {
        workers->setText("Workers: " + QString::number(state.workers) + "/" + QString::number(state.type.getMaxWorkers()));
    }

    auto stockDetails(new QLabel(this));
    auto productionDetails(new QLabel(this));
    if (state.farm) {
        productionDetails->setText("Growth: " + QString::number(state.farm->growthPercent) + "%");
    }
    else if (state.industrial) {
        stockDetails->setText("Stock: " + QString::number(state.industrial->rawMaterialStock) + " " + state.type.getIndustrialConf().rawMaterialConf.getTitle());
        productionDetails->setText("Production: " + QString::number(state.industrial->productionPercent) + "%");
    }
    else if (state.producer) {
        stockDetails->setText("Stock: " + QString::number(state.producer->rawMaterialStock) + " " + state.type.getProducerConf().producedItemConf.getTitle());
    }

    // Layout
    auto layout(new QVBoxLayout);
    layout->addWidget(title);
    layout->addWidget(workers);
    layout->addWidget(stockDetails);
    layout->addWidget(productionDetails);

    setLayout(layout);
    setMinimumHeight(120);
    setMinimumWidth(320);
}
