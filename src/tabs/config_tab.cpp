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

	QFormLayout *mapFormLayout = new QFormLayout;

	crossroadsLabel = new QLabel;
	mapFormLayout->addRow(tr("No. of crossroads:"), crossroadsLabel);
	speedLimitLabel = new QLabel;
	mapFormLayout->addRow(tr("Speed limit:"), speedLimitLabel);
	frictionLabel = new QLabel;
	mapFormLayout->addRow(tr("Coefficient of friction:"), frictionLabel);

	QGroupBox *mapGroupBox = new QGroupBox(tr("Map:"));

	mapGroupBox->setLayout(mapFormLayout);

	QVBoxLayout *vBoxLayout = new QVBoxLayout;

	vBoxLayout->setAlignment(Qt::AlignCenter);
	vBoxLayout->addStretch();
	vBoxLayout->addWidget(carsGroupBox);
	vBoxLayout->addWidget(mapGroupBox);
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
	speedLimitLabel->setText(QString("%1 km/h").arg(config->getSpeedLimit()));
	if (config->getFriction() == FRICTIONASPHALTINDEX)
		frictionLabel->setText(QString::number(FRICTIONASPHALT));
	else if (config->getFriction() == FRICTIONGRASSINDEX)
		frictionLabel->setText(QString::number(FRICTIONGRASS));
}
