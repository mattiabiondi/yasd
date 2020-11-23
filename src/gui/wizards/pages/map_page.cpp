#include "map_page.h"

MapWizardPage::MapWizardPage(QWidget *parent)
	: QWizardPage(parent)
{
	setTitle(tr("Map preferences"));
	setSubTitle(tr("Specify preferences about the map.<br>"
		       "You can change them later."));

	QVBoxLayout *layout = new QVBoxLayout;

	mapWidget = new MapWidget;
	layout->addWidget(mapWidget);
	setLayout(layout);
}

int MapWizardPage::nextId() const
{
	return -1;
}
