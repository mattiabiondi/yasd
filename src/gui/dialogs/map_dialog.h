#ifndef YASD_MAP_DIALOG_H
#define YASD_MAP_DIALOG_H

#include <QtWidgets>
#include <QDialog>
#include <QSpinBox>
#include <QComboBox>

#include "../const.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
QT_END_NAMESPACE

class MapDialog : public QDialog
{
Q_OBJECT

public:
MapDialog(QWidget *parent = nullptr);

private:
QDialogButtonBox *buttonBox;
QSpinBox *crossroadsNoSpinBox;
QSpinBox *speedLimitSpinBox;
QComboBox *frictionComboBox;
};

#endif // YASD_MAP_DIALOG_H
