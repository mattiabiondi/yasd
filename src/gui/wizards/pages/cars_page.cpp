#include "cars_page.h"

CarsWizardPage::CarsWizardPage(QWidget *parent)
{
	setTitle(tr("Cars preferences"));
	setSubTitle(tr("Specify preferences about the set of cars.<br>"
		       "You can change them up until the first run."));

	QVBoxLayout *layout = new QVBoxLayout;

	carsWidget = new CarsWidget;
	layout->addWidget(carsWidget);
	setLayout(layout);
}

int CarsWizardPage::nextId() const
{
	return NewWizard::Map_Page;
}
