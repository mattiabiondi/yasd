#ifndef YASD_MAP_DIALOG_H
#define YASD_MAP_DIALOG_H

#include <QtWidgets>
#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QDialogButtonBox>

#include "src/configuration.h"
#include "src/const.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
QT_END_NAMESPACE

class TrackDialog : public QDialog
{
Q_OBJECT

public:
TrackDialog(Configuration *config, QWidget *parent = nullptr);

private:
Configuration *const config;

QDialogButtonBox *buttonBox;
QSpinBox *crossroadsSpinBox;
QSpinBox *limitSpinBox;
QComboBox *frictionComboBox;

private slots:
void saveConfig();
};

#endif // YASD_MAP_DIALOG_H
