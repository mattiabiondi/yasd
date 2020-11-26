#include "src/application.h"

int main(int argc, char *argv[])
{
	Application app(argc, argv);

#ifdef Q_OS_ANDROID
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	QCoreApplication::setApplicationName("yasd");
	QCoreApplication::setApplicationVersion(PROJECT_VERSION);
	QCommandLineParser parser;
	parser.setApplicationDescription(QCoreApplication::applicationName());
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addPositionalArgument("file", "The .yasd file to load.");
	parser.process(app);

	if (!parser.positionalArguments().isEmpty())
		Appl()->loadConfig(parser.positionalArguments().first());

	return app.exec();
}
