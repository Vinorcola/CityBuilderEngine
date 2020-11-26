#ifndef BUILDINGDETAILSDIALOG_HPP
#define BUILDINGDETAILSDIALOG_HPP

#include <QtWidgets/QDialog>

struct BuildingState;

class BuildingDetailsDialog : public QDialog
{
        Q_OBJECT

    public:
        BuildingDetailsDialog(const BuildingState& state);
};

#endif // BUILDINGDETAILSDIALOG_HPP
