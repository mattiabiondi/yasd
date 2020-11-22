#ifndef YASD_MAP_PAGE_H
#define YASD_MAP_PAGE_H

#include <QtWidgets/QWizardPage>
#include <QtWidgets/QLabel>

class MapPage : public QWidget
{
Q_OBJECT

public:
    MapPage(QWidget *parent = nullptr);

private:
    QLabel *label;

};

#endif //YASD_MAP_PAGE_H
