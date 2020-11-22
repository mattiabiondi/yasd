#include "cars_page.h"

CarsSetWizardPage::CarsSetWizardPage(QWidget *parent)
{
	setTitle(tr("Cars"));
}

int CarsSetWizardPage::nextId() const
{
	return NewWizard::Map_Page;
}
