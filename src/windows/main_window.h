#ifndef YASD_MAIN_WINDOW_H
#define YASD_MAIN_WINDOW_H

#include <QMainWindow>

#include "src/configuration.h"
#include "src/session.h"
#include "src/application.h"
#include "src/widgets/track_widget.h"
#include "src/wizards/new_wizard.h"
#include "src/dialogs/cars_dialog.h"
#include "src/dialogs/track_dialog.h"
#include "src/dialogs/config_dialog.h"

QT_BEGIN_NAMESPACE
class Session;
class QAction;
class QMenu;
class QPushButton;
class QSessionManager;
class ConfigWidget;
class TrackTab;
class TrackWidget;
class ConfigDialog;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
MainWindow();
ConfigDialog *configDialog;

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
void viewConfig();
void about();
void fileWasModified();
void configurationChanged();
void speedChanged();
#ifndef QT_NO_SESSIONMANAGER
void commitData(QSessionManager &);
#endif

private:
void createActions();
void createStatusBar();
void createWelcomeWidget();
void createTrackWidget();
void readSettings();
void writeSettings();
bool maybeSave();
static bool hasRecentFiles();
void prependToRecentFiles(const QString &fileName);
void setRecentFilesVisible(bool visible);
QString strippedName(const QString &fullFileName);

const Session *session;

QPushButton *createButton(const QAction *action, const QString &text = QString());

QWidget *welcomeWidget();
TrackWidget *trackWidget;

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
QAction *viewConfigAct;
QAction *aboutAct;
QAction *aboutQtAct;

NewWizard *newWizard;
};

#endif // YASD_MAIN_WINDOW_H
