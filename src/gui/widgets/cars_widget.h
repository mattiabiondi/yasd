#ifndef YASD_CARS_WIDGET_H
#define YASD_CARS_WIDGET_H

#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QSpinBox>

class CarsWidget : public QWidget
{
Q_OBJECT

public:
CarsWidget(QWidget *parent = nullptr);

private:
enum { MinCarsNo = 0, MaxCarsNo = 10 };

QGroupBox *carsNoBox;
QSpinBox *typeASpinBox;
QSpinBox *typeBSpinBox;
QSpinBox *typeCSpinBox;
};

#endif // YASD_CARS_WIDGET_H
