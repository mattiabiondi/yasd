#include "src/configuration.h"

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
	QFile file(fileName);

	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(nullptr, QString("yasd"),
				     QString("Cannot read file %1:\n%2.")
				     .arg(QDir::toNativeSeparators(fileName), file.errorString()));
		return nullptr;
	}

	QByteArray bytes = file.readAll();

	file.close();

	QJsonParseError jsonError;
	QJsonDocument document = QJsonDocument::fromJson(bytes, &jsonError);

	if (jsonError.error != QJsonParseError::NoError) {
		QMessageBox::warning(nullptr, QString("yasd"),
				     QString("Cannot parse from JSON:\n%1.")
				     .arg(jsonError.errorString()));
		return nullptr;
	}
	if (!document.isObject()) {
		QMessageBox::warning(nullptr, QString("yasd"),
				     QString("JSON object expected:\n%1."));
		return nullptr;
	}

	QJsonObject root = document.object();
	QScopedPointer<Configuration> config(new Configuration);

	if (root.contains("cars")) {
		QJsonObject cars = root.value("cars").toObject();
		config->setRed(cars.take("red").toInt());
		config->setGreen(cars.take("green").toInt());
		config->setBlue(cars.take("blue").toInt());
	}

	if (root.contains("map")) {
		QJsonObject map = root.value("map").toObject();
		config->setCrossroads(map.take("crossroads").toInt());
		config->setSpeedLimit(map.take("speedLimit").toInt());
		config->setFriction(map.take("friction").toInt());
	}
	return config.take();
}

Configuration *Configuration::create()
{
	QScopedPointer<Configuration> config(new Configuration);

	return config.take();
}

bool Configuration::save(const QString &fileName)
{
	QJsonObject root;

	QJsonObject cars;

	cars.insert("red", getRed());
	cars.insert("green", getGreen());
	cars.insert("blue", getBlue());

	QJsonObject map;

	map.insert("crossroads", getCrossroads());
	map.insert("speedLimit", getSpeedLimit());
	map.insert("friction", getFriction());

	root.insert("cars", cars);
	root.insert("map", map);

	QJsonDocument document;

	document.setObject(root);

	QByteArray bytes = document.toJson(QJsonDocument::Indented);

	QString errorMessage;

	QSaveFile file(fileName);

	if (file.open(QFile::WriteOnly | QFile::Text)) {
		QTextStream out(&file);
		out.setCodec("utf-8");
		out << bytes;
		if (!file.commit())
			errorMessage = QString("Cannot write file %1:\n%2.")
				       .arg(QDir::toNativeSeparators(fileName), file.errorString());
	} else {
		errorMessage = QString("Cannot open file %1 for writing:\n%2.")
			       .arg(QDir::toNativeSeparators(fileName), file.errorString());
	}

	if (!errorMessage.isEmpty()) {
		QMessageBox::warning(nullptr, QString("yasd"), errorMessage);
		return false;
	}

	return true;
}

void Configuration::setRed(int value)
{
	red = bumpProperty(MINCARS, value, MAXCARS);
}

void Configuration::setGreen(int value)
{
	green = bumpProperty(MINCARS, value, MAXCARS);
}

void Configuration::setBlue(int value)
{
	blue = bumpProperty(MINCARS, value, MAXCARS);
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
