#include "new_wizard.h"

NewWizard::NewWizard(QWidget *parent)
	: QWizard(parent)
{
	setPage(Path_Page, new PathWizardPage);
	setPage(Cars_Page, new CarsSetWizardPage);
	setPage(Map_Page, new MapWizardPage);

	setStartId(Path_Page);
	setWizardStyle(ModernStyle);

	setWindowTitle(tr("Create a new configuration"));
}

PathWizardPage::PathWizardPage(QWidget *parent) : QWizardPage(parent)
{
	setTitle(tr("Path"));
}

int PathWizardPage::nextId() const
{
	return NewWizard::Cars_Page;
}
