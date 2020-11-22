#ifndef YASD_NEW_WIZARD_H
#define YASD_NEW_WIZARD_H

#include <QWizard>
#include <QVBoxLayout>
#include <QLabel>

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
enum { Path_Page, Cars_Page, Map_Page };
NewWizard(QWidget *parent = nullptr);

//todo void accept() override;
};

class PathWizardPage : public QWizardPage
{
Q_OBJECT

public:
PathWizardPage(QWidget *parent = nullptr);
int nextId() const override;
private:
};

#endif // YASD_NEW_WIZARD_H
