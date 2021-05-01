#ifndef YASD_APPLICATION_H
#define YASD_APPLICATION_H

#include <QApplication>
#include <QScopedPointer>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "src/configuration.h"
#include "src/session.h"
#include "src/windows/main_window.h"

QT_BEGIN_NAMESPACE
class Session;
class MainWindow;
QT_END_NAMESPACE

class Application : public QApplication {
Q_OBJECT

public:
Application(int& argc, char **argv);

Configuration *getConfig();
Session *getSession();
void createConfig(Configuration *newConfig);
void loadConfig(const QString &fileName);
void setCurrentConfig(const QString &fileName, Configuration *newConfig);

const QString& getCurrentDir() const
{
	return dir;
}

QString curFile;
bool isUntitled;

signals:
void configurationChanged();

private:
QScopedPointer<Configuration> config;
QScopedPointer<Session> session;
QScopedPointer<MainWindow> mainWin;
QString dir;
};

Application *Appl();

#endif // YASD_APPLICATION_H
