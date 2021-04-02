#include "src/dialogs/config_dialog.h"

ConfigDialog::ConfigDialog(QWidget *parent)
	: QDialog(parent)
{
	QFormLayout *carsFormLayout = new QFormLayout;

	redLabel = new QLabel;
	carsFormLayout->addRow(tr("Red - Fast driver:"), redLabel);
	greenLabel = new QLabel;
	carsFormLayout->addRow(tr("Green - Regular driver:"), greenLabel);
	blueLabel = new QLabel;
	carsFormLayout->addRow(tr("Blue - Slow driver:"), blueLabel);

	QGroupBox *carsGroupBox = new QGroupBox(tr("Number of cars:"));

	carsGroupBox->setLayout(carsFormLayout);

	QFormLayout *trackFormLayout = new QFormLayout;

	crossroadsLabel = new QLabel;
	trackFormLayout->addRow(tr("No. of crossroads:"), crossroadsLabel);
	limitLabel = new QLabel;
	trackFormLayout->addRow(tr("Speed limit:"), limitLabel);
	frictionLabel = new QLabel;
	trackFormLayout->addRow(tr("Coefficient of friction:"), frictionLabel);

	QGroupBox *trackGroupBox = new QGroupBox(tr("Track:"));

	trackGroupBox->setLayout(trackFormLayout);

	QVBoxLayout *vBoxLayout = new QVBoxLayout;

	vBoxLayout->setAlignment(Qt::AlignCenter);
	vBoxLayout->addStretch();
	vBoxLayout->addWidget(carsGroupBox);
	vBoxLayout->addWidget(trackGroupBox);
	vBoxLayout->addStretch();

	QWidget *configWidget = new QWidget;

	configWidget->setObjectName("ConfigDialog");
	configWidget->setLayout(vBoxLayout);

	QScrollArea *scrollArea = new QScrollArea;

	scrollArea->setWidget(configWidget);
	scrollArea->setWidgetResizable(true);
	scrollArea->setFrameShape(QFrame::NoFrame);
	scrollArea->setStyleSheet("QAbstractScrollArea, #ConfigDialog {background: transparent}");

	QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget(scrollArea);

	buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &ConfigDialog::reject);
	layout->addWidget(buttonBox);

	setLayout(layout);

	update();
}

void ConfigDialog::update()
{
	const Configuration *config = Appl()->getConfig();

	redLabel->setText(QString::number(config->getRed()));
	greenLabel->setText(QString::number(config->getGreen()));
	blueLabel->setText(QString::number(config->getBlue()));
	crossroadsLabel->setText(QString::number(config->getCrossroads()));
	limitLabel->setText(QString("%1 km/h").arg(config->getLimit()));
	if (config->getFriction() == FRICTIONASPHALTINDEX)
		frictionLabel->setText(QString::number(FRICTIONASPHALT));
	else if (config->getFriction() == FRICTIONGRASSINDEX)
		frictionLabel->setText(QString::number(FRICTIONGRASS));
}
