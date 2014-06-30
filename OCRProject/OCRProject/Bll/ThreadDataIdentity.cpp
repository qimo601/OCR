#include "ThreadDataIdentity.h"
#include <QDebug>
ThreadDataIdentity::ThreadDataIdentity(QObject  *parent)
: QThread(parent)
{

}

ThreadDataIdentity::~ThreadDataIdentity()
{

}
void ThreadDataIdentity::run()
{
	qDebug() << "【ThreadDataIdentity】启动ThreadDataIdentity,线程Id" << QThread::currentThreadId();

	qDebug() << "【ThreadDataIdentity】运行结束!";
	this->exec();

}