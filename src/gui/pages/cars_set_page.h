#ifndef YASD_CARS_SET_PAGE_H
#define YASD_CARS_SET_PAGE_H

#include <QtWidgets/QWizardPage>
#include <QtWidgets/QLabel>

class CarsSetPage : public QWidget
{
Q_OBJECT

public:
CarsSetPage(QWidget *parent = nullptr);

private:
QLabel *label;
};

#endif // YASD_CARS_SET_PAGE_H
