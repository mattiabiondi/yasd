#include <QtWidgets/QVBoxLayout>
#include "new_dialog.h"
#include "../pages/cars_set_page.h"

NewDialog::NewDialog(QWidget *parent)
	: QWizard(parent)
{
	setPage(Path_Page, new PathWizardPage);
	setPage(Cars_Set_Page, new CarsSetWizardPage);
	setPage(Map_Page, new MapWizardPage);

	setStartId(Path_Page);
	setWizardStyle(ModernStyle);

	setWindowTitle(tr("Create new configuration"));
}

PathWizardPage::PathWizardPage(QWidget *parent) : QWizardPage(parent)
{
	setTitle(tr("Path page"));
	topLabel = new QLabel(tr("Path page"));
	topLabel->setWordWrap(true);
}

int PathWizardPage::nextId() const
{
	return NewDialog::Cars_Set_Page;
}

CarsSetWizardPage::CarsSetWizardPage(QWidget *parent)
{
	setTitle(tr("Cars set page"));

	carsSetPage = new CarsSetPage;
	QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget(carsSetPage);
	setLayout(layout);
}

int CarsSetWizardPage::nextId() const
{
	return NewDialog::Map_Page;
}

MapWizardPage::MapWizardPage(QWidget *parent) : QWizardPage(parent)
{
	setTitle(tr("Map page"));

	mapPage = new MapPage;
	QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget(mapPage);
	setLayout(layout);
}

int MapWizardPage::nextId() const
{
	return -1;
}
