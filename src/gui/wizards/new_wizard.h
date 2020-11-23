#ifndef YASD_NEW_WIZARD_H
#define YASD_NEW_WIZARD_H

#include <QWizard>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>

#include "pages/cars_page.h"
#include "pages/map_page.h"

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
enum { Cars_Page, Map_Page };
NewWizard(QWidget *parent = nullptr);

//todo void accept() override;
};

#endif // YASD_NEW_WIZARD_H