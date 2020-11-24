#include <QtWidgets>

#include "main_window.h"

MainWindow::MainWindow()
	: tabWidget(new QTabWidget)
{
	setCentralWidget(tabWidget);

	createActions();
	createStatusBar();
	createTabs();

	readSettings();

#ifndef QT_NO_SESSIONMANAGER
	QGuiApplication::setFallbackSessionManagementEnabled(false);
	connect(qApp, &QGuiApplication::commitDataRequest,
		this, &MainWindow::commitData);
#endif

	setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (maybeSave()) {
		writeSettings();
		event->accept();
	} else {
		event->ignore();
	}
}

void MainWindow::newFile()
{
	if (maybeSave()) {
		setCurrentFile(QString());
		newWizard = new NewWizard;
		newWizard->exec();
	}
}

void MainWindow::open()
{
	if (maybeSave()) {
		QString fileName = QFileDialog::getOpenFileName(this);
		if (!fileName.isEmpty())
			loadFile(fileName);
	}
}

bool MainWindow::save()
{
	return isUntitled ? saveAs() : saveFile(curFile);
}

bool MainWindow::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), curFile);

	if (fileName.isEmpty())
		return false;

	return saveFile(fileName);
}

void MainWindow::setRecentFilesVisible(bool visible)
{
	recentFileSubMenuAct->setVisible(visible);
	recentFileSeparator->setVisible(visible);
}

static inline QString recentFilesKey()
{
	return QStringLiteral("recentFileList");
}
static inline QString fileKey()
{
	return QStringLiteral("file");
}

static QStringList readRecentFiles(QSettings &settings)
{
	QStringList result;
	const int count = settings.beginReadArray(recentFilesKey());

	for (int i = 0; i < count; ++i) {
		settings.setArrayIndex(i);
		result.append(settings.value(fileKey()).toString());
	}
	settings.endArray();
	return result;
}

static void writeRecentFiles(const QStringList &files, QSettings &settings)
{
	const int count = files.size();

	settings.beginWriteArray(recentFilesKey());
	for (int i = 0; i < count; ++i) {
		settings.setArrayIndex(i);
		settings.setValue(fileKey(), files.at(i));
	}
	settings.endArray();
}

bool MainWindow::hasRecentFiles()
{
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
	const int count = settings.beginReadArray(recentFilesKey());

	settings.endArray();
	return count > 0;
}

void MainWindow::prependToRecentFiles(const QString &fileName)
{
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

	const QStringList oldRecentFiles = readRecentFiles(settings);
	QStringList recentFiles = oldRecentFiles;

	recentFiles.removeAll(fileName);
	recentFiles.prepend(fileName);
	if (oldRecentFiles != recentFiles)
		writeRecentFiles(recentFiles, settings);

	setRecentFilesVisible(!recentFiles.isEmpty());
}

void MainWindow::updateRecentFileActions()
{
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

	const QStringList recentFiles = readRecentFiles(settings);
	const int count = qMin(int(MAXRECENTFILES), recentFiles.size());
	int i = 0;

	for ( ; i < count; ++i) {
		const QString fileName = MainWindow::strippedName(recentFiles.at(i));
		recentFileActs[i]->setText(tr("&%1 %2").arg(i + 1).arg(fileName));
		recentFileActs[i]->setData(recentFiles.at(i));
		recentFileActs[i]->setVisible(true);
	}
	for ( ; i < MAXRECENTFILES; ++i)
		recentFileActs[i]->setVisible(false);
}

void MainWindow::openRecentFile()
{
	if (const QAction *action = qobject_cast<const QAction *>(sender()))
		loadFile(action->data().toString());
}

void MainWindow::clearRecentFiles()
{
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
	QStringList recentFiles = readRecentFiles(settings);

	recentFiles.clear();
	writeRecentFiles(recentFiles, settings);
	setRecentFilesVisible(!recentFiles.isEmpty());
}

void MainWindow::editCars()
{
	carsDialog = new CarsDialog;
	carsDialog->exec();
}

void MainWindow::editMap()
{
	mapDialog = new MapDialog;
	mapDialog->exec();
}

void MainWindow::about()
{
	// TODO
	// complete
	QMessageBox::about(this, tr("About yasd"), tr(
				   "<h3>yasd *insert version*</h3>"
				   "<p>(yet another) self-driving car simulator</p>"
				   "<p>yasd is *insert description*</p>"
				   "<p>Website</p>"
				   "<p>Copyright</p>"
				   "<p>Credits</p>"
				   "<p>License</p>"));
}

void MainWindow::fileWasModified()
{
	// TODO
	//setWindowModified(if is modified();
}

void MainWindow::createActions()
{
	QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
	QToolBar *fileToolBar = addToolBar(tr("File"));

	// TODO
	const QIcon newIcon = QIcon::fromTheme("document-new");

	newAct = new QAction(newIcon, tr("&New"), this);
	newAct->setShortcuts(QKeySequence::New);
	newAct->setStatusTip(tr("Create a new file"));
	connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
	fileMenu->addAction(newAct);
	fileToolBar->addAction(newAct);

	// TODO icon
	const QIcon openIcon = QIcon::fromTheme("document-open");

	openAct = new QAction(openIcon, tr("&Open..."), this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip(tr("Open an existing file"));
	connect(openAct, &QAction::triggered, this, &MainWindow::open);
	fileMenu->addAction(openAct);
	fileToolBar->addAction(openAct);

	// TODO icon
	const QIcon saveIcon = QIcon::fromTheme("document-save");

	saveAct = new QAction(saveIcon, tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save the file to disk"));
	connect(saveAct, &QAction::triggered, this, &MainWindow::save);
	fileMenu->addAction(saveAct);
	fileToolBar->addAction(saveAct);

	// TODO icon
	const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");

	saveAsAct = fileMenu->addAction(saveAsIcon, tr("Save &As..."), this, &MainWindow::saveAs);
	saveAsAct->setShortcuts(QKeySequence::SaveAs);
	saveAsAct->setStatusTip(tr("Save the file under a new name"));

	fileMenu->addSeparator();

	QMenu *recentMenu = fileMenu->addMenu(tr("Recent..."));

	connect(recentMenu, &QMenu::aboutToShow, this, &MainWindow::updateRecentFileActions);
	recentFileSubMenuAct = recentMenu->menuAction();

	for (int i = 0; i < MAXRECENTFILES; ++i) {
		recentFileActs[i] = recentMenu->addAction(QString(), this, &MainWindow::openRecentFile);
		recentFileActs[i]->setVisible(false);
	}

	clearRecentFilesAct = new QAction("Clear recent", this);
	clearRecentFilesAct->setStatusTip("Clear recent configurations");
	connect(clearRecentFilesAct, &QAction::triggered, this, &MainWindow::clearRecentFiles);
	recentMenu->addAction(clearRecentFilesAct);

	recentFileSeparator = fileMenu->addSeparator();

	setRecentFilesVisible(MainWindow::hasRecentFiles());

	const QIcon exitIcon = QIcon::fromTheme("application-exit");

	exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
	exitAct->setShortcuts(QKeySequence::Quit);
	exitAct->setStatusTip(tr("Exit yasd"));

	menuBar()->addSeparator();

	QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

	editCarsAct = editMenu->addAction(tr("Cars..."), this, &MainWindow::editCars);
	editCarsAct->setStatusTip(tr("Edit car preferences"));

	editMapAct = editMenu->addAction(tr("Map..."), this, &MainWindow::editMap);
	editMapAct->setStatusTip(tr("Edit map preferences"));

	menuBar()->addSeparator();

	QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

	aboutAct = helpMenu->addAction(tr("&About yasd"), this, &MainWindow::about);
	aboutAct->setStatusTip(tr("About yasd"));

	aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
	aboutQtAct->setStatusTip(tr("About the Qt library"));
}

void MainWindow::createStatusBar()
{
	statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createTabs()
{
	const QIcon detailsIcon = QIcon::fromTheme("todo");

	tabWidget->addTab(welcomeTab(), detailsIcon, "Welcome");
}

QPushButton *MainWindow::createButton(const QAction *action, const QString &text)
{
	QPushButton *button = new QPushButton(action->icon(), text);

	connect(button, &QPushButton::clicked, action, &QAction::trigger);
	return button;
}

QWidget *MainWindow::welcomeTab()
{
	QScrollArea *scrollArea = new QScrollArea;
	QWidget *tab = new QWidget;

	tab->setObjectName("WelcomeTab");
	scrollArea->setWidget(tab);
	scrollArea->setWidgetResizable(true);
	scrollArea->setFrameShape(QFrame::NoFrame);
	scrollArea->setStyleSheet("QAbstractScrollArea, #WelcomeTab {background: transparent}");

	QVBoxLayout *layout = new QVBoxLayout(tab);

	layout->setAlignment(Qt::AlignCenter);

	layout->addStretch();

	QLabel *heading = new QLabel(QString("Welcome to yasd"));
	QFont headingFont = heading->font();

	headingFont.setPointSizeF(headingFont.pointSizeF() * 1.3);
	headingFont.setBold(true);
	heading->setFont(headingFont);
	heading->setAlignment(Qt::AlignCenter);
	layout->addWidget(heading);

	layout->addWidget(createButton(newAct, "Create a new configuration"));

	layout->addWidget(createButton(openAct, "Open an existing configuration"));

	layout->addStretch();

	return scrollArea;
}

void MainWindow::readSettings()
{
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
	const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();

	if (geometry.isEmpty()) {
		const QRect availableGeometry = screen()->availableGeometry();
		resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
		move((availableGeometry.width() - width()) / 2,
		     (availableGeometry.height() - height()) / 2);
	} else {
		restoreGeometry(geometry);
	}
}

void MainWindow::writeSettings()
{
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

	settings.setValue("geometry", saveGeometry());
}

bool MainWindow::maybeSave()
{
	// TODO
	/* return true if file is not modified
	 * return warning message if is modified
	 */
	return true;
}

void MainWindow::loadFile(const QString &fileName)
{
	QFile file(fileName);

	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("yasd"),
				     tr("Cannot read file %1:\n%2.")
				     .arg(QDir::toNativeSeparators(fileName), file.errorString()));
		return;
	}

	// TODO read file
	QTextStream in(&file);

#ifndef QT_NO_CURSOR
	QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	// TODO set the file read
#ifndef QT_NO_CURSOR
	QGuiApplication::restoreOverrideCursor();
#endif

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::saveFile(const QString &fileName)
{
	QString errorMessage;

	QGuiApplication::setOverrideCursor(Qt::WaitCursor);
	QSaveFile file(fileName);

	if (file.open(QFile::WriteOnly | QFile::Text)) {
		// TODO write file
		QTextStream out(&file);
		if (!file.commit())
			errorMessage = tr("Cannot write file %1:\n%2.")
				       .arg(QDir::toNativeSeparators(fileName), file.errorString());
	} else {
		errorMessage = tr("Cannot open file %1 for writing:\n%2.")
			       .arg(QDir::toNativeSeparators(fileName), file.errorString());
	}
	QGuiApplication::restoreOverrideCursor();

	if (!errorMessage.isEmpty()) {
		QMessageBox::warning(this, tr("yasd"), errorMessage);
		return false;
	}

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File saved"), 2000);
	return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
	static int sequenceNumber = 1;

	isUntitled = fileName.isEmpty();
	if (isUntitled)
		curFile = tr("untitled%1.yasd").arg(sequenceNumber++);
	else
		curFile = QFileInfo(fileName).canonicalFilePath();

	// TODO
	// set file as not modified
	setWindowModified(false);

	if (!isUntitled && windowFilePath() != curFile)
		MainWindow::prependToRecentFiles(curFile);

	setWindowFilePath(curFile);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}

#ifndef QT_NO_SESSIONMANAGER
void MainWindow::commitData(QSessionManager &manager)
{
	if (manager.allowsInteraction()) {
		if (!maybeSave())
			manager.cancel();
	} else {
		// Non-interactive: save without asking
		// TODO check if file is modified
		save();
	}
}
#endif
