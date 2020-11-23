#ifndef YASD_MAP_WIDGET_H
#define YASD_MAP_WIDGET_H

#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpinBox>
#include <QComboBox>

class MapWidget : public QWidget
{
Q_OBJECT

public:
MapWidget(QWidget *parent = nullptr);

private:
enum {
	MinCrossroadsNo		= 0,
	MaxCrossroadssNo	= 10,
	MinSpeedLimit		= 15,
	MaxSpeedLimit		= 130,
	FrictionAsphalt		= 72,
	FrictionGrass		= 35
};

QSpinBox *crossroadsNoSpinBox;
QSpinBox *speedLimitSpinBox;
QComboBox *frictionComboBox;
};

#endif // YASD_MAP_WIDGET_H
