#ifndef YASD_CONFIG_H
#define YASD_CONFIG_H

#include <QString>
#include <QScopedPointer>

#include "const.h"

class Configuration {
public:

static Configuration *loadFromFile(const QString &fileName, QString &error);
static Configuration *create(const QString &fileName);
bool save(const QString &fileName);
const QString& getFileName() const
{
	return fileName;
}

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
Configuration(const QString &fileName);

QString fileName;

int typeA;
int typeB;
int typeC;
int crossroads;
int speedLimit;
int friction;
};

#endif // YASD_CONFIG_H
