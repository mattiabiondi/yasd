#include <QtWidgets>

#include "map_dialog.h"

MapDialog::MapDialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle(tr("Map preferences"));

	QVBoxLayout *layout = new QVBoxLayout;

	mapWidget = new MapWidget;
	layout->addWidget(mapWidget);

	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
					 | QDialogButtonBox::Cancel);
	connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

	layout->addWidget(buttonBox);

	setLayout(layout);
}
