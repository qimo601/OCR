/**
*
* 项   目:  PET/CT软件 通信模块
* 文件名称:  TcpSocket.cpp
* 文件路径： NetworkCommunication/TcpSocket.cpp
* 摘   要:  socket通讯类，主要实现发起新连接，
*          读取客户端数据，发送数据等功能
* 作   者： 刘兆邦
* 完成日期： 2011年11月23日
* Copyright (c) 2011, 中科院苏州医工所医学影像室电子组.All rights reserved.
* Version v1.0
*/

#include <QtNetwork>
#include "TcpSocket.h"
#include <QDebug>
#include <QHash>


TcpSocket::TcpSocket(int descriptor, QObject *parent)
    : socketDescriptorEternal(descriptor),QTcpSocket(parent)
{
    //信号槽:连接上后,客户端
    connect(this, SIGNAL(connected()), this, SLOT(connectedSlot()));
    //信号槽:断开连接后，应删除当前对象.客户端/服务端
    connect(this, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
	//信号槽:有数据.客户端/服务端--非阻塞模式，暂停
    //connect(this, SIGNAL(readyRead()), this, SLOT(readAllMessage()));
    nextBlockSize = 0;
    qDebug()  << "TcpSocket ThreadId:" << QThread::currentThreadId();
	
    //信号槽:跟踪TcpSocket状态.客户端/服务端.已经在Network和Tcpserver中跟踪了。
    //connect(this,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(getTcpSocketState(QAbstractSocket::SocketState)));
    
    
}
TcpSocket::~TcpSocket()
{

}

/**
 *函数介绍：连接服务端
 *输入参数：(ip：计算机IP，port：端口)
 *返回值：
 */
void TcpSocket::connectToRemoteHost(QString ip,qint32 port)
{
    //连接到服务端，连接成功会 emits connected()信号
    connectToHost(ip,port);

}

/**
 *函数介绍：发送数据
 *输入参数：字节数组temp
 *返回值：Returns the number of bytes that were actually written, or -1 if an error occurred.
 */
qint64 TcpSocket::sendMessage(QByteArray& temp)
{
    //用于暂存要发送的数据
    QByteArray block = temp;
    //往套接字缓存中写入数据，并返回实际发送字节数，-1代表有错误
    return this->write(block);
}

/**
* 函数介绍： 读取套接字数据（服务端，客户端都可用）
* 输入参数： 无
* 信号:发送接收到的数据，以及此套接字的描述符
* 返回值  ： 无
*/
void TcpSocket::readMessage()
{
    qint32 tcpSocketSize = 0;
    QDataStream in(this);
	//缓冲区大小=0，没有限制.保证数据不丢失
    //qDebug() << "TcpSocket Internal Read Buffer缓冲区大小：" << readBufferSize();
	//对于For open sequential devices, size() = bytesAvailable()
    qDebug()<<"Socket已缓冲大小" << bytesAvailable();
    //设置数据流版本，这里要和服务器端相同
	in.setVersion(QDataStream::Qt_5_3);
	in.setByteOrder(QDataStream::LittleEndian);
    in.device()->seek(0);
	
    //如果是刚开始接收数据
    if (nextBlockSize == 0)
    {
        //判断接收的数据是否有两字节，也就是文件的大小信息
        //如果有则保存到nextBlockSize变量中，没有则返回，继续接收数据
        if (bytesAvailable() < sizeof(qint32))
            return;
        in >> nextBlockSize;//得到长度
        qDebug()<<"接收到数据包nextBlockSize："<<nextBlockSize;
    }

    tcpSocketSize = this->size();
	qDebug()<<"输出数据包长度后，已缓冲大小：" << bytesAvailable();
    //如果数据没接受完，继续接收
    if (bytesAvailable() < nextBlockSize)
        return;
    in.device()->seek(0);
    //接收数据
    QByteArray resultArray;
    //获取全部数据,除了长度
    resultArray = this->read(nextBlockSize);
    tcpSocketSize = this->size();
    qDebug()<<"输出一个数据包后，已缓冲大小："<<tcpSocketSize;
    //发送接收到的数据，以及此套接字的描述符
    emit haveReadDataSignal(resultArray,this->socketDescriptor());
    //读完数据后，数据内容大小置为0
    nextBlockSize = 0;
}

/**
* 函数介绍： 读取套接字所有数据
* 输入参数： 无
* 信号:发送接收到的数据，以及此套接字的描述符
* 返回值  ： 无
*/
void TcpSocket::readAllMessage()
{
	qint32 tcpSocketSize = 0;
	//QDataStream in(this);

	//qDebug() << "Socket已缓冲大小" << bytesAvailable();
	//设置数据流版本，这里要和服务器端相同
	//in.setVersion(QDataStream::Qt_5_3);
	//in.setByteOrder(QDataStream::LittleEndian);
	//in.device()->seek(0);

	//in.device()->seek(0);
	//接收数据
	QByteArray resultArray;

	//qDebug() << "读之前，有多少数据：" << bytesAvailable();
	//获取全部数据,除了长度
	resultArray = this->readAll();
	tcpSocketSize = this->size();
	//qDebug() << "读完后，还有多少数据：" << bytesAvailable();
	//发送接收到的数据，以及此套接字的描述符
	emit haveReadDataSignal(resultArray, this->socketDescriptor());

}
/**
* 函数介绍： 读取套接字所有数据
* 输入参数： 数据、socket描述符
* 返回值  ： 无
*/
void TcpSocket::readAllMessage(QByteArray& result,int& descrip)
{
	qint32 tcpSocketSize = 0;
	//QDataStream in(this);

	//qDebug() << "Socket已缓冲大小" << bytesAvailable();
	//设置数据流版本，这里要和服务器端相同
	//in.setVersion(QDataStream::Qt_5_3);
	//in.setByteOrder(QDataStream::LittleEndian);
	//in.device()->seek(0);

	//in.device()->seek(0);
	//接收数据
	//QByteArray resultArray;

	//qDebug() << "读之前，有多少数据：" << bytesAvailable();
	//获取全部数据,除了长度
	result = this->readAll();
	descrip = this->socketDescriptor();
	tcpSocketSize = this->size();
	//qDebug() << "读完后，还有多少数据：" << bytesAvailable();
	//发送接收到的数据，以及此套接字的描述符
	//emit haveReadDataSignal(result, descrip);

}
/**
* 废弃函数
* 函数介绍:socket出错
* 输入参数:无
* 返回值:无
*/
void TcpSocket::TcpSocketError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::ConnectionRefusedError:  break;
    case QAbstractSocket::RemoteHostClosedError:  break;
    case QAbstractSocket::HostNotFoundError:  break;
    case QAbstractSocket::SocketTimeoutError: break;

    default: break;

    }
    qDebug()<< "SocketError: " << socketError;
    emit tcpSocketErrorSignal(socketError);
}

/**
 *函数介绍:获取TcpSocketState
 *输入参数:无
 *返回值:  无
 */
void TcpSocket::getTcpSocketState(QAbstractSocket::SocketState socketState)
{
    //enum QAbstractSocket::SocketState socketState = this->state();
    switch (socketState)
    {
    case QAbstractSocket::UnconnectedState: qDebug() << "UnconnectedState:The socket is not connected."; break;
    case QAbstractSocket::HostLookupState: qDebug()  << "HostLookupState:The socket is performing a host name lookup."; break;
    case QAbstractSocket::ConnectingState: qDebug()  << "ConnectingState:The socket has started establishing a connection."; break;
    case QAbstractSocket::ConnectedState:
        qDebug()  << "ConnectedState:A connection is established.";
        emit connectedForServerSignal(this->socketDescriptor());
        break;
    case QAbstractSocket::BoundState: qDebug()  << "BoundState:The socket is bound to an address and port (for servers)."; break;
    case QAbstractSocket::ClosingState: qDebug()  << "ClosingState:The socket is about to close (data may still be waiting to be written)."; break;
    default: qDebug()<<"ListeningState:For internal use only.";break;

    }
}

//void QAbstractSocket::connected () [signal]
//This signal is emitted after connectToHost() has been called and a connection has been successfully established.
//Note: On some operating systems the connected() signal may be directly emitted from the connectToHost() call for connections to the localhost.

/**
 *函数介绍:socket连接上后槽函数，
 *输入参数:
 *返回值:无
 */
void TcpSocket::connectedSlot()
{
    //发出已连接信号，有socket描述符
    emit connectedSignal(this->socketDescriptor());
    qDebug()<< "TcpSocket对象" << this->socketDescriptor() << " 发出已连接信号";
}

/**
 *函数介绍:关闭一个socket连接后槽函数，
 *输入参数:
 *返回值:无
 */
void TcpSocket::disconnectedSlot()
{
    //删除对象之前，已关闭信号
    emit disconnectedBeforeDeleteSignal(socketDescriptorEternal);
    qDebug()<<"TcpSocket对象" << socketDescriptorEternal << " 发出已关闭信号";
    //删除此对象
    //deleteLater();
}
