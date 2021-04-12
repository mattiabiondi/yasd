#ifndef YASD_CHARTS_DIALOG_H
#define YASD_CHARTS_DIALOG_H

#include <QDialog>
#include <QScrollArea>
#include <QFormLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

#include "src/application.h"
#include "src/configuration.h"
#include "src/widgets/cars/car.h"

using namespace QtCharts;

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
QT_END_NAMESPACE

class ChartsDialog : public QDialog
{
Q_OBJECT

public:
ChartsDialog(QWidget *parent = nullptr);

public slots:
void update(QLineSeries *series, bool isDialogVisible);

private:
QDialogButtonBox *buttonBox;
QLabel *redLabel;
QLabel *greenLabel;
QLabel *blueLabel;
QLabel *generationLabel;
QLabel *crossroadsLabel;
QLabel *limitLabel;
QLabel *frictionLabel;
QLineSeries *series = NULL;
QChart *chart;
QChartView *chartView;
};

#endif // YASD_CHARTS_DIALOG_H
