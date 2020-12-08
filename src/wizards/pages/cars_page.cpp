#include "cars_page.h"

CarsWizardPage::CarsWizardPage(QWidget *parent)
{
	setTitle(tr("Cars preferences"));
	setSubTitle(tr("Specify preferences about the set of cars.<br>"
		       "You can change them up until the first run."));

	redSpinBox = new QSpinBox;
	redSpinBox->setRange(MINCARS, MAXCARS);
	greenSpinBox = new QSpinBox;
	greenSpinBox->setRange(MINCARS, MAXCARS);
	blueSpinBox = new QSpinBox;
	blueSpinBox->setRange(MINCARS, MAXCARS);

	QFormLayout *formLayout = new QFormLayout;

	formLayout->addRow(tr("Red - Fast driver:"), redSpinBox);
	formLayout->addRow(tr("Green - Regular driver:"), greenSpinBox);
	formLayout->addRow(tr("Blue - Slow driver:"), blueSpinBox);

	carsNoBox = new QGroupBox(tr("Number of cars:"));
	carsNoBox->setLayout(formLayout);

	registerField("redNo", redSpinBox);
	registerField("greenNo", greenSpinBox);
	registerField("blueNo", blueSpinBox);

	QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget(carsNoBox);
	setLayout(layout);

	connect(redSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		this, &QWizardPage::completeChanged);
	connect(greenSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		this, &QWizardPage::completeChanged);
	connect(blueSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		this, &QWizardPage::completeChanged);
}

bool CarsWizardPage::isComplete() const
{
	return field("redNo").toInt() +
	       field("greenNo").toInt() +
	       field("blueNo").toInt();
}
