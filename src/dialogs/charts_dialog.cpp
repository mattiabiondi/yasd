#include "src/dialogs/charts_dialog.h"

ChartsDialog::ChartsDialog(QWidget *parent)
	: QDialog(parent)
{
    setWindowTitle(tr("Charts"));
    series = new QLineSeries();
    // series->append(0, 6);
    // series->append(2, 4);
    // series->append(3, 8);
    // series->append(7, 4);
    // series->append(10, 5);
    // *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
   
   QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget(chartView);
    setMinimumWidth(500);
    setMinimumHeight(400);
	setLayout(layout);
}

void ChartsDialog::update(QLineSeries *series,bool isDialogVisible)
{
    if(!isDialogVisible) return;
    
    QLayout *l =  this->layout();
    delete l;
    
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
   
    QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget(chartView);
    setMinimumWidth(500);
    setMinimumHeight(400);
	setLayout(layout);
}