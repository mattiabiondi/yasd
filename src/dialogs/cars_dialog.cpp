#include "src/dialogs/cars_dialog.h"

CarsDialog::CarsDialog(Configuration *config, QWidget *parent)
	: QDialog(parent),
	config(config)
{
	setWindowTitle(tr("Cars preferences"));

	typeASpinBox = new QSpinBox;
	typeASpinBox->setRange(MINCARS, MAXCARS);
	typeASpinBox->setValue(config->getTypeA());
	typeBSpinBox = new QSpinBox;
	typeBSpinBox->setRange(MINCARS, MAXCARS);
	typeBSpinBox->setValue(config->getTypeB());
	typeCSpinBox = new QSpinBox;
	typeCSpinBox->setRange(MINCARS, MAXCARS);
	typeCSpinBox->setValue(config->getTypeC());

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
	connect(buttonBox, &QDialogButtonBox::accepted, this, &CarsDialog::saveConfig);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

	layout->addWidget(buttonBox);

	setLayout(layout);
}

void CarsDialog::saveConfig()
{
	config->setTypeA(typeASpinBox->value());
	config->setTypeB(typeBSpinBox->value());
	config->setTypeC(typeCSpinBox->value());
}
