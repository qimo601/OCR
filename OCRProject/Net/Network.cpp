/**
*
* 项   目:  PET/CT软件 应用层程序
* 文件名称:  Network.cpp
* 文件路径： NetworkCommunication/Network.cpp
* 摘   要:  网络通信模块类，向其它模块提供通讯服务接口：
*
* 作   者： 刘兆邦
* 完成日期： 2011年12月01日
* 修改人：刘兆邦
* 修改内容：添加系统日志、修改函数名、划分客户端和服务端
* 修改日期：2012年09月03日
* Copyright (c) 2011, 中科院苏州医工所医学影像室电子组.
* All rights reserved.
* Version v1.0
*/
#include "Network.h"
#include "TcpSocket.h"
#include "NetServerThread.h"
#include <QtNetwork>

/**
*函数介绍：构造函数
*输入参数：客户端名称:name,默认参数服务端ip:127.0.0.1,默认参数服务端端口:6666默认参数QObject *parent = 0
*返回值：无
*/
Network::Network(QString name, QString ip, int port, QObject *parent)
{
	this->clientName = name;
	this->remoteHostIp = ip;
	this->remoteHostPort = port;
	//初始化本地计算机信息
	initComputerInfo();
	//初始化客户端
	initClient();
	//初始化服务端
	initServer();

	//写入系统日志
	//Global::systemLog->append(QString(tr("初始化网络客户端:%1完毕.")).arg(clientName), QString(tr("初始化客户端:%1,并完成网络客户端与本地服务端程序相关联.")).arg(clientName), SystemLog::INFO);

}
Network::~Network()
{
	//释放
	delete clientSocket;
}
/**
*函数介绍：初始化客户端
*输入参数：无
*返回值：无
*/
void Network::initClient()
{
	//写入系统日志
	//Global::systemLog->append(QString(tr("初始化网络客户端:%1.....")).arg(clientName), clientName + tr("客户端初始化."), SystemLog::LOG);


	//新建一个客户端socket
	clientSocket = new TcpSocket();
	//初始化它的永久描述符，在断开后，未删除前仍有效
	clientSocket->setSocketDescriptorEternal(clientSocket->socketDescriptor());
	//信号槽:跟踪clientSocket状态
	connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(getClientSocketState(QAbstractSocket::SocketState)));
	//信号槽: 客户端接收远程计算机数据
	connect(clientSocket, SIGNAL(haveReadDataSignal(QByteArray, int)), this, SLOT(clientReceiveData(QByteArray, int)));
	//信号槽: 客户端连接服务器成功
	connect(clientSocket, SIGNAL(connectedSignal(int)), this, SLOT(clientSocketConnectSuccess(int)));
	//信号槽: 客户端关闭与服务器连接
	connect(clientSocket, SIGNAL(disconnectedBeforeDeleteSignal(int)), this, SLOT(clientSocketDisconnect(int)));
	//信号槽: 客户端socket出现错误
	connect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(clientSocketError(QAbstractSocket::SocketError)));

	connect(clientSocket, SIGNAL(disconnected()), this, SLOT(disconnectSlot()) );

	//写入系统日志
	//Global::systemLog->append(QString(tr("初始化网络客户端:%1结束.")).arg(clientName), clientName + tr("客户端初始化结束."), SystemLog::LOG);
}

void Network::disconnectSlot()
{
	emit disconnected();
}

/**
*函数介绍：初始化服务端程序
*输入参数：无
*返回值：无
*/
void Network::initServer()
{
	//写入系统日志
	//Global::systemLog->append(QString(tr("初始化网络客户端:%1与本地服务端相关联.....")).arg(clientName), tr("初始化本地网络服务端程序与客户端相关联."), SystemLog::LOG);
	//若获得启动服务端信号，tcpServer启动服务端
	connect(this, SIGNAL(startTcpServerSignal(int)), tcpServer, SLOT(start(int)));
	//若获得停止服务端信号，tcpServer停止服务端
	connect(this, SIGNAL(stopTcpServerSignal()), tcpServer, SLOT(stop()));
	//写入系统日志
	//Global::systemLog->append(QString(tr("初始化网络客户端:%1与网络服务端相关联结束.").arg(clientName)), tr("初始化本地网络服务端程序与客户端相关联."), SystemLog::LOG);
}
//定义静态数据成员 tcpServer，全局通信服务端
TcpServer* Network::tcpServer = new TcpServer();

//定义静态数据成员 netServerThread,全局通信服务端线程
NetServerThread* Network::netServerThread = new NetServerThread();


/**
*函数介绍:初始化本地计算机信息
*输入参数:无
*返回值:无
*/
void Network::initComputerInfo()
{
	QString localHostName = QHostInfo::localHostName();
	//设置本地计算机名
	setLocalName(localHostName);
	QHostInfo info = QHostInfo::fromName(localHostName);
	foreach(QHostAddress address, info.addresses())
	{
		if (address.protocol() == QAbstractSocket::IPv4Protocol)
		{
			//设置本地计算机IP
			setLocalIp(address.toString());
		}
	}
}
/**
*函数介绍:连接上服务端
*输入参数:(ip：计算机IP，port：端口)
*返回值: 返回socket指针
*/
TcpSocket* Network::connectToHost(QString ip, qint32 port)
{
	//远程服务器Ip
	remoteHostIp = ip;
	//远程服务器端口
	remoteHostPort = port;
	//写入系统日志
	//Global::systemLog->append(tr("连接远程服务端中......"), clientName + QString(tr("客户端连接远程服务端,ip = %1,port = %2.")).arg(ip).arg(port), SystemLog::INFO);
	//如客户端socket不存在，则新建一个
	if (clientSocket == 0)
	{
		//初始化客户端Socket
		initClient();
	}
	//连接远程计算机
	clientSocket->connectToRemoteHost(remoteHostIp, remoteHostPort);
	return clientSocket;
}
/**
*函数介绍:断开连接远程服务端
*输入参数:
*返回值: 无
*/
void Network::disConnectToHost()
{
	//如果clientSocket未关闭，断开连接，关闭Socket
	if (clientSocket != 0)
		clientSocket->disconnectFromHost();
	//删除该socket，实际在TcpSocket中的槽函数disconnectedSlot中，已经试图删除一次.
	//clientSocket->deleteLater();
	//delete clientSocket;
	//设置客户端socket指针为0;
	qDebug() << "大小" << clientSocket->bytesAvailable();
	clientSocket = 0;
}


/**
*函数介绍：客户端发送数据
*输入参数：
*        block：发送的有数据类型格式的数据
*        needClose:true,表示需要关闭该客户端;false,表示保持该客户端
*返回值： 该数据包的大小
*/
quint64 Network::sendData(QByteArray& block, bool needClose)
{
	quint64 sendLength = 0;
	//发送数据
	sendLength = clientSocket->sendMessage(block);
	//关闭客户端
	if (needClose)
	{
		//试着关闭socket，缓冲区有数据，尽量发送完毕后，再断开.然后发送disconnected()信号
		clientSocket->disconnectFromHost();
	}
	return sendLength;
}
/**
*函数介绍：客户端阻塞等待回复数据
*输入参数：
*        block：发送的有数据类型格式的数据
*        needClose:true,表示需要关闭该客户端;false,表示保持该客户端
*返回值： 该数据包的大小
*/
bool Network::waitForReadyRead(int msecs)
{
	
	return clientSocket->waitForReadyRead(msecs);
}

/**
* 函数介绍： 读取套接字所有数据
* 输入参数： 无
* 信号:发送接收到的数据，以及此套接字的描述符
* 返回值  ： 无
*/
void Network::readAllMessage(QByteArray& result, int& descriptor)
{
	clientSocket->readAllMessage(result,descriptor);
}
/**
*函数介绍：客户端是否已经连上服务端
*输入参数：
*返回值： 成功连上返回true,否则返回失败.
*/
bool Network::isConnectedToServer()
{
	int m = clientSocket->state();
	if (clientSocket->state() == 3)
		return true;
	else
		return false;
}
/**
*函数介绍：启动通信服务端
*输入参数：port:本地服务端监听端口
*返回值：  true,启动成功.false,启动失败
*/
bool Network::startServer(int port)
{
	localPort = port;
	//写入系统日志
	//Global::systemLog->append(tr("网络通信服务端正在启动......"), clientName + QString(tr("本地网络服务端启动,本地IP = %1,监听端口port = %2.")).arg(localIp).arg(localPort), SystemLog::INFO);

	//如果服务端通信没在监听
	if (!tcpServer->isListening())
	{
		tcpServer->moveToThread(netServerThread);

		netServerThread->start();
		//写入系统日志
		//Global::systemLog->append(tr("网络通信服务端线程已经启动."), clientName + QString(tr("本地网络服务端启动,本地IP = %1,监听端口port = %2.")).arg(localIp).arg(localPort), SystemLog::INFO);
		qDebug() << "服务器线程启动";
		//发出启动TcpServer信号
		emit startTcpServerSignal(port);

		return true;
	}
	else
	{
		//Global::systemLog->append(tr("网络通信服务端启动失败."), QString(tr("服务端目前已经在监听，或者本机端口%1已经被占用")).arg(localPort), SystemLog::ERROR);
		qDebug() << "网络通信服务端启动失败,服务端目前已经在监听，或者本机端口已经被占用";
		return false;
	}

}

/**
*函数介绍:停止信服务端
*输入参数:无
*返回值: true,启动成功.false,启动失败
*/
bool Network::stopServer()
{
	if (tcpServer->isListening())
	{
		//Global::systemLog->append(tr("正在停止监听......"), QString(tr("已经发出停止监听信号,正在试图停止服务端网络监听.")), SystemLog::INFO);
		//发出停止TcpServer信号，调用tcpServer槽函数stop()
		emit stopTcpServerSignal();
		qDebug() << "停止监听成功";
		return true;
	}
	else
	{
		qDebug() << "停止监听失败，可能服务端没有监听";
		//Global::systemLog->append(tr("停止监听失败."), QString(tr("停止监听失败，可能服务端没有启动监听.")), SystemLog::WARN);
		return false;
	}
}
/**
*函数介绍:获取客户端Socket状态
*输入参数:clientSocket状态
*返回值:  无
*/
void Network::getClientSocketState(QAbstractSocket::SocketState socketState)
{
	remoteHostName = clientSocket->peerAddress().toString();
	remoteHostIp = clientSocket->peerName();
	remoteHostPort = clientSocket->peerPort();
	switch (socketState)
	{
	case QAbstractSocket::UnconnectedState:
		qDebug() << "UnconnectedState:The socket is not connected.";
		//Global::systemLog->append(QString(tr("%1网络客户端状态：未连上.")).arg(clientName), QString(tr("未连上远程计算机IP:%1,port:%2,UnconnectedState:The socket is not connected.")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::INFO);
		break;
	case QAbstractSocket::HostLookupState:
		qDebug() << "HostLookupState:The socket is performing a host name lookup.";
		//Global::systemLog->append(QString(tr("%1网络客户端状态：正在查询主机中......")).arg(clientName), QString(tr("正在查询远程计算机IP:%1,port:%2,HostLookupState:The socket is performing a host name lookup.")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::INFO);
		break;
	case QAbstractSocket::ConnectingState:
		qDebug() << "ConnectingState:The socket has started establishing a connection.";
		//Global::systemLog->append(QString(tr("%1网络客户端状态：正在创建网络连接......")).arg(clientName), QString(tr("正在创建网络连接，远程计算机IP:%1,port:%2,ConnectingState:The socket has started establishing a connection.")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::INFO);
		break;
	case QAbstractSocket::ConnectedState:
		qDebug() << "ConnectedState:A connection is established.";
		//Global::systemLog->append(QString(tr("%1网络客户端状态：TCP连接创建成功.")).arg(clientName), QString(tr("网络已经连接成功，远程计算机IP:%1,port:%2,ConnectedState:A connection is established.")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::INFO);
		break;
	case QAbstractSocket::BoundState:
		qDebug() << "BoundState:The socket is bound to an address and port (for servers).";
		//Global::systemLog->append(QString(tr("%1网络客户端状态：服务端已绑定TCP Socket的IP和端口.")).arg(clientName), QString(tr("服务端已经绑定IP和端口，远程计算机IP:%1,port:%2,BoundState:The socket is bound to an address and port (for servers).")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::INFO);
		break;
	case QAbstractSocket::ClosingState:
		qDebug() << "ClosingState:The socket is about to close (data may still be waiting to be written).";
		//Global::systemLog->append(QString(tr("%1网络客户端状态：即将关闭状态.")).arg(clientName), QString(tr("网络即将关闭,远程计算机IP:%1,port:%2,ClosingState:The socket is about to close (data may still be waiting to be written).")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::INFO);
		break;
	case QAbstractSocket::ListeningState:
		qDebug() << "ListeningState:For internal use only.";
		//Global::systemLog->append(QString(tr("%1网络客户端状态：侦听状态")).arg(clientName), QString(tr("网络侦听状态,远程计算机IP:%1,port:%2")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::INFO);
		break;
	default:
		qDebug() << "网络其他状态";
		//Global::systemLog->append(QString(tr("%1网络客户端状态：其他状态.")).arg(clientName), QString(tr("网络其他状态,远程计算机IP:%1,port:%2")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::INFO);
	}
}

/**
*函数介绍:客户端的clientSocket接收服务端返回数据
*输入参数:QByteArray result:接收到的数据,int descriptor:套接字描述符
*返回值:  无
*修改：董月芳
*时间：2012.7.17
*修改内容：添加命令解析分支程序
*/
void Network::clientReceiveData(QByteArray result, int descriptor)
{
	//接收到的字节数组
	QByteArray resultArray = result;//客户端接收到数据，发送信号
	emit clientReceiveDataSignal(resultArray, descriptor);
	// qDebug() << "Network:得到回复，socket描述符"<< descriptor;
}

/**
*函数介绍:客户端socket连接成功
*输入参数:descriptor:socket描述符
*返回值:  无
*/
void Network::clientSocketConnectSuccess(int descriptor)
{
	remoteHostName = clientSocket->peerAddress().toString();
	remoteHostIp = clientSocket->peerName();
	remoteHostPort = clientSocket->peerPort();
	emit connectToHostSuccessSignal();
	//写入系统日志
	//Global::systemLog->append(tr("客户端连接远程主机成功"), clientName + QString(tr("客户端连接远程主机成功,computername = %1,ip = %2, port = %3.")).arg(remoteHostName).arg(remoteHostIp).arg(remoteHostPort), SystemLog::INFO);

	qDebug() << "network:客户端连接远程主机成功";
}
/**
*函数介绍:客户端socket断开连接成功
*输入参数:无
*返回值:  无
*/
void Network::clientSocketDisconnect(int descriptor)
{
	emit disConnectToHostSuccessSignal();
	//写入系统日志
	//Global::systemLog->append(tr("客户端断开与远程主机连接成功"), clientName + QString(tr("断开与远程主机连接成功,ip = %1, port = %2.")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::INFO);

	qDebug() << "network:客户端断开连接远程主机成功";
}

/**
*函数介绍:客户端socket出错
*输入参数:无
*返回值:  无
*/
void Network::clientSocketError(QAbstractSocket::SocketError socketError)
{
	remoteHostName = clientSocket->peerAddress().toString();
	remoteHostIp = clientSocket->peerName();
	remoteHostPort = clientSocket->peerPort();
	emit clientSocketErrorSignal(socketError);
	switch (socketError)
	{
	case QAbstractSocket::ConnectionRefusedError:
		//Global::systemLog->append(QString(tr("%1网络客户端出错：拒绝连接.")).arg(clientName), QString(tr("远程计算机IP:%1,port:%2拒绝连接,The connection was refused by the peer (or timed out).")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::ERROR);
		break;
	case QAbstractSocket::RemoteHostClosedError:
		//Global::systemLog->append(QString(tr("%1网络客户端出错：远程主机关闭了连接.")).arg(clientName), QString(tr("远程计算机IP:%1,port:%2关闭了SOCKET连接,客户端SOCKET也即将关闭,The remote host closed the connection. ")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::ERROR);
		break;
	case QAbstractSocket::HostNotFoundError:
		//Global::systemLog->append(QString(tr("%1网络客户端出错：找不到远程主机.")).arg(clientName), QString(tr("找不到远程计算机IP:%1,port:%2,The host address was not found. ")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::ERROR);
		break;
	case QAbstractSocket::SocketResourceError:
		//Global::systemLog->append(QString(tr("%1网络客户端出错：Socket资源不够.")).arg(clientName), QString(tr("Socket资源不够，远程计算机IP:%1,port:%2,The local system ran out of resources (e.g., too many sockets). ")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::ERROR);
		break;
	case QAbstractSocket::SocketTimeoutError:
		//Global::systemLog->append(QString(tr("%1网络客户端出错：操作超时.")).arg(clientName), QString(tr("客户端网络操作超时，远程计算机IP:%1,port:%2,The socket operation timed out. ")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::ERROR);
		break;
	case QAbstractSocket::DatagramTooLargeError:
		//Global::systemLog->append(QString(tr("%1网络客户端出错：数据包过大.")).arg(clientName), QString(tr("客户端网络数据包国大，远程计算机IP:%1,port:%2,The socket operation timed out. ")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::ERROR);
		break;
	case QAbstractSocket::NetworkError:
		//Global::systemLog->append(QString(tr("%1网络客户端出错：计算机网络出错.")).arg(clientName), QString(tr("计算机网络出错，可能网线断开了，远程计算机IP:%1,port:%2,The datagram was larger than the operating system's limit (which can be as low as 8192 bytes).")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::ERROR);
		break;
	default:
		int i = 0;
		//Global::systemLog->append(QString(tr("%1网络客户端出错：未知错误,SocketError:%2")).arg(clientName).arg(socketError), QString(tr("未知错误，远程计算机IP:%1,port:%2")).arg(remoteHostIp).arg(remoteHostPort), SystemLog::ERROR);

	}
	qDebug() << "network:客户端socket出错";
}
