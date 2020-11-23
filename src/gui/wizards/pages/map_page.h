#ifndef YASD_MAP_PAGE_H
#define YASD_MAP_PAGE_H

#include <QWizardPage>
#include <QLabel>

#include "../../widgets/map_widget.h"

class MapWizardPage : public QWizardPage
{
Q_OBJECT

public:
MapWizardPage(QWidget *parent = nullptr);
int nextId() const override;

private:
MapWidget *mapWidget;
};

#endif // YASD_MAP_PAGE_H