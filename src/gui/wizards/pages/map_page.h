#ifndef YASD_MAP_PAGE_H
#define YASD_MAP_PAGE_H

#include <QWizardPage>
#include <QFormLayout>
#include <QSpinBox>
#include <QComboBox>

#include "src/const.h"

class MapWizardPage : public QWizardPage
{
Q_OBJECT

protected:
void initializePage() override;

public:
MapWizardPage(QWidget *parent = nullptr);

private:
QSpinBox *crossroadsNoSpinBox;
QSpinBox *speedLimitSpinBox;
QComboBox *frictionComboBox;
};

#endif // YASD_MAP_PAGE_H
