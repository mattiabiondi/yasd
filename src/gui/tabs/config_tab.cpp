#include "config_tab.h"

ConfigTab::ConfigTab(QWidget *parent)
	: QWidget(parent)
{
	QFormLayout *carsFormLayout = new QFormLayout;

	typeALabel = new QLabel;
	carsFormLayout->addRow(tr("Type A - Regular driver:"), typeALabel);
	typeBLabel = new QLabel;
	carsFormLayout->addRow(tr("Type B - Fast driver:"), typeBLabel);
	typeCLabel = new QLabel;
	carsFormLayout->addRow(tr("Type C - Slow driver:"), typeCLabel);

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

	typeALabel->setText(QString::number(config->getTypeA()));
	typeBLabel->setText(QString::number(config->getTypeB()));
	typeCLabel->setText(QString::number(config->getTypeC()));
	crossroadsLabel->setText(QString::number(config->getCrossroads()));
	speedLimitLabel->setText(QString("%1 km/h").arg(config->getSpeedLimit()));
	if (config->getFriction() == FRICTIONASPHALTINDEX)
		frictionLabel->setText(QString::number(FRICTIONASPHALT));
	else if (config->getFriction() == FRICTIONGRASSINDEX)
		frictionLabel->setText(QString::number(FRICTIONGRASS));
}
