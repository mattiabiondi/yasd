#include "new_wizard.h"

NewWizard::NewWizard(QWidget *parent)
	: QWizard(parent)
{
	addPage(new CarsWizardPage);
	addPage(new TrackWizardPage);

	setWizardStyle(ModernStyle);

	setWindowTitle(tr("Create a new configuration"));
}

Configuration *NewWizard::getConfig()
{
	Configuration *config = Configuration::create();

	config->setRed(field("red").toInt());
	config->setGreen(field("green").toInt());
	config->setBlue(field("blue").toInt());
	config->setCrossroads(field("crossroads").toInt());
	config->setLimit(field("limit").toInt());
	config->setFriction(field("friction").toInt());
	return config;
}
