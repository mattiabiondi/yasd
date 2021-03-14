#ifndef YASD_MAIN_WINDOW_H
#define YASD_MAIN_WINDOW_H

#include <QMainWindow>

#include "src/configuration.h"
#include "src/application.h"
#include "src/tabs/config_tab.h"
#include "src/tabs/track_tab.h"
#include "src/windows/track_window.h"
#include "src/wizards/new_wizard.h"
#include "src/dialogs/cars_dialog.h"
#include "src/dialogs/track_dialog.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QTabWidget;
class QPushButton;
class QSessionManager;
class ConfigTab;
class TrackTab;
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
bool save();
bool saveAs();
void updateRecentFileActions();
void openRecentFile();
void clearRecentFiles();
void editCars();
void editTrack();
void about();
void openTrack();
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
TrackTab *trackTab;

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
QAction *editTrackAct;
QAction *aboutAct;
QAction *aboutQtAct;
QAction *openTrackAct;

NewWizard *newWizard;
TrackDialog *trackDialog;
};

#endif // YASD_MAIN_WINDOW_H
