#include <QtWidgets>

#include "cars_dialog.h"

CarsDialog::CarsDialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle(tr("Cars preferences"));

	typeASpinBox = new QSpinBox;
	typeASpinBox->setRange(MINCARS, MAXCARS);
	typeBSpinBox = new QSpinBox;
	typeBSpinBox->setRange(MINCARS, MAXCARS);
	typeCSpinBox = new QSpinBox;
	typeCSpinBox->setRange(MINCARS, MAXCARS);

	QFormLayout *formLayout = new QFormLayout;
	formLayout->addRow(tr("Type &A - Regular driver:"), typeASpinBox);
	formLayout->addRow(tr("Type &B - Fast driver:"), typeBSpinBox);
	formLayout->addRow(tr("Type &C - Slow driver:"), typeCSpinBox);

	QVBoxLayout *layout = new QVBoxLayout;

	carsNoBox = new QGroupBox(tr("Number of cars:"));
	carsNoBox->setLayout(formLayout);
	layout->addWidget(carsNoBox);

	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
					 | QDialogButtonBox::Cancel);
	connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

	layout->addWidget(buttonBox);

	setLayout(layout);
}
