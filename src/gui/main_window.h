#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/configuration.h"
#include "src/application.h"
#include "src/gui/tabs/config_tab.h"
#include "src/gui/wizards/new_wizard.h"
#include "src/gui/dialogs/cars_dialog.h"
#include "src/gui/dialogs/map_dialog.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QTabWidget;
class QPushButton;
class QSessionManager;
class ConfigTab;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
MainWindow();

protected:
void closeEvent(QCloseEvent *event) override;

private slots:
void newFile();
void open();
void save();
void saveAs();
void updateRecentFileActions();
void openRecentFile();
void clearRecentFiles();
void editCars();
void editMap();
void about();
void fileWasModified();
void configurationChanged();
#ifndef QT_NO_SESSIONMANAGER
void commitData(QSessionManager &);
#endif

private:
void createActions();
void createStatusBar();
void createTabs();
void readSettings();
void writeSettings();
bool maybeSave();
static bool hasRecentFiles();
void prependToRecentFiles(const QString &fileName);
void setRecentFilesVisible(bool visible);
QString strippedName(const QString &fullFileName);

QPushButton *createButton(const QAction *action, const QString &text = QString());

QTabWidget *tabWidget;
QWidget *welcomeTab();
ConfigTab *configTab;

QAction *newAct;
QAction *openAct;
QAction *saveAct;
QAction *saveAsAct;
QAction *recentFileActs[MAXRECENTFILES];
QAction *recentFileSubMenuAct;
QAction *recentFileSeparator;
QAction *clearRecentFilesAct;
QAction *exitAct;
QAction *editCarsAct;
QAction *editMapAct;
QAction *aboutAct;
QAction *aboutQtAct;

NewWizard *newWizard;
MapDialog *mapDialog;
};

#endif // MAINWINDOW_H
