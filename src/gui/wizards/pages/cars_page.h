#ifndef YASD_CARS_PAGE_H
#define YASD_CARS_PAGE_H

#include <QWizardPage>
#include <QGroupBox>
#include <QSpinBox>

#include "../new_wizard.h"
#include "../../const.h"

class CarsWizardPage : public QWizardPage
{
Q_OBJECT

public:
CarsWizardPage(QWidget *parent = nullptr);

protected:
bool isComplete() const override;

private:
QGroupBox *carsNoBox;
QSpinBox *typeASpinBox;
QSpinBox *typeBSpinBox;
QSpinBox *typeCSpinBox;
};

#endif // YASD_CARS_PAGE_H
