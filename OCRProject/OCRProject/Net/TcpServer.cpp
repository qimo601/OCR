/**
*
* 项    目:  PET/CT软件 通信模块
* 文件名称:  TcpServer.cpp
* 文件路径： NetworkCommunication/TcpServer.cpp
* 摘    要:  通信服务类程序
* 作    者： 刘兆邦
* 完成日期： 2011年11月23日
* 修改人：   刘兆邦
* 修改内容： 添加日志、修改部分程序
* 修改日期： 2012年09月05日
* Copyright (c) 2011-2012, 中科院苏州医工所医学影像室电子组.All rights reserved.
* Version v2.0
*/
#include <QtCore>
#include "TcpSocket.h"
#include "TcpServer.h"
#include "Include/Global.h"
TcpServer::TcpServer(QObject *parent)
    : QTcpServer(parent)
{

}



TcpServer::~TcpServer()
{

}
/**
 *函数介绍:启动通信服务端
 *输入参数:无
 *返回值:无
 */
void TcpServer::start(int port)
{
    if(listen(QHostAddress::Any,port))
    {
        qDebug()<< "TcpServer start ThreadId:" << QThread::currentThreadId();
		//写入系统日志
		//Global::systemLog->append(tr("网络通信服务端启动监听成功."), QString(tr("监听端口port: %1.")).arg(port), SystemLog::INFO);
        qDebug() << "服务端启动监听成功";
        emit startSuccessSignal();
        //服务端有新连接，输出服务器当前连接
        //connect(this, SIGNAL(newConnection()), this, SLOT(getAllConnection()));
		
    }
    else
    {
		//写入系统日志
		//Global::systemLog->append(tr("网络通信服务端启动监听失败."), QString(tr("监听端口port: %1.")).arg(port), SystemLog::INFO);
        //监听本地主机的port端口，如果出错就输出错误信息，并关闭
        qDebug() << "启动服务端监听失败";
        //停止监听
        stop();
        emit startFailSignal();
    }
}
/**
 *函数介绍:停止通信服务端
 *输入参数:无
 *返回值:无
 */
void TcpServer::stop()
{

	QString serverAddress = this->serverAddress().toString();
	int serverPort = this->serverPort();
    close();
	//写入系统日志
	//Global::systemLog->append(tr("网络通信服务端停止监听."), QString(tr("本地IP%1:,监听端口port:%2.")).arg(serverAddress).arg(serverPort), SystemLog::INFO);
    emit stopSuccessSignal();
}
/**
 *函数介绍:有请求连接，新建一个socket
 *输入参数:int socketId,新建socket的SocketDescriptor
 *返回值:无
 */
void TcpServer::incomingConnection(int socketId)
{
    TcpSocket *socket = new TcpSocket(socketId,this);
	//设置socket描述符
    socket->setSocketDescriptor(socketId);
	//写入系统日志
	//Global::systemLog->append(tr("网络通信服务端有新的连接请求"), QString(tr("服务端接收新的连接请求,socket描述符 = %1.")).arg(socketId), SystemLog::INFO);

    qDebug()<<"服务端有新的连接,socketDescriptor:"<<socket->socketDescriptor();
    //新建了一个socket连接
    addServerSocket(socketId);


    //获得客户端数据
    connect(socket, SIGNAL(haveReadDataSignal(QByteArray,int)), this, SLOT(getClientMessage(QByteArray,int)));
	//信号槽:跟踪服务端Socket状态
    connect(socket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(getServerSocketState(QAbstractSocket::SocketState)));
    //信号槽:服务端socket出现错误
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(serverSocketError(QAbstractSocket::SocketError)));

    //与客户端断开某socket连接，服务端状态发生改变
    connect(socket, SIGNAL(disconnectedBeforeDeleteSignal(int)), this, SLOT(removeServerSocket(int)));
    //与客户端断开连接，输出服务器当前连接
    //connect(socket, SIGNAL(disconnectedBeforeDeleteSignal(int)), this, SLOT(getAllConnection()));	
	//与客户端连接上后，输出服务器当前连接
    //connect(socket, SIGNAL(connectedForServerSignal(int)), this, SLOT(getAllConnection()));
    //与客户端连接上后，输出服务器当前连接
    //connect(socket, SIGNAL(connectedForServerSignal(int)), this, SLOT(addServerSocket(int)));

}
/**
 *函数介绍:获得客户端数据
 *输入参数:接收到的字节数组 result,服务端套接字描述符 descriptor
 *返回值:无
 */
void TcpServer::getClientMessage(QByteArray result,int descriptor)
{
    //接收到的字节数组
    QByteArray resultArray = result ;
    QDataStream in(resultArray);
    in.setVersion(QDataStream::Qt_4_6);
    //网络字节序　Little endian：将低序字节存储在起始地址  Big endian：将高序字节存储在起始地址
    in.setByteOrder(QDataStream::LittleEndian);
    //长度
    qint32 length;
    //目标设备ID
    qint32 destEquipId;
    //源设备Id
    qint32 sourceEquipID;
    //命令
    qint32 cmd ;
    length = resultArray.size();
    in >> destEquipId;
    in >> sourceEquipID;
    in >> cmd;
	QString destEquipName = Global::getComputerDeviceName(destEquipId);
	QString sourceEquipName = Global::getComputerDeviceName(sourceEquipID);
    //qDebug() << "tcpServer 得到客户端数据大小length:" <<length << "cmd" << cmd;
    //服务器接收到数据，发送信号
    //扫描类命令的回复
    if( cmd >= 0x0000 && cmd <= 0x0050)
    {
        emit haveScanSignal(resultArray,descriptor);
		qDebug() << QString("服务端得到扫描类命令,命令:%1,目标机器:%2,源设备:%3,命令长度:%4").arg(cmd).arg(destEquipName).arg(sourceEquipName).arg(length);
		//写入系统日志
		//Global::systemLog->append(QString(tr("服务端得到扫描类命令,命令:%1")).arg(cmd), QString("服务端得到扫描类命令：命令:%1,目标机器:%2,源设备:%3,命令长度:%4").arg(cmd).arg(destEquipName).arg(sourceEquipName).arg(length), SystemLog::LOG);

	}
    //床类命令的回复
    else if( cmd >= 0x0051 && cmd <= 0x00A0)
    {
		qDebug() << QString("服务端得到床类命令,命令:%1,目标机器:%2,源设备:%3,命令长度:%4").arg(cmd).arg(destEquipName).arg(sourceEquipName).arg(length);
		//写入系统日志
		//Global::systemLog->append(QString(tr("服务端得到床类命令,命令:%1")).arg(cmd), QString("服务端得到扫描类命令：命令:%1,目标机器:%2,源设备:%3,命令长度:%4").arg(cmd).arg(destEquipName).arg(sourceEquipName).arg(length), SystemLog::LOG);

    }
    //其他类命令的回复
    else
    {
		qDebug() << QString("服务端得到其它类命令,命令:%1,目标机器:%2,源设备:%3,命令长度:%4").arg(cmd).arg(destEquipName).arg(sourceEquipName).arg(length);
		//写入系统日志
		//Global::systemLog->append(QString(tr("服务端得到其它类命令,命令:%1")).arg(cmd), QString("服务端得到扫描类命令：命令:%1,目标机器:%2,源设备:%3,命令长度:%4").arg(cmd).arg(destEquipName).arg(sourceEquipName).arg(length), SystemLog::LOG);

    }

}
/**
 *函数介绍:回复客户端数据
 *输入参数:回复数据QByteArray result,套接字描述符 descriptor
 *返回值:无
 */
void TcpServer::replyClientMessage(QByteArray result,int descriptor)
{
    TcpSocket *serverSocket;
    if(descriptor!=-1)
    {
        //获得服务端套接字
        serverSocket = getServerSocket(descriptor);
        //发送数据
        if(serverSocket)
			serverSocket->sendMessage(result);
		qDebug()<<"正在回复数据。。。。。。";
    }
}

/**
 *函数介绍:获取服务器上指定描述符的socket指针
 *输入参数:descriptor，socket描述符.
 *返回值:如果找到指定socket，则返回该指针；否则返回0.
 */
TcpSocket* TcpServer::getServerSocket(int descriptor)
{
    //获取tcpServer所有serverSocket对象
    QList<TcpSocket*> serverSocketList = this->findChildren<TcpSocket*>();
    for (int i=0;i<serverSocketList.count();i++)
    {
        TcpSocket *item = serverSocketList.at(i);
        //如果找到指定socket，则返回该指针
        if(item->socketDescriptor()== descriptor)
        {
            //qDebug() << "已寻找到通信服务端上socket指针 socketDescriptor:" << item->socketDescriptor();
            return item;
        }


    }
    qDebug() << "未寻找到通信服务端上socket指针";
    //未找到指定socket，返回0
    return 0;
}

/**
 *函数介绍:获取服务器所有挂起连接
 *输入参数:无
 *返回值:无
 */
void TcpServer::getAllConnection()
{
    //获取tcpServer所有serverSocket对象
    QList<TcpSocket*> serverSocketList = this->findChildren<TcpSocket*>();

    int count = 0;
    for (int i=0;i<serverSocketList.count();i++)
    {
        QTcpSocket *item = serverSocketList.at(i);
        if(item->socketDescriptor()!= -1)
        {
            qDebug() << "服务器正在挂起的socket连接 socketDescriptor:" << item->socketDescriptor();
            count++;
        }
    }
    qDebug() << "共有" <<count <<"个客户端连接到本服务器";
}
/**
 *函数介绍:tcpServer 添加socket
 *输入参数:descriptor,改变状态的socket描述符
 *返回值:无
 */
void TcpServer::addServerSocket(int descriptor)
{
    //tcpServer发出添加一个serverSocket信号
    emit addServerSocketSignal(descriptor);
    qDebug()<<"tcpServer发出添加一个serverSocket信号";
    getAllConnection();
}

/**
 *函数介绍:tcpServer 移除socket
 *输入参数:descriptor,改变状态的socket描述符
 *返回值:无
 */
void TcpServer::removeServerSocket(int descriptor)
{
    //tcpServer发出移除了一个serverSocket信号
    emit removeServerSocketSignal(descriptor);
    qDebug()<<"tcpServer发出移除了一个serverSocket信号";
    getAllConnection();
}
/**
 *函数介绍:跟踪server端socket状态
 *输入参数:服务端socket状态
 *返回值:无
 */
void TcpServer::getServerSocketState(QAbstractSocket::SocketState socketState)
{
	QTcpSocket *serverSocket = qobject_cast<QTcpSocket *>(sender());
	QString clientIp = serverSocket->peerAddress().toString();
	int clientPort = serverSocket->peerPort();
	QString serverIp = this->serverAddress().toString();
	int serverPort = this->serverPort();
	//测试代码  是否和上面的一样的Ip和port???
	QString serverIp1 = serverSocket->localAddress().toString();
	int serverPort1 = serverSocket->localPort();
	//测试代码
    switch (socketState)
    {
    case QAbstractSocket::UnconnectedState: 
		qDebug() << "服务端：UnconnectedState:The socket is not connected.";
		//Global::systemLog->append(QString(tr("网络服务端状态：断开连接状态,未连上客户端Socket.客户端IP:%1")).arg(clientIp), QString(tr("与客户端计算机断开连接，客户端IP:%1,port:%2,UnconnectedState:The socket is not connected.")).arg(clientIp).arg(clientPort), SystemLog::INFO);
		break;
    case QAbstractSocket::HostLookupState: 
		qDebug()  << "服务端：HostLookupState:The socket is performing a host name lookup.";
		//Global::systemLog->append(QString(tr("网络服务端状态：正在查询计算机中......客户端IP:%1")).arg(clientIp), QString(tr("正在查询客户端计算机IP:%1,port:%2,HostLookupState:The socket is performing a host name lookup.")).arg(clientIp).arg(clientPort), SystemLog::INFO);
		break;
	case QAbstractSocket::ConnectingState: 
		qDebug()  << "服务端：ConnectingState:The socket has started establishing a connection.";
		//Global::systemLog->append(QString(tr("网络服务端状态：正在创建网络连接......客户端IP:%1")).arg(clientIp), QString(tr("正在创建网络连接，客户端计算机IP:%1,port:%2,ConnectingState:The socket has started establishing a connection.")).arg(clientIp).arg(clientPort), SystemLog::INFO);
		break;
	case QAbstractSocket::ConnectedState: 
		qDebug()  << "服务端：ConnectedState:A connection is established."; 
		//Global::systemLog->append(QString(tr("网络服务端状态：TCP连接创建成功.客户端IP:%1")).arg(clientIp), QString(tr("网络已经连接成功，客户端计算机IP:%1,port:%2,ConnectedState:A connection is established.")).arg(clientIp).arg(clientPort), SystemLog::INFO);
		break;
    case QAbstractSocket::BoundState: 
		qDebug()  << "服务端：BoundState:The socket is bound to an address and port (for servers)."; 
		//Global::systemLog->append(QString(tr("网络服务端状态：服务端已绑定TCP Socket.服务端IP:%1,port:%2.")).arg(serverIp).arg(serverPort), QString(tr("网络已经连接成功，本地服务端IP:%1,port:%2,客户端计算机IP:%3,port:%4,BoundState:The socket is bound to an address and port (for servers).")).arg(serverIp).arg(serverPort).arg(clientIp).arg(clientPort), SystemLog::INFO);
		break;
    case QAbstractSocket::ClosingState: 
		qDebug()  << "服务端：ClosingState:The socket is about to close (data may still be waiting to be written)."; 
		//Global::systemLog->append(QString(tr("网络服务端状态：即将关闭一个TCP Socket.客户端IP:%1")).arg(clientIp), QString(tr("网络即将关闭,远程计算机IP:%1,port:%2,ClosingState:The socket is about to close (data may still be waiting to be written).")).arg(clientIp).arg(clientPort), SystemLog::INFO);
		break;
	case QAbstractSocket::ListeningState: 
		qDebug()  << "服务端：ListeningState:For internal use only."; 
		//Global::systemLog->append(QString(tr("网络服务端状态：Socket侦听状态.客户端IP:%1")).arg(clientIp), QString(tr("网络侦听状态,远程计算机IP:%1,port:%2")).arg(clientIp).arg(clientPort), SystemLog::INFO);
		break;
    default: 
		qDebug()<<"服务端：网络其他状态";
		//Global::systemLog->append(QString(tr("网络服务端状态：其他状态.客户端IP:%1")).arg(clientIp), QString(tr("网络其他状态,远程计算机IP:%1,port:%2")).arg(clientIp).arg(clientPort), SystemLog::INFO);
    }

	serverSocket = 0;
}


/**
 *函数介绍:服务端socket出错
 *输入参数:无
 *返回值:  无
 */
void TcpServer::serverSocketError(QAbstractSocket::SocketError socketError)
{
	QTcpSocket *serverSocket = qobject_cast<QTcpSocket *>(sender());
	QString clientIp = serverSocket->peerAddress().toString();
	int clientPort = serverSocket->peerPort();
	QString serverIp = this->serverAddress().toString();
	int serverPort = this->serverPort();

    emit serverSocketErrorSignal(socketError);
	switch (socketError)
    {
    case QAbstractSocket::ConnectionRefusedError:  
		//Global::systemLog->append(QString(tr("网络服务端出错：拒绝连接.")).arg(clientIp), QString(tr("客户端计算机IP:%1,port:%2拒绝连接,The connection was refused by the peer (or timed out).")).arg(clientIp).arg(clientPort), SystemLog::ERROR);
		break;
    case QAbstractSocket::RemoteHostClosedError:   
		//Global::systemLog->append(QString(tr("网络服务端出错：远程主机关闭了连接.")).arg(clientIp), QString(tr("客户端计算机IP:%1,port:%2关闭了SOCKET连接,服务端SOCKET也即将关闭,The remote host closed the connection. ")).arg(clientIp).arg(clientPort), SystemLog::ERROR);
		break;
    case QAbstractSocket::HostNotFoundError:   
		//Global::systemLog->append(QString(tr("网络服务端出错：找不到远程主机.")).arg(clientIp), QString(tr("找不到客户端计算机IP:%1,port:%2,The host address was not found. ")).arg(clientIp).arg(clientPort), SystemLog::ERROR);
		break;
	case QAbstractSocket::SocketResourceError:  
		//Global::systemLog->append(QString(tr("网络服务端出错：Socket资源不够.")).arg(clientIp), QString(tr("本地Socket资源不够，客户端计算机IP:%1,port:%2,The local system ran out of resources (e.g., too many sockets). ")).arg(clientIp).arg(clientPort), SystemLog::ERROR);
		break;
    case QAbstractSocket::SocketTimeoutError:  
		//Global::systemLog->append(QString(tr("网络服务端出错：操作超时.")).arg(clientIp), QString(tr("服务端网络操作超时，客户端计算机IP:%1,port:%2,The socket operation timed out. ")).arg(clientIp).arg(clientPort), SystemLog::ERROR);
		break;
	case QAbstractSocket::DatagramTooLargeError:  
		//Global::systemLog->append(QString(tr("网络服务端出错：数据包过大.")).arg(clientIp), QString(tr("服务端网络数据包过大，客户端计算机IP:%1,port:%2,The socket operation timed out. ")).arg(clientIp).arg(clientPort), SystemLog::ERROR);
		break;
	case QAbstractSocket::NetworkError:  
		//Global::systemLog->append(QString(tr("网络服务端出错：计算机网络出错.")).arg(clientIp), QString(tr("网络出错，可能网线断开了，客户端计算机IP:%1,port:%2,The datagram was larger than the operating system's limit (which can be as low as 8192 bytes).")).arg(clientIp).arg(clientPort), SystemLog::ERROR);
		break;
    default:
		int i = 0;
		//Global::systemLog->append(QString(tr("网络服务端出错：未知错误,SocketError:%2")).arg(clientIp).arg(socketError), QString(tr("未知错误，客户端计算机IP:%1,port:%2")).arg(clientIp).arg(clientPort), SystemLog::ERROR);

    }
    qDebug() << "服务端socket出错";
}
