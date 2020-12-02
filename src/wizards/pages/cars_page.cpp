#include "cars_page.h"

CarsWizardPage::CarsWizardPage(QWidget *parent)
{
	setTitle(tr("Cars preferences"));
	setSubTitle(tr("Specify preferences about the set of cars.<br>"
		       "You can change them up until the first run."));

	typeASpinBox = new QSpinBox;
	typeASpinBox->setRange(MINCARS, MAXCARS);
	typeBSpinBox = new QSpinBox;
	typeBSpinBox->setRange(MINCARS, MAXCARS);
	typeCSpinBox = new QSpinBox;
	typeCSpinBox->setRange(MINCARS, MAXCARS);

	QFormLayout *formLayout = new QFormLayout;

	formLayout->addRow(tr("Type &A - Regular driver:"), typeASpinBox);
	formLayout->addRow(tr("Type &B - Fast driver:"), typeBSpinBox);
	formLayout->addRow(tr("Type &C - Slow driver:"), typeCSpinBox);

	carsNoBox = new QGroupBox(tr("Number of cars:"));
	carsNoBox->setLayout(formLayout);

	registerField("typeANo", typeASpinBox);
	registerField("typeBNo", typeBSpinBox);
	registerField("typeCNo", typeCSpinBox);

	QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget(carsNoBox);
	setLayout(layout);

	connect(typeASpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		this, &QWizardPage::completeChanged);
	connect(typeBSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		this, &QWizardPage::completeChanged);
	connect(typeCSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		this, &QWizardPage::completeChanged);
}

bool CarsWizardPage::isComplete() const
{
	return field("typeANo").toInt() +
	       field("typeBNo").toInt() +
	       field("typeCNo").toInt();
}
