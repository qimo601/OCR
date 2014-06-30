/**
*
* ��   Ŀ:  PET/CT��� ͨ��ģ��
* �ļ�����:  NetServerThread.cpp
* �ļ�·���� NetworkCommunication/NetServerThread.cpp
* ժ   Ҫ:  ͨ���߳�
* ��   �ߣ� ���װ�
* ������ڣ� 2011��11��23��
* Copyright (c) 2011, �п�Ժ����ҽ����ҽѧӰ���ҵ�����.All rights reserved.
* Version v1.0
*/
#include "NetServerThread.h"
#include <QMessageBox>

NetServerThread::NetServerThread(QObject *parent)
    : QThread(parent)
{

}



NetServerThread::~NetServerThread()
{

}

/**
 *�������ܣ��߳�start()֮��,Ĭ��ִ��run()����
 *�����������
 *����ֵ��
 */ 
void NetServerThread::run()
{
//    qDebug() <<"NetServerThread run ID:"<<currentThreadId();
//    tcpServer.start();
//    connect(&tcpServer, SIGNAL(haveRecSignal(QStringList)), this, SLOT(getServerMessageList(QStringList)));
    //�����¼�ѭ�����ȴ�exit()��call
    this->exec();

}

void NetServerThread::getServerMessageList(QStringList list)
{
    messageList = list ;
    emit sendNetInfoSignal(messageList);
}
