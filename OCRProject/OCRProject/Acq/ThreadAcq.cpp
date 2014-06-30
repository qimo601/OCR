#include "ThreadAcq.h"
#include <QDebug>
ThreadAcq::ThreadAcq(QObject  *parent)
: QThread(parent)
{

}

ThreadAcq::~ThreadAcq()
{

}
void ThreadAcq::run()
{
	qDebug() << "【ThreadAcq】启动ThreadAcq,线程Id" << QThread::currentThreadId();

	qDebug() << "【ThreadAcq】运行结束!";
	this->exec();

}