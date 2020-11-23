#ifndef YASD_MAP_DIALOG_H
#define YASD_MAP_DIALOG_H

#include <QDialog>

#include "../widgets/map_widget.h"

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
MapWidget *mapWidget;
};

#endif // YASD_MAP_DIALOG_H
