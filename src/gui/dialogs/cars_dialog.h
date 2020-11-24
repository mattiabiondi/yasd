#ifndef YASD_CARS_DIALOG_H
#define YASD_CARS_DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QSpinBox>

#include "../const.h"

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
QGroupBox *carsNoBox;
QSpinBox *typeASpinBox;
QSpinBox *typeBSpinBox;
QSpinBox *typeCSpinBox;
};

#endif // YASD_CARS_DIALOG_H
