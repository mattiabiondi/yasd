#include "map_page.h"

MapWizardPage::MapWizardPage(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle(tr("Map preferences"));
	setSubTitle(tr("Specify preferences about the map.<br>"
		       "You can change them later."));

	crossroadsNoSpinBox = new QSpinBox;
	crossroadsNoSpinBox->setRange(MINCROSSROADS, MAXCROSSROADS);
	speedLimitSpinBox = new QSpinBox;
	speedLimitSpinBox->setRange(MINSPEEDLIMIT, MAXSPEEDLIMIT);
	speedLimitSpinBox->setSuffix(" km/h");
	frictionComboBox = new QComboBox;
	frictionComboBox->addItem(QString("Asphalt (clean and dry) - 0.%1").arg(FRICTIONASPHALT));
	frictionComboBox->addItem(QString("Grass (clean and dry) - 0.%1").arg(FRICTIONGRASS));

	registerField("crossroadsNo", crossroadsNoSpinBox);
	registerField("speedLimit", speedLimitSpinBox);
	registerField("friction", frictionComboBox);

	QFormLayout *formLayout = new QFormLayout;
	formLayout->addRow(tr("No. of crossroads:"), crossroadsNoSpinBox);
	formLayout->addRow(tr("Speed limit:"), speedLimitSpinBox);
	formLayout->addRow(tr("Coefficient of friction:"), frictionComboBox);
	setLayout(formLayout);
}

void MapWizardPage::initializePage()
{
	speedLimitSpinBox->setValue(DEFAULTSPEEDLIMIT);
}
