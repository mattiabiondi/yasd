#include <QtWidgets/QVBoxLayout>
#include "map_page.h"

MapPage::MapPage(QWidget *parent)
{
	QVBoxLayout *layout = new QVBoxLayout;

	label = new QLabel(tr("prova2"));
	layout->addWidget(label);
	setLayout(layout);


	setLayout(layout);
}
