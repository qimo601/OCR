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
	qDebug() << "��USBThreadRealTime������ThreadRealTime,�߳�Id" << QThread::currentThreadId();

	qDebug() << "��ThreadRealTime�����н���!";
	this->exec();

}