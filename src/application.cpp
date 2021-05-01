#include "application.h"

Application::Application(int& argc, char **argv)
	: QApplication(argc, argv),
	config(NULL)
{
	QCoreApplication::setOrganizationName("yasd");

	session.reset(new Session);

	mainWin.reset(new MainWindow);

	mainWin->show();
}

Configuration *Application::getConfig()
{
	return config.get();
}

Session *Application::getSession()
{
	return session.get();
}

void Application::createConfig(Configuration *newConfig)
{
	setCurrentConfig(QString(), newConfig);
}

void Application::loadConfig(const QString &fileName)
{
	QString error;
	Configuration *newConfig = Configuration::loadFromFile(QFile::encodeName(fileName).constData(),
							       error);

	if (newConfig)
		setCurrentConfig(fileName, newConfig);
	else
		QMessageBox::critical(mainWin.get(), QString("%1: Error").arg(applicationName()),
				      QString("<b>Error loading configuration:</b> %1").arg(error));
}

void Application::setCurrentConfig(const QString &fileName, Configuration *newConfig)
{
	session->stop();

	config.reset(newConfig);

	static int sequenceNumber = 1;

	isUntitled = fileName.isEmpty();
	if (isUntitled) {
		curFile = tr("untitled%1.yasd").arg(sequenceNumber++);
	} else {
		QFileInfo info(fileName);
		dir = info.absolutePath();
		QDir::setCurrent(dir);
		curFile = info.canonicalFilePath();
	}

	emit configurationChanged();
}

Application *Appl()
{
	return static_cast<Application *>(qApp);
}
