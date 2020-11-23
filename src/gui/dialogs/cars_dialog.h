#ifndef YASD_CARS_DIALOG_H
#define YASD_CARS_DIALOG_H

#include <QDialog>

#include "../widgets/cars_widget.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
QT_END_NAMESPACE

class CarsDialog : public QDialog
{
Q_OBJECT

public:
CarsDialog(QWidget *parent = nullptr);

private:
QDialogButtonBox *buttonBox;
CarsWidget *carsWidget;
};

#endif // YASD_CARS_DIALOG_H
