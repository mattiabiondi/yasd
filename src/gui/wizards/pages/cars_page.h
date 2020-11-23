#ifndef YASD_CARS_PAGE_H
#define YASD_CARS_PAGE_H

#include <QWizardPage>
#include <QLabel>

#include "../new_wizard.h"
#include "../../widgets/cars_widget.h"

class CarsWizardPage : public QWizardPage
{
Q_OBJECT

public:
CarsWizardPage(QWidget *parent = nullptr);
int nextId() const override;

private:
CarsWidget *carsWidget;
};

#endif // YASD_CARS_PAGE_H
