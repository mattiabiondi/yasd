#ifndef YASD_CONFIG_H
#define YASD_CONFIG_H

#include <QString>
#include <QScopedPointer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QSaveFile>
#include <QDir>
#include <QMessageBox>

#include "src/const.h"

class Configuration {
public:

static Configuration *loadFromFile(const QString &fileName, QString &error);
static Configuration *create();
bool save(const QString &fileName);

void setRed(int value);
int getRed() const
{
	return red;
}

void setGreen(int value);
int getGreen() const
{
	return green;
}

void setBlue(int value);
int getBlue() const
{
	return blue;
}

void setCrossroads(int value);
int getCrossroads() const
{
	return crossroads;
}

void setLimit(int value);
int getLimit() const
{
	return limit;
}

void setFriction(int value);
int getFriction() const
{
	return friction;
}

private:
int red;
int green;
int blue;
int crossroads;
int limit;
int friction;
};

#endif // YASD_CONFIG_H
