#include "new_wizard.h"

NewWizard::NewWizard(QWidget *parent)
	: QWizard(parent)
{
	addPage(new CarsWizardPage);
	addPage(new MapWizardPage);

	setWizardStyle(ModernStyle);

	setWindowTitle(tr("Create a new configuration"));
}

void NewWizard::accept()
{
	int typeANo = field("typeANo").toInt();
	int typeBNo = field("typeBNo").toInt();
	int typeCNo = field("typeCNo").toInt();

	int crossroadsNo = field("crossroadsNo").toInt();
	int speedLimit = field("speedLimit").toInt();
	int friction = field("friction").toInt();

	QDialog::accept();
}
