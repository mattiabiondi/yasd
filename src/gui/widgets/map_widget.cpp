#include "map_widget.h"

MapWidget::MapWidget(QWidget *parent)
	: QWidget(parent)
{
	crossroadsNoSpinBox = new QSpinBox;
	crossroadsNoSpinBox->setRange(MinCrossroadsNo, MaxCrossroadssNo);
	speedLimitSpinBox = new QSpinBox;
	speedLimitSpinBox->setRange(MinSpeedLimit, MaxSpeedLimit);
	speedLimitSpinBox->setSuffix(" km/h");
	frictionComboBox = new QComboBox;
	frictionComboBox->addItem("Asphalt (clean and dry) - 0.72");
	frictionComboBox->addItem("Grass (clean and dry) - 0.35");
	frictionComboBox->setMinimumWidth(325);

	QFormLayout *formLayout = new QFormLayout;

	formLayout->addRow(tr("No. of crossroads:"), crossroadsNoSpinBox);
	formLayout->addRow(tr("Speed limit:"), speedLimitSpinBox);
	formLayout->addRow(tr("Coefficient of friction:"), frictionComboBox);

	setLayout(formLayout);
}
