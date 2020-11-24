#include "new_wizard.h"

NewWizard::NewWizard(QWidget *parent)
	: QWizard(parent)
{
	addPage(new CarsWizardPage);
	addPage(new MapWizardPage);

	setWizardStyle(ModernStyle);

	setWindowTitle(tr("Create a new configuration"));
}
