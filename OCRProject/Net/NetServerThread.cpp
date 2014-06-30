/**
*
* 项   目:  PET/CT软件 通信模块
* 文件名称:  NetServerThread.cpp
* 文件路径： NetworkCommunication/NetServerThread.cpp
* 摘   要:  通信线程
* 作   者： 刘兆邦
* 完成日期： 2011年11月23日
* Copyright (c) 2011, 中科院苏州医工所医学影像室电子组.All rights reserved.
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
 *函数介绍：线程start()之后,默认执行run()函数
 *输入参数：无
 *返回值：
 */ 
void NetServerThread::run()
{
//    qDebug() <<"NetServerThread run ID:"<<currentThreadId();
//    tcpServer.start();
//    connect(&tcpServer, SIGNAL(haveRecSignal(QStringList)), this, SLOT(getServerMessageList(QStringList)));
    //启动事件循环，等待exit()被call
    this->exec();

}

void NetServerThread::getServerMessageList(QStringList list)
{
    messageList = list ;
    emit sendNetInfoSignal(messageList);
}
