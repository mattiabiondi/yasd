#include "src/dialogs/cars_dialog.h"

CarsDialog::CarsDialog(Configuration *config, QWidget *parent)
	: QDialog(parent),
	config(config)
{
	setWindowTitle(tr("Cars preferences"));

	QVBoxLayout *layout = new QVBoxLayout;

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

	layout->addLayout(formLayout);

	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
					 | QDialogButtonBox::Cancel);

	connect(buttonBox, &QDialogButtonBox::accepted, this, &CarsDialog::saveConfig);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

	layout->addWidget(buttonBox);

	setLayout(layout);
}

void CarsDialog::saveConfig()
{
	// Note: at least two cars are needed for genetic algorithm
	if (redSpinBox->value() + greenSpinBox->value() + blueSpinBox->value() > 1) {
		config->setRed(redSpinBox->value());
		config->setGreen(greenSpinBox->value());
		config->setBlue(blueSpinBox->value());
		accept();
	} else {
		QMessageBox warning;
		warning.setIcon(QMessageBox::Warning);
		warning.setWindowTitle("Warning");
		warning.setText("At least two cars are needed for the genetic algorithm!");
		warning.exec();
	}
}
