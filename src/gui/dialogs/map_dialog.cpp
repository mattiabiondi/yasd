#include "map_dialog.h"

MapDialog::MapDialog(Configuration *config, QWidget *parent)
	: QDialog(parent),
	config(config)
{
	setWindowTitle(tr("Map preferences"));

	QVBoxLayout *layout = new QVBoxLayout;

	crossroadsNoSpinBox = new QSpinBox;
	crossroadsNoSpinBox->setRange(MINCROSSROADS, MAXCROSSROADS);
	crossroadsNoSpinBox->setValue(config->getCrossroads());
	speedLimitSpinBox = new QSpinBox;
	speedLimitSpinBox->setRange(MINSPEEDLIMIT, MAXSPEEDLIMIT);
	speedLimitSpinBox->setSuffix(" km/h");
	speedLimitSpinBox->setValue(config->getSpeedLimit());
	frictionComboBox = new QComboBox;
	frictionComboBox->addItem(QString("Asphalt (clean and dry) - %1").arg(FRICTIONASPHALT));
	frictionComboBox->addItem(QString("Grass (clean and dry) - %1").arg(FRICTIONGRASS));
	frictionComboBox->setCurrentIndex(config->getFriction());

	QFormLayout *formLayout = new QFormLayout;

	formLayout->addRow(tr("No. of crossroads:"), crossroadsNoSpinBox);
	formLayout->addRow(tr("Speed limit:"), speedLimitSpinBox);
	formLayout->addRow(tr("Coefficient of friction:"), frictionComboBox);

	layout->addLayout(formLayout);

	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
					 | QDialogButtonBox::Cancel);
	connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::accepted, this, &MapDialog::saveConfig);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

	layout->addWidget(buttonBox);

	setLayout(layout);
}

void MapDialog::saveConfig()
{
	config->setCrossroads(crossroadsNoSpinBox->value());
	config->setSpeedLimit(speedLimitSpinBox->value());
	config->setFriction(frictionComboBox->currentIndex());
}
