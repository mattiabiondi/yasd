#ifndef YASD_APPLICATION_H
#define YASD_APPLICATION_H

#include <QApplication>
#include <QScopedPointer>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "src/configuration.h"
#include "src/gui/main_window.h"

class MainWindow;

class Application : public QApplication {
Q_OBJECT

public:
Application(int& argc, char **argv);

Configuration *getConfig();
void createConfig(Configuration *newConfig);
void loadConfig(const QString &fileName);

const QString& getCurrentDir() const
{
	return dir;
}

QString curFile;
bool isUntitled;

signals:
void configurationChanged();

private:
void setCurrentConfig(Configuration *newConfig);
QScopedPointer<Configuration> config;
QScopedPointer<MainWindow> mainWin;
QString dir;
};

Application *Appl();

#endif // YASD_APPLICATION_H
