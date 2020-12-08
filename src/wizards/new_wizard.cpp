#include "new_wizard.h"

NewWizard::NewWizard(QWidget *parent)
	: QWizard(parent)
{
	addPage(new CarsWizardPage);
	addPage(new MapWizardPage);

	setWizardStyle(ModernStyle);

	setWindowTitle(tr("Create a new configuration"));
}

Configuration *NewWizard::getConfig()
{
	Configuration *config = Configuration::create();

	config->setRed(field("redNo").toInt());
	config->setGreen(field("greenNo").toInt());
	config->setBlue(field("blueNo").toInt());
	config->setCrossroads(field("crossroadsNo").toInt());
	config->setSpeedLimit(field("speedLimit").toInt());
	config->setFriction(field("friction").toInt());
	return config;
}
