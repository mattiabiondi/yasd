#include "configuration.h"

template<typename T>
static T bumpProperty(T minValue, T value, T maxValue)
{
	if (value < minValue)
		return minValue;
	else if (value > maxValue)
		return maxValue;
	else
		return value;
}

Configuration *Configuration::loadFromFile(const QString &fileName, QString &error)
{
	// todo read json
/*
 *      QFile file(fileName);
 *
 *      if (!file.open(QFile::ReadOnly | QFile::Text)) {
 *              QMessageBox::warning(this, tr("yasd"),
 *                                   tr("Cannot read file %1:\n%2.")
 *                                   .arg(QDir::toNativeSeparators(fileName), file.errorString()));
 *              return;
 *      }
 */
	QScopedPointer<Configuration> config(new Configuration);

/*
 *
 *      // TODO read file
 *      QTextStream in(&file);
 *
 #ifndef QT_NO_CURSOR
 *      QGuiApplication::setOverrideCursor(Qt::WaitCursor);
 #endif
 *      // TODO set the file read
 #ifndef QT_NO_CURSOR
 *      QGuiApplication::restoreOverrideCursor();
 #endif
 */
	return config.take();
}

Configuration *Configuration::create()
{
	QScopedPointer<Configuration> config(new Configuration);

	return config.take();
}

bool Configuration::save(const QString &fileName)
{
	// todo write json

/*
 *      QString errorMessage;
 *
 *      QGuiApplication::setOverrideCursor(Qt::WaitCursor);
 *      QSaveFile file(fileName);
 *
 *      if (file.open(QFile::WriteOnly | QFile::Text)) {
 *              // TODO write file
 *              QTextStream out(&file);
 *              if (!file.commit())
 *                      errorMessage = tr("Cannot write file %1:\n%2.")
 *                                     .arg(QDir::toNativeSeparators(fileName), file.errorString());
 *      } else {
 *              errorMessage = tr("Cannot open file %1 for writing:\n%2.")
 *                             .arg(QDir::toNativeSeparators(fileName), file.errorString());
 *      }
 *      QGuiApplication::restoreOverrideCursor();
 *
 *      if (!errorMessage.isEmpty()) {
 *              QMessageBox::warning(this, tr("yasd"), errorMessage);
 *              return false;
 *      }
 *
 *      //setCurrentFile(fileName);
 */
	return true;
}

void Configuration::setTypeA(int value)
{
	typeA = bumpProperty(MINCARS, value, MAXCARS);
}

void Configuration::setTypeB(int value)
{
	typeB = bumpProperty(MINCARS, value, MAXCARS);
}

void Configuration::setTypeC(int value)
{
	typeC = bumpProperty(MINCARS, value, MAXCARS);
}

void Configuration::setCrossroads(int value)
{
	crossroads = bumpProperty(MINCROSSROADS, value, MAXCROSSROADS);
}

void Configuration::setSpeedLimit(int value)
{
	speedLimit = bumpProperty(MINSPEEDLIMIT, value, MAXSPEEDLIMIT);
}

void Configuration::setFriction(int value)
{
	friction = bumpProperty(FRICTIONASPHALTINDEX, value, FRICTIONGRASSINDEX);
}
