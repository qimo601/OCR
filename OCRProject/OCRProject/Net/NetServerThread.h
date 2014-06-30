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

#ifndef NETSERVERTHREAD_H
#define NETSERVERTHREAD_H

#include <QThread>
#include "TcpServer.h"

class NetServerThread : public QThread
{
    Q_OBJECT

public:
    NetServerThread(QObject *parent = 0);
    ~NetServerThread();
    //�߳�start(),Ĭ��ִ��run()����
    void run();
private slots:
    //��ȡ���������յ�������
    void getServerMessageList(QStringList);
signals:
    //�������������ź�
    void sendNetInfoSignal(QStringList);

private:

    QStringList messageList;


    
};

#endif
