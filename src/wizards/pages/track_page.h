#ifndef YASD_MAP_PAGE_H
#define YASD_MAP_PAGE_H

#include <QWizardPage>
#include <QFormLayout>
#include <QSpinBox>
#include <QComboBox>

#include "src/const.h"

class TrackWizardPage : public QWizardPage
{
Q_OBJECT

protected:
void initializePage() override;

public:
TrackWizardPage(QWidget *parent = nullptr);

private:
QSpinBox *crossroadsSpinBox;
QSpinBox *limitSpinBox;
QComboBox *frictionComboBox;
};

#endif // YASD_MAP_PAGE_H
