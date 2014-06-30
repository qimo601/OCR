/**
*
* 项   目:   PET/CT软件 通信模块
* 文件名称:  TcpSocket.h
* 文件路径： NetworkCommunication/TcpSocket.h
* 摘   要:   socket通讯类，主要实现发起新连接，
*            读取客户端数据，发送数据等功能
* 作   者：  刘兆邦
* 完成日期： 2011年11月23日
* 修改人:    刘兆邦
* 修改内容： 删除冗余函数getMessageList()、
* 修改日期： 2012-09-06
* Copyright (c) 2011-2012, 中科院苏州医工所医学影像室电子组.All rights reserved.
* Version v2.0
*/

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>
//#include "ui_formserver.h"
#include <QStringList>

class TcpSocket : public QTcpSocket
{
    Q_OBJECT

public:
    //默认参数decriptor,tcpServer建立连接时，需要传值给TcpSocket的socketDescriptorEternal成员
    TcpSocket(int descriptor = -1, QObject *parent = 0);
    ~TcpSocket();
    //获取永久描述符
    int getSocketDescriptorEternal()
    {
        return socketDescriptorEternal;
    }
    //设置永久描述符
    void setSocketDescriptorEternal(int descriptor)
    {
        socketDescriptorEternal = descriptor;
    }

public slots:

    //连接通信服务端
    void connectToRemoteHost(QString,qint32);
    //获取TcpSocket中的数据
    void readMessage();
	//读取套接字内所有数据
	void readAllMessage();
	//读取套接字所有数据至指定数组
	void readAllMessage(QByteArray& result, int& descrip);
    //发送数据给TcpSocket
    qint64 sendMessage(QByteArray&);
    //连接上后，槽函数处理
    void connectedSlot();
    //断开连接后，槽函数处理
    void disconnectedSlot();

	//**********废弃************//
    //socket出错
    void TcpSocketError(QAbstractSocket::SocketError);
    //获取TcpSocketState
    void getTcpSocketState(QAbstractSocket::SocketState);
	//**********废弃************//

signals:
    //信号:socket读数据成功，并传递数据
    void haveReadDataSignal(QByteArray,int);
    //信号:socket已断开信号，在未删除之前.有描述符
    void disconnectedBeforeDeleteSignal(int);
    //信号:socket已连接，有描述符
    void connectedSignal(int);
	
    //信号:有一个socket已连接信号，专为服务端发送
    void connectedForServerSignal(int);

	//**********废弃************//
    //信号:错误信号
    void tcpSocketErrorSignal(QAbstractSocket::SocketError);
	//**********废弃************//
private:

    //socket接收到的数据大小,不包含本身值的2个字节
    qint32 nextBlockSize;
    //此socket 永久描述符，需要初始化.在socket断开等状态发生改变后，该描述符仍不变
    int socketDescriptorEternal;


};

#endif
