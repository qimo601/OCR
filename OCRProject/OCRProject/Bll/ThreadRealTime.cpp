#include "ThreadRealTime.h"
#include <QDebug>
ThreadRealTime::ThreadRealTime(QObject  *parent)
: QThread(parent)
{

}

ThreadRealTime::~ThreadRealTime()
{

}
void ThreadRealTime::run()
{
	qDebug() << "【USBThreadRealTime】启动ThreadRealTime,线程Id" << QThread::currentThreadId();

	qDebug() << "【ThreadRealTime】运行结束!";
	this->exec();

}