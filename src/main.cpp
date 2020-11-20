#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
#ifdef Q_OS_ANDROID
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("yasd");
	QCoreApplication::setApplicationName("yasd");
	QCoreApplication::setApplicationVersion(PROJECT_VERSION);
	QCommandLineParser parser;
	parser.setApplicationDescription(QCoreApplication::applicationName());
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addPositionalArgument("file", "The .yasd file to load.");
	parser.process(app);

	MainWindow mainWin;
	if (!parser.positionalArguments().isEmpty())
		mainWin.loadFile(parser.positionalArguments().first());
	mainWin.show();
	return app.exec();
}
