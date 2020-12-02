#ifndef YASD_CONFIG_TAB_H
#define YASD_CONFIG_TAB_H

#include <QWidget>
#include <QScrollArea>
#include <QFormLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

#include "src/application.h"
#include "src/configuration.h"

class ConfigTab : public QWidget {
Q_OBJECT

public:
ConfigTab(QWidget *parent = 0);

public slots:
void update();

private:
QLabel *typeALabel;
QLabel *typeBLabel;
QLabel *typeCLabel;
QLabel *crossroadsLabel;
QLabel *speedLimitLabel;
QLabel *frictionLabel;
};

#endif // YASD_CONFIG_TAB_H
