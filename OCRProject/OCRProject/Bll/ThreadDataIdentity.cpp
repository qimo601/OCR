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
	qDebug() << "��ThreadDataIdentity������ThreadDataIdentity,�߳�Id" << QThread::currentThreadId();

	qDebug() << "��ThreadDataIdentity�����н���!";
	this->exec();

}