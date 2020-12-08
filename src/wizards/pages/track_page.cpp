#include "track_page.h"

TrackWizardPage::TrackWizardPage(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle(tr("Track preferences"));
	setSubTitle(tr("Specify preferences about the track.<br>"
		       "You can change them later."));

	crossroadsSpinBox = new QSpinBox;
	crossroadsSpinBox->setRange(MINCROSSROADS, MAXCROSSROADS);
	limitSpinBox = new QSpinBox;
	limitSpinBox->setRange(MINSPEEDLIMIT, MAXSPEEDLIMIT);
	limitSpinBox->setSuffix(" km/h");
	frictionComboBox = new QComboBox;
	frictionComboBox->addItem(QString("Asphalt (clean and dry) - %1").arg(FRICTIONASPHALT));
	frictionComboBox->addItem(QString("Grass (clean and dry) - %1").arg(FRICTIONGRASS));

	registerField("crossroads", crossroadsSpinBox);
	registerField("limit", limitSpinBox);
	registerField("friction", frictionComboBox);

	QFormLayout *formLayout = new QFormLayout;

	formLayout->addRow(tr("No. of crossroads:"), crossroadsSpinBox);
	formLayout->addRow(tr("Speed limit:"), limitSpinBox);
	formLayout->addRow(tr("Coefficient of friction:"), frictionComboBox);
	setLayout(formLayout);
}

void TrackWizardPage::initializePage()
{
	limitSpinBox->setValue(DEFAULTSPEEDLIMIT);
}
