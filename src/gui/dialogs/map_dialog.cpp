#include "map_dialog.h"

MapDialog::MapDialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle(tr("Map preferences"));

	QVBoxLayout *layout = new QVBoxLayout;

	crossroadsNoSpinBox = new QSpinBox;
	crossroadsNoSpinBox->setRange(MINCROSSROADS, MAXCROSSROADS);
	speedLimitSpinBox = new QSpinBox;
	speedLimitSpinBox->setRange(MINSPEEDLIMIT, MAXSPEEDLIMIT);
	speedLimitSpinBox->setSuffix(" km/h");
	frictionComboBox = new QComboBox;
	frictionComboBox->addItem(QString("Asphalt (clean and dry) - 0.%1").arg(FRICTIONASPHALT));
	frictionComboBox->addItem(QString("Grass (clean and dry) - 0.%1").arg(FRICTIONGRASS));

	QFormLayout *formLayout = new QFormLayout;

	formLayout->addRow(tr("No. of crossroads:"), crossroadsNoSpinBox);
	formLayout->addRow(tr("Speed limit:"), speedLimitSpinBox);
	formLayout->addRow(tr("Coefficient of friction:"), frictionComboBox);

	layout->addLayout(formLayout);

	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
					 | QDialogButtonBox::Cancel);
	connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

	layout->addWidget(buttonBox);

	setLayout(layout);
}
