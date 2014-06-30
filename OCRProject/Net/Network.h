/**
*
* 项   目:  PET/CT软件 应用层程序
* 文件名称:  Network.h
* 文件路径： NetworkCommunication/Network.h
* 摘   要:  网络通信模块类，向其它模块提供接口：
*
* 作   者： 刘兆邦
* 完成日期： 2011年11月28日
* 修改人：刘兆邦
* 修改内容：添加系统日志、修改函数名、划分客户端和服务端
* 修改日期：2012年09月03日
* Copyright (c) 2011, 中科院苏州医工所医学影像室电子组.
* All rights reserved.
* Version v2.0
*/

// 源代码编码必须是: UTF-8(BOM)  
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef NETWORK_H
#define NETWORK_H
#include "TcpSocket.h"
#include "TcpServer.h"
#include "NetServerThread.h"

class Network : public QObject
{
    Q_OBJECT

public:

	//构造函数
    Network(QString name = "无名", QString ip = "127.0.0.1", int port = 6666, QObject *parent = 0);
    ~Network();
	
	

	 //获取网络客户端名称
    QString getClientName()
    {
        return clientName;
    }
    //设置网络客户端名称
    void setClientName(QString mClientName)
    {
        clientName = mClientName;
    }
    //获取clientSocket
    TcpSocket* getClientSocket()
    {
        return clientSocket;
    }
    //设置clientSocket
    void setClientSocket(TcpSocket* socket)
    {
        clientSocket = socket;
    }
    

    //获取远程服务器计算机名
    QString getRemoteHostName()
    {
        return remoteHostName;
    }
    //设置远程服务器计算机名
    void setRemoteHostName(QString name)
    {
        remoteHostName = name;
    }
    //获取远程服务器IP
    QString getRemoteHostIp()
    {
        return remoteHostIp;
    }
    //设置远程服务器IP
    void setRemoteHostIp(QString ip)
    {
        remoteHostIp = ip;
    }
    //获取远程服务器port
    qint32 getRemoteHostPort()
    {
        return remoteHostPort;
    }
    //设置远程服务器port
    void setRemoteHostPort(qint32 port)
    {
        remoteHostPort = port;
    }

    //获取本地计算机名
    QString getLocalName()
    {
        return localName;
    }
    //设置本地计算机名
    void setLocalName(QString name)
    {
        localName = name;
    }
    //获取本地IP
    QString getLocalIp()
    {
        return localIp;
    }
    //设置本地IP
    void setLocalIp(QString ip)
    {
        localIp = ip;
    }

    //获取本地port
    qint32 getLocalPort()
    {
        return localPort;
    }
    //设置本地port
    void setLocalPort(qint32 port)
    {
        localPort = port;
    }


public slots:

	//初始化本地计算机信息
	void initComputerInfo();
	//初始化客户端
	void initClient();
	//初始化服务端
	void initServer();
	//客户端发送数据
	quint64 sendData(QByteArray&, bool);
	//阻塞客户端等待返回数据
	bool waitForReadyRead(int msecs = 30000);
	//读取套接字中返回的所有数据
	void readAllMessage(QByteArray& result, int& descriptor);
	//客户端socket是否已经连上服务端
	bool isConnectedToServer();
	//启动通信服务端. true:启动成功,false:启动失败
	bool startServer(int);
	//停止信服务端
	bool stopServer();
    //获取客户端Socket状态
    void getClientSocketState(QAbstractSocket::SocketState);
    //连接服务器
    TcpSocket* connectToHost(QString, qint32);
    //断开连接远程服务端
    void disConnectToHost();
    //客户端接收发来的数据
    void clientReceiveData(QByteArray, int);
    
    //客户端连接服务端成功
    void clientSocketConnectSuccess(int);
	//客户端socket断开连接成功
	void clientSocketDisconnect(int);
    //客户端socket出错
    void clientSocketError(QAbstractSocket::SocketError);
	void disconnectSlot();
signals:
   
    //信号: 客户端从服务端得到数据-特例
    void clientReceiveDataSignal(QByteArray, int);
    //信号：客户端得到扫描类命令回复
    void clientReceiveScanReplySignal(QByteArray,int);
    //信号：客户端得到床参数类回复
    void clientReceiveTableReplySignal(QByteArray,int);	
	//信号：客户端得到重建参数类回复
	void clientReceiveReconReplySignal(QByteArray,int);

    //信号: 客户端连接服务端成功，供业务层使用
    void connectToHostSuccessSignal();
	//信号: 客户端断开连接成功，供业务层使用
	void disConnectToHostSuccessSignal();
    //信号: 客户端出错信号
    void clientSocketErrorSignal(QAbstractSocket::SocketError);

	//信号: 启动TcpServer
    void startTcpServerSignal(int);
    //信号: 停止TcpServer
    void stopTcpServerSignal();
	//断开
	void disconnected();

public:
    //全局：本地服务端对象
    static TcpServer *tcpServer;
    //全局：本地服务端通信线程
    static NetServerThread *netServerThread;

private:
	//网络客户端名称
	QString clientName;  
	//本地计算机名
    QString localName;
    //本地Ip
    QString localIp;
    //监听端口Port
    qint32 localPort;
    //存储服务端接收到，并传送过来的数据
    QStringList messageList;
    //远程服务器计算机名
    QString remoteHostName;
    //远方服务器Ip
    QString remoteHostIp;
    //远方服务器Port
    qint32 remoteHostPort;
   
    //客户端套接字(每个Network实例化对象，只能有一个clientSocket).
    TcpSocket* clientSocket;

	//********废弃变量*******//
	
	//*********废弃变量******//

};



#endif // NETWORK_H
