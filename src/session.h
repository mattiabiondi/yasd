#ifndef YASD_SESSION_H
#define YASD_SESSION_H

#include <QObject>
#include <QAction>
#include <QTimer>

#include "src/application.h"

enum Status {
	// HALTED,
	RUNNING,
	STOPPED
};

class QAction;
class QTimer;

class Session: public QObject {
	Q_OBJECT

public:
	//static const int kNumSpeedLevels = 5;
	//static const int kMaxSpeed = kNumSpeedLevels - 1;

	Session();

	Status getStatus() const {
		return status;
	}

	bool isStopped() const {
		return status == STOPPED;
	}

	// bool isStoppedByUser() const {
	// 	return stoppedByUser;
	// }

	bool isRunning() const {
		return status == RUNNING;
	}

	// bool isStarted() const {
	// 	return status != MS_HALTED;
	// }

	// void halt();

	// unsigned int getStopMask() const {
	// 	return stopMask;
	// }

	// int getSpeed() const {
	// 	return speed;
	// }

	// Machine* getMachine() const {
	// 	return machine.get();
	// }
	//
	// SymbolTable* getSymbolTable() {
	// 	return symbolTable.get();
	// }
	//
	// StoppointSet* getBreakpoints() {
	// 	return &breakpoints;
	// }
	// StoppointListModel* getBreakpointListModel() {
	// 	return bplModel.get();
	// }
	//
	// StoppointSet* getSuspects() {
	// 	return &suspects;
	// }
	// StoppointSet* getTracepoints() {
	// 	return &tracepoints;
	// }
	//
	// const CpuStatusMap* getCpuStatusMap() const {
	// 	return cpuStatusMap.get();
	// }

	// Global actions
	// QAction* startAction;
	// QAction* haltAction;
	// QAction* toggleAction;
	QAction* resetAct;

	QAction* startAct;
	// QAction* stepAction;
	QAction* stopAct;
	QAction* toggleAct;

public slots:
	// void setStopMask(unsigned int value);
	// void setSpeed(int value);
	void stop();

signals:
	void statusChanged();
	void sessionStarted();
	void sessionStopped();
	void sessionRan();
	// void MachineHalted();
	void sessionReset();
	// void DebugIterationCompleted();

	// void SpeedChanged(int);

private:
	// static const uint32_t kMaxSkipped = 50000;

	void createActions();
	void setStatus(Status status);

	// void initializeMachine();

	// void step(unsigned int steps);
	// void runStepIteration();
	// void runContIteration();

	// void relocateStoppoints(const SymbolTable* newTable, StoppointSet& set);

	Status status;
	// scoped_ptr<Machine> machine;

	// scoped_ptr<SymbolTable> symbolTable;

	// We need a "proxy" stop mask here since it has to live through
	// machine reconfigurations, resets, etc.
	// unsigned int stopMask;

	// int speed;
	// static const unsigned int kIterCycles[kNumSpeedLevels];
	// static const unsigned int kIterInterval[kNumSpeedLevels];

	// StoppointSet breakpoints;
	// scoped_ptr<StoppointListModel> bplModel;
	// StoppointSet suspects;
	// StoppointSet tracepoints;
	//
	// scoped_ptr<CpuStatusMap> cpuStatusMap;
	//
	// bool stoppedByUser;
	//
	// bool stepping;
	// unsigned int stepsLeft;

	QTimer* timer;
	// QTimer* idleTimer;

	// uint32_t idleSteps;

private slots:
	void configurationChanged();

	void start();
	// void haltMachine();
	void toggle();
	void reset();
	// void continue();
	// void onStep();
	// void toggleDebug();
	//
	void updateActions();
	//
	// void runIteration();
	// void skip();
};

#endif // YASD_SESSION_H
