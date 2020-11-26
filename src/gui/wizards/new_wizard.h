#ifndef YASD_NEW_WIZARD_H
#define YASD_NEW_WIZARD_H

#include <QWizard>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QScopedPointer>
#include <QString>

#include "pages/cars_page.h"
#include "pages/map_page.h"
#include "src/configuration.h"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QGroupBox;
class QLineEdit;
class QRadioButton;
QT_END_NAMESPACE

class NewWizard : public QWizard
{
Q_OBJECT

public:
NewWizard(QWidget *parent = nullptr);

Configuration *getConfig();
};

#endif // YASD_NEW_WIZARD_H
