#include <QtWidgets>

#include "cars_dialog.h"

CarsDialog::CarsDialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle(tr("Cars preferences"));

	QVBoxLayout *layout = new QVBoxLayout;

	carsWidget = new CarsWidget;
	layout->addWidget(carsWidget);

	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
					 | QDialogButtonBox::Cancel);
	connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

	layout->addWidget(buttonBox);

	setLayout(layout);
}
