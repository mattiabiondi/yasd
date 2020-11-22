#include <QtWidgets/QVBoxLayout>
#include "../dialogs/new_dialog.h"

CarsSetPage::CarsSetPage(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout;

	label = new QLabel(tr("provaaa"));
	layout->addWidget(label);
	setLayout(layout);
}
