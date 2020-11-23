#include "new_wizard.h"

NewWizard::NewWizard(QWidget *parent)
	: QWizard(parent)
{
	setPage(Cars_Page, new CarsWizardPage);
	setPage(Map_Page, new MapWizardPage);

	setStartId(Cars_Page);
	setWizardStyle(ModernStyle);

	setWindowTitle(tr("Create a new configuration"));
}
