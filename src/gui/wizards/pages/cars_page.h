#ifndef YASD_CARS_PAGE_H
#define YASD_CARS_PAGE_H

#include <QWizardPage>
#include <QVBoxLayout>
#include <QLabel>

#include "../new_wizard.h"

class CarsSetWizardPage : public QWizardPage
{
Q_OBJECT

public:
CarsSetWizardPage(QWidget *parent = nullptr);
int nextId() const override;
private:
};

#endif // YASD_CARS_PAGE_H
