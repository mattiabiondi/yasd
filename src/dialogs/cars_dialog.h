#ifndef YASD_CARS_DIALOG_H
#define YASD_CARS_DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QSpinBox>
#include <QDialogButtonBox>

#include "src/configuration.h"
#include "src/const.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
QT_END_NAMESPACE

class CarsDialog : public QDialog
{
Q_OBJECT

public:
CarsDialog(Configuration *config, QWidget *parent = nullptr);

private:
Configuration *const config;

QDialogButtonBox *buttonBox;
QGroupBox *carsNoBox;
QSpinBox *typeASpinBox;
QSpinBox *typeBSpinBox;
QSpinBox *typeCSpinBox;

private slots:
void saveConfig();
};

#endif // YASD_CARS_DIALOG_H
