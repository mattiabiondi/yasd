#include "map_page.h"

MapWizardPage::MapWizardPage(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle(tr("Map"));
}

int MapWizardPage::nextId() const
{
	return -1;
}
