#ifndef THREADREALTIME_H
#define THREADREALTIME_H

#include <QThread>

class ThreadRealTime : public QThread
{
	Q_OBJECT

public:
	ThreadRealTime(QObject  *parent = 0);
	~ThreadRealTime();
	void run();
private:
	
};

#endif // THREADREALTIME_H
