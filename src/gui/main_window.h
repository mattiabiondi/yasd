#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "wizards/new_wizard.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QTabWidget;
class QPushButton;
class QSessionManager;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
MainWindow();

void loadFile(const QString &fileName);

protected:
void closeEvent(QCloseEvent *event) override;

private slots:
void newFile();
void open();
bool save();
bool saveAs();
void updateRecentFileActions();
void openRecentFile();
void clearRecentFiles();
void editSet();
void editMap();
void about();
void fileWasModified();
#ifndef QT_NO_SESSIONMANAGER
void commitData(QSessionManager &);
#endif

private:
enum { MaxRecentFiles = 5 };

void createActions();
void createStatusBar();
void createTabs();
void readSettings();
void writeSettings();
bool maybeSave();
static bool hasRecentFiles();
void prependToRecentFiles(const QString &fileName);
void setRecentFilesVisible(bool visible);
bool saveFile(const QString &fileName);
void setCurrentFile(const QString &fileName);
QString strippedName(const QString &fullFileName);

QTabWidget *tabWidget;

QPushButton *createButton(const QAction *action, const QString &text = QString());

QWidget *welcomeTab();

QAction *newAct;
QAction *openAct;
QAction *saveAct;
QAction *saveAsAct;
QAction *recentFileActs[MaxRecentFiles];
QAction *recentFileSubMenuAct;
QAction *recentFileSeparator;
QAction *clearRecentFilesAct;
QAction *exitAct;
QAction *editSetAct;
QAction *editMapAct;
QAction *aboutAct;
QAction *aboutQtAct;

NewWizard *newWizard;

QString curFile;
bool isUntitled;
};

#endif // MAINWINDOW_H
