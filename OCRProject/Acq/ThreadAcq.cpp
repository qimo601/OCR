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
	qDebug() << "��ThreadAcq������ThreadAcq,�߳�Id" << QThread::currentThreadId();

	qDebug() << "��ThreadAcq�����н���!";
	this->exec();

}