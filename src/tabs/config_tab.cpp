#include "src/tabs/config_tab.h"

ConfigTab::ConfigTab(QWidget *parent)
	: QWidget(parent)
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

	QWidget *tab = new QWidget;

	tab->setObjectName("ConfigTab");
	tab->setLayout(vBoxLayout);

	QScrollArea *scrollArea = new QScrollArea;

	scrollArea->setWidget(tab);
	scrollArea->setWidgetResizable(true);
	scrollArea->setFrameShape(QFrame::NoFrame);
	scrollArea->setStyleSheet("QAbstractScrollArea, #ConfigTab {background: transparent}");

	QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget(scrollArea);
	setLayout(layout);

	update();
}

void ConfigTab::update()
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
