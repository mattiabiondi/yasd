#ifndef YASD_NEW_DIALOG_H
#define YASD_NEW_DIALOG_H

#include <QWizard>
#include <QLabel>
#include "../pages/cars_set_page.h"
#include "../pages/map_page.h"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QGroupBox;
class QLineEdit;
class QRadioButton;
QT_END_NAMESPACE

class NewDialog : public QWizard
{
Q_OBJECT

public:
    enum { Path_Page, Cars_Set_Page, Map_Page };
    NewDialog(QWidget *parent = nullptr);


//    void accept() override;
};

class PathWizardPage : public QWizardPage
{
Q_OBJECT

public:
    PathWizardPage(QWidget *parent = nullptr);
    int nextId() const override;
private:
    QLabel *topLabel;
};

class CarsSetWizardPage : public QWizardPage
{
 Q_OBJECT

public:
    CarsSetWizardPage(QWidget *parent = nullptr);
    int nextId() const override;
private:
    CarsSetPage *carsSetPage;

};

class MapWizardPage : public QWizardPage
{
Q_OBJECT

public:
    MapWizardPage(QWidget *parent = nullptr);
    int nextId() const override;

private:
    MapPage *mapPage;
};


#endif //YASD_NEW_DIALOG_H
