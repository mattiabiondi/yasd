#include "cars_widget.h"

CarsWidget::CarsWidget(QWidget *parent)
	: QWidget(parent)
{
	typeASpinBox = new QSpinBox;
	typeASpinBox->setRange(MinCarsNo, MaxCarsNo);
	typeASpinBox->setMinimumWidth(150);
	typeBSpinBox = new QSpinBox;
	typeBSpinBox->setRange(MinCarsNo, MaxCarsNo);
	typeBSpinBox->setMinimumWidth(150);
	typeCSpinBox = new QSpinBox;
	typeCSpinBox->setRange(MinCarsNo, MaxCarsNo);
	typeCSpinBox->setMinimumWidth(150);

	QFormLayout *formLayout = new QFormLayout;

	formLayout->addRow(tr("Type &A - Regular driver:"), typeASpinBox);
	formLayout->addRow(tr("Type &B - Fast driver:"), typeBSpinBox);
	formLayout->addRow(tr("Type &C - Slow driver:"), typeCSpinBox);

	carsNoBox = new QGroupBox(tr("Number of cars:"));
	carsNoBox->setLayout(formLayout);

	QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget(carsNoBox);
	setLayout(layout);
}
