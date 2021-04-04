#ifndef YASD_CONFIG_DIALOG_H
#define YASD_CONFIG_DIALOG_H

#include <QDialog>
#include <QScrollArea>
#include <QFormLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

#include "src/application.h"
#include "src/configuration.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
QT_END_NAMESPACE

class ConfigDialog : public QDialog
{
Q_OBJECT

public:
ConfigDialog(QWidget *parent = nullptr);

public slots:
void update();

private:
QDialogButtonBox *buttonBox;
QLabel *redLabel;
QLabel *greenLabel;
QLabel *blueLabel;
QLabel *generationLabel;
QLabel *crossroadsLabel;
QLabel *limitLabel;
QLabel *frictionLabel;
};

#endif // YASD_CONFIG_DIALOG_H
