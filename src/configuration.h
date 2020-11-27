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

void setTypeA(int value);
int getTypeA() const
{
	return typeA;
}

void setTypeB(int value);
int getTypeB() const
{
	return typeB;
}

void setTypeC(int value);
int getTypeC() const
{
	return typeC;
}

void setCrossroads(int value);
int getCrossroads() const
{
	return crossroads;
}

void setSpeedLimit(int value);
int getSpeedLimit() const
{
	return speedLimit;
}

void setFriction(int value);
int getFriction() const
{
	return friction;
}

private:
int typeA;
int typeB;
int typeC;
int crossroads;
int speedLimit;
int friction;
};

#endif // YASD_CONFIG_H
