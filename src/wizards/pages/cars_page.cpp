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

	registerField("red", redSpinBox);
	registerField("green", greenSpinBox);
	registerField("blue", blueSpinBox);

	QFormLayout *formLayout = new QFormLayout;

	formLayout->addRow(tr("Red - Fast driver:"), redSpinBox);
	formLayout->addRow(tr("Green - Regular driver:"), greenSpinBox);
	formLayout->addRow(tr("Blue - Slow driver:"), blueSpinBox);

	setLayout(formLayout);

	connect(redSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		this, &QWizardPage::completeChanged);
	connect(greenSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		this, &QWizardPage::completeChanged);
	connect(blueSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		this, &QWizardPage::completeChanged);
}

bool CarsWizardPage::isComplete() const
{
	// Note: at least two cars are needed for genetic algorithm
	// TODO: future works --> RL if only one car
	return (field("red").toInt() + field("green").toInt() + field("blue").toInt()) > 1;
}
