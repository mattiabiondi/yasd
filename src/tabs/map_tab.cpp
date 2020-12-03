#include "src/tabs/map_tab.h"

MapTab::MapTab(QWidget *parent)
	: QWidget(parent)
{
	grass = new QColor("#a3be8c");
	asphalt = new QColor("#4c566a");

	vBoxLayout = new QVBoxLayout;
	vBoxLayout->setAlignment(Qt::AlignCenter);

	QWidget *tab = new QWidget;

	tab->setObjectName("MapTab");
	tab->setLayout(vBoxLayout);

	QScrollArea *scrollArea = new QScrollArea;

	scrollArea->setWidget(tab);
	scrollArea->setWidgetResizable(true);
	scrollArea->setFrameShape(QFrame::NoFrame);
	scrollArea->setStyleSheet("QAbstractScrollArea, #MapTab {background: transparent}");

	QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget(scrollArea);
	setLayout(layout);

	scene = nullptr;
	view = nullptr;
	track = nullptr;

	update();
}

void MapTab::update()
{
	if (scene) {
		if (view) {
			if (track) {
				scene->removeItem(track);
				delete track;
			}
			vBoxLayout->removeWidget(view);
			delete view;
		}
		delete scene;
	}

	scene = new QGraphicsScene(this);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);

	view = new QGraphicsView(scene);

	view->setRenderHint(QPainter::Antialiasing);
	view->setDragMode(QGraphicsView::ScrollHandDrag);
	view->setBackgroundBrush(QBrush(grass->rgb()));
	view->setCacheMode(QGraphicsView::CacheBackground);
	view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

	vBoxLayout->addWidget(view);

	int crossroadsNum = Appl()->getConfig()->getCrossroads();

	addTrack(scene, asphalt, crossroadsNum);
}

void MapTab::addTrack(QGraphicsScene *scene, QColor *material, int crossroads)
{
	track = new QGraphicsPathItem;

	QPainterPath path;

	switch (crossroads) {
	case 0:
		lissajous(0, 0);
		break;
	case 1:
		lissajous(1, 0);
		break;
	case 2:
		lissajous(0, 2);
		break;
	case 3:
		lissajous(3, 0); // ?
		break;
	case 4:
		lissajous(0, 4); // ?
		break;
	case 5:
		lissajous(5, 0); // ?
		break;
	case 6:
		lissajous(0, 6); // ?
		break;
	case 7:
		lissajous(1, 2);
		break;
	case 8:
		lissajous(0, 8); // ?
		break;
	case 9:
		lissajous(0, 6); // ?
		break;
	case 10:
		lissajous(3, 2); // ?
		break;
	}

	for (int i = 0; i < points - 1; i++) {
		path.moveTo(curve[i]);
		path.lineTo(curve[i + 1]);
	}
	//todo: close path

	track->setPath(path);
	track->setPen(QPen(QBrush(material->rgb()), 75, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	scene->addItem(track);
}

void MapTab::lissajous(int a, int b)
{
	int w = 750;    // width
	int h = w;      // height

	float d = w - 0.2 * w;
	float r = d / 2;

	float cx = w + a * w + w / 2;
	float cy = h + b * h + h / 2;

	float angle = 0;

	for (int i = 0; i < points; i++) {
		float x = r * cos(angle * (a + 1) - M_PI_2);
		float y = r * sin(angle * (b + 1) - M_PI_2);

		curve[i] = QPointF(cx + x, cy + y);

		angle += 0.01;
	}
}

void MapTab::wheelEvent(QWheelEvent *event)
{
	if (event->angleDelta().y() > 0)
		view->scale(1.25, 1.25);
	else
		view->scale(0.8, 0.8);
}
