/**
*
* 项   目:  PET/CT软件 通信模块
* 文件名称:  TcpServer.cpp
* 文件路径： NetworkCommunication/TcpServer.cpp
* 摘   要:  通信服务类程序
* 作   者： 刘兆邦
* 完成日期： 2011年11月23日
* 修改人：刘兆邦
* 修改内容：添加系统日志、修改函数名、删除冗余信号和函数、修改客户端关闭连接服务端崩溃bug
* 修改日期：2012年09月05日
* Copyright (c) 2011-2012, 中科院苏州医工所医学影像室电子组.All rights reserved.
* Version v2.0
*/
#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QStringList>
#include "TcpSocket.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT

public:
    TcpServer(QObject *parent = 0);
    ~TcpServer();

public slots:
    //获取指定描述符的socket指针
    TcpSocket* getServerSocket(int);
	//回复客户端信息
    void replyClientMessage(QByteArray,int);
    //增加一个serverSocket
    void addServerSocket(int);
    //移除一个serverSocket
    void removeServerSocket(int);
	//跟踪server端socket状态
	void getServerSocketState(QAbstractSocket::SocketState);
	//服务端socket出错
	void serverSocketError(QAbstractSocket::SocketError);
private slots:
    //获得客户端信息
    void getClientMessage(QByteArray,int);
    //开始服务器通讯,默认端口 = 6666
    void start(int = 6666);
    //停止服务器通讯
    void stop();
    //获取服务器所有挂起连接
    void getAllConnection();
signals:
    
    //信号: 启动服务端成功
    void startSuccessSignal();
    //信号: 启动服务端失败
    void startFailSignal();
    //信号: 停止服务端成功
    void stopSuccessSignal();
    //信号: 发出添加一个serverSocket信号
    void addServerSocketSignal(int);
    //信号：移除了一个serversocket
    void removeServerSocketSignal(int);
	//信号: 服务端socket出错信号
	void serverSocketErrorSignal(QAbstractSocket::SocketError);
	//**************持续添加按照通信命令类划分信号*********************//
	//信号：服务端接收到scan类命令参数
    void haveScanSignal(QByteArray,int);
	
	//**************持续添加按照通信命令类划分信号*********************//
private:
    
    //有新的请求连接
    void incomingConnection(int socketId);



};

#endif//TCPSERVER_H
