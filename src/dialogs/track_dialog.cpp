#include "src/dialogs/track_dialog.h"

TrackDialog::TrackDialog(Configuration *config, QWidget *parent)
	: QDialog(parent),
	config(config)
{
	setWindowTitle(tr("Track preferences"));

	QVBoxLayout *layout = new QVBoxLayout;

	crossroadsSpinBox = new QSpinBox;
	crossroadsSpinBox->setRange(MINCROSSROADS, MAXCROSSROADS);
	crossroadsSpinBox->setValue(config->getCrossroads());
	limitSpinBox = new QSpinBox;
	limitSpinBox->setRange(MINSPEEDLIMIT, MAXSPEEDLIMIT);
	limitSpinBox->setSuffix(" km/h");
	limitSpinBox->setValue(config->getLimit());
	frictionComboBox = new QComboBox;
	frictionComboBox->addItem(QString("Asphalt (clean and dry) - %1").arg(FRICTIONASPHALT));
	frictionComboBox->addItem(QString("Grass (clean and dry) - %1").arg(FRICTIONGRASS));
	frictionComboBox->setCurrentIndex(config->getFriction());

	QFormLayout *formLayout = new QFormLayout;

	formLayout->addRow(tr("No. of crossroads:"), crossroadsSpinBox);
	formLayout->addRow(tr("Speed limit:"), limitSpinBox);
	formLayout->addRow(tr("Coefficient of friction:"), frictionComboBox);

	layout->addLayout(formLayout);

	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
					 | QDialogButtonBox::Cancel);
	connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::accepted, this, &TrackDialog::saveConfig);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

	layout->addWidget(buttonBox);

	setLayout(layout);
}

void TrackDialog::saveConfig()
{
	config->setCrossroads(crossroadsSpinBox->value());
	config->setLimit(limitSpinBox->value());
	config->setFriction(frictionComboBox->currentIndex());
}
