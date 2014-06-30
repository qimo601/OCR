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
    //线程start(),默认执行run()函数
    void run();
private slots:
    //获取服务器接收到的数据
    void getServerMessageList(QStringList);
signals:
    //发送网络数据信号
    void sendNetInfoSignal(QStringList);

private:

    QStringList messageList;


    
};

#endif
