#include "src/dialogs/cars_dialog.h"

CarsDialog::CarsDialog(Configuration *config, QWidget *parent)
	: QDialog(parent),
	config(config)
{
	setWindowTitle(tr("Cars preferences"));

	redSpinBox = new QSpinBox;
	redSpinBox->setRange(MINCARS, MAXCARS);
	redSpinBox->setValue(config->getRed());
	greenSpinBox = new QSpinBox;
	greenSpinBox->setRange(MINCARS, MAXCARS);
	greenSpinBox->setValue(config->getGreen());
	blueSpinBox = new QSpinBox;
	blueSpinBox->setRange(MINCARS, MAXCARS);
	blueSpinBox->setValue(config->getBlue());

	QFormLayout *formLayout = new QFormLayout;

	formLayout->addRow(tr("Red - Fast driver:"), redSpinBox);
	formLayout->addRow(tr("Green - Regular driver:"), greenSpinBox);
	formLayout->addRow(tr("Blue - Slow driver:"), blueSpinBox);

	QVBoxLayout *layout = new QVBoxLayout;

	carsBox = new QGroupBox(tr("Number of cars:"));
	carsBox->setLayout(formLayout);
	layout->addWidget(carsBox);

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
	config->setRed(redSpinBox->value());
	config->setGreen(greenSpinBox->value());
	config->setBlue(blueSpinBox->value());
}
