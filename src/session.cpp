#include "src/session.h"

Session::Session()
	: status(STOPPED)
{
	createActions();
	updateActions();
	connect(this, &Session::statusChanged, this, &Session::updateActions);
	connect(this, &Session::speedChanged, this, &Session::updateActions);
	connect(Appl(), &Application::configurationChanged, this, &Session::configurationChanged);

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &Session::timeout);
}

void Session::createActions()
{
	startAct = new QAction("Start", this);
	startAct->setIcon(QIcon::fromTheme("media-playback-start"));
	connect(startAct, &QAction::triggered, this, &Session::start);
	startAct->setEnabled(false);

	stopAct = new QAction("Stop", this);
	stopAct->setIcon(QIcon::fromTheme("media-playback-pause"));
	connect(stopAct, &QAction::triggered, this, &Session::stop);
	stopAct->setEnabled(false);

	toggleAct = new QAction("Start", this);
	toggleAct->setIcon(QIcon::fromTheme("media-playback-start"));
	connect(toggleAct, &QAction::triggered, this, &Session::toggle);
	toggleAct->setShortcut(QKeySequence("Space"));
	toggleAct->setEnabled(false);

	incSpeedAct = new QAction("Speed++", this);
	incSpeedAct->setIcon(QIcon::fromTheme("media-seek-forward"));
	connect(incSpeedAct, &QAction::triggered, this, &Session::increaseSpeed);
	incSpeedAct->setShortcut(QKeySequence("Ctrl++"));
	incSpeedAct->setEnabled(false);

	decSpeedAct = new QAction("Speed--", this);
	decSpeedAct->setIcon(QIcon::fromTheme("media-seek-backward"));
	connect(decSpeedAct, &QAction::triggered, this, &Session::decreaseSpeed);
	decSpeedAct->setShortcut(QKeySequence("Ctrl+-"));
	decSpeedAct->setEnabled(false);
}

void Session::updateActions()
{
	startAct->setEnabled(Appl()->getConfig() != NULL && !isRunning());
	stopAct->setEnabled(isRunning());

	if (startAct->isEnabled() || Appl()->getConfig() == NULL) {
		toggleAct->setText("Start");
		toggleAct->setToolTip("Start");
		toggleAct->setIcon(QIcon::fromTheme("media-playback-start"));
	} else {
		toggleAct->setText("Stop");
		toggleAct->setToolTip("Stop");
		toggleAct->setIcon(QIcon::fromTheme("media-playback-pause"));
	}

	incSpeedAct->setEnabled(Appl()->getConfig() != NULL && Appl()->getConfig()->getSpeed() < MAXSPEED);
	decSpeedAct->setEnabled(Appl()->getConfig() != NULL && Appl()->getConfig()->getSpeed() > MINSPEED);
}

void Session::setStatus(Status status)
{
	if (status != this->status) {
		this->status = status;
		emit statusChanged();
	}
}

void Session::setSpeed(int speed)
{
	if (Appl()->getConfig() != NULL) {
		Appl()->getConfig()->setSpeed(speed);

		// Set timeout interval to: 1000ms/60 (= 60fps) / speed
		timer->setInterval((1000 / 60) / speed);

		emit speedChanged();
	}
}

void Session::configurationChanged()
{
	if (Appl()->getConfig() != NULL) {
		startAct->setEnabled(true);
		toggleAct->setEnabled(true);
		incSpeedAct->setEnabled(Appl()->getConfig()->getSpeed() < MAXSPEED);
		decSpeedAct->setEnabled(Appl()->getConfig()->getSpeed() > MINSPEED);
	}
}

void Session::toggle()
{
	if (startAct->isEnabled())
		start();
	else
		stop();
}

void Session::start()
{
	assert(isStopped());

	emit sessionStarted();

	setStatus(RUNNING);

	timer->start();
}

void Session::stop()
{
	if (isRunning()) {
		timer->stop();
		setStatus(STOPPED);
		emit sessionStopped();
	}
}

void Session::increaseSpeed()
{
	if (Appl()->getConfig() != NULL)
		setSpeed(Appl()->getConfig()->getSpeed() + 1);
}

void Session::decreaseSpeed()
{
	if (Appl()->getConfig() != NULL)
		setSpeed(Appl()->getConfig()->getSpeed() - 1);
}

void Session::timeout()
{
	emit iterationDone();
}
