/**
*
* ��   Ŀ:  PET/CT��� ͨ��ģ��
* �ļ�����:  TcpSocket.cpp
* �ļ�·���� NetworkCommunication/TcpSocket.cpp
* ժ   Ҫ:  socketͨѶ�࣬��Ҫʵ�ַ��������ӣ�
*          ��ȡ�ͻ������ݣ��������ݵȹ���
* ��   �ߣ� ���װ�
* ������ڣ� 2011��11��23��
* Copyright (c) 2011, �п�Ժ����ҽ����ҽѧӰ���ҵ�����.All rights reserved.
* Version v1.0
*/

#include <QtNetwork>
#include "TcpSocket.h"
#include <QDebug>
#include <QHash>


TcpSocket::TcpSocket(int descriptor, QObject *parent)
    : socketDescriptorEternal(descriptor),QTcpSocket(parent)
{
    //�źŲ�:�����Ϻ�,�ͻ���
    connect(this, SIGNAL(connected()), this, SLOT(connectedSlot()));
    //�źŲ�:�Ͽ����Ӻ�Ӧɾ����ǰ����.�ͻ���/�����
    connect(this, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
	//�źŲ�:������.�ͻ���/�����--������ģʽ����ͣ
    //connect(this, SIGNAL(readyRead()), this, SLOT(readAllMessage()));
    nextBlockSize = 0;
    qDebug()  << "TcpSocket ThreadId:" << QThread::currentThreadId();
	
    //�źŲ�:����TcpSocket״̬.�ͻ���/�����.�Ѿ���Network��Tcpserver�и����ˡ�
    //connect(this,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(getTcpSocketState(QAbstractSocket::SocketState)));
    
    
}
TcpSocket::~TcpSocket()
{

}

/**
 *�������ܣ����ӷ����
 *���������(ip�������IP��port���˿�)
 *����ֵ��
 */
void TcpSocket::connectToRemoteHost(QString ip,qint32 port)
{
    //���ӵ�����ˣ����ӳɹ��� emits connected()�ź�
    connectToHost(ip,port);

}

/**
 *�������ܣ���������
 *����������ֽ�����temp
 *����ֵ��Returns the number of bytes that were actually written, or -1 if an error occurred.
 */
qint64 TcpSocket::sendMessage(QByteArray& temp)
{
    //�����ݴ�Ҫ���͵�����
    QByteArray block = temp;
    //���׽��ֻ�����д�����ݣ�������ʵ�ʷ����ֽ�����-1�����д���
    return this->write(block);
}

/**
* �������ܣ� ��ȡ�׽������ݣ�����ˣ��ͻ��˶����ã�
* ��������� ��
* �ź�:���ͽ��յ������ݣ��Լ����׽��ֵ�������
* ����ֵ  �� ��
*/
void TcpSocket::readMessage()
{
    qint32 tcpSocketSize = 0;
    QDataStream in(this);
	//��������С=0��û������.��֤���ݲ���ʧ
    //qDebug() << "TcpSocket Internal Read Buffer��������С��" << readBufferSize();
	//����For open sequential devices, size() = bytesAvailable()
    qDebug()<<"Socket�ѻ����С" << bytesAvailable();
    //�����������汾������Ҫ�ͷ���������ͬ
	in.setVersion(QDataStream::Qt_5_3);
	in.setByteOrder(QDataStream::LittleEndian);
    in.device()->seek(0);
	
    //����Ǹտ�ʼ��������
    if (nextBlockSize == 0)
    {
        //�жϽ��յ������Ƿ������ֽڣ�Ҳ�����ļ��Ĵ�С��Ϣ
        //������򱣴浽nextBlockSize�����У�û���򷵻أ�������������
        if (bytesAvailable() < sizeof(qint32))
            return;
        in >> nextBlockSize;//�õ�����
        qDebug()<<"���յ����ݰ�nextBlockSize��"<<nextBlockSize;
    }

    tcpSocketSize = this->size();
	qDebug()<<"������ݰ����Ⱥ��ѻ����С��" << bytesAvailable();
    //�������û�����꣬��������
    if (bytesAvailable() < nextBlockSize)
        return;
    in.device()->seek(0);
    //��������
    QByteArray resultArray;
    //��ȡȫ������,���˳���
    resultArray = this->read(nextBlockSize);
    tcpSocketSize = this->size();
    qDebug()<<"���һ�����ݰ����ѻ����С��"<<tcpSocketSize;
    //���ͽ��յ������ݣ��Լ����׽��ֵ�������
    emit haveReadDataSignal(resultArray,this->socketDescriptor());
    //�������ݺ��������ݴ�С��Ϊ0
    nextBlockSize = 0;
}

/**
* �������ܣ� ��ȡ�׽�����������
* ��������� ��
* �ź�:���ͽ��յ������ݣ��Լ����׽��ֵ�������
* ����ֵ  �� ��
*/
void TcpSocket::readAllMessage()
{
	qint32 tcpSocketSize = 0;
	//QDataStream in(this);

	//qDebug() << "Socket�ѻ����С" << bytesAvailable();
	//�����������汾������Ҫ�ͷ���������ͬ
	//in.setVersion(QDataStream::Qt_5_3);
	//in.setByteOrder(QDataStream::LittleEndian);
	//in.device()->seek(0);

	//in.device()->seek(0);
	//��������
	QByteArray resultArray;

	//qDebug() << "��֮ǰ���ж������ݣ�" << bytesAvailable();
	//��ȡȫ������,���˳���
	resultArray = this->readAll();
	tcpSocketSize = this->size();
	//qDebug() << "����󣬻��ж������ݣ�" << bytesAvailable();
	//���ͽ��յ������ݣ��Լ����׽��ֵ�������
	emit haveReadDataSignal(resultArray, this->socketDescriptor());

}
/**
* �������ܣ� ��ȡ�׽�����������
* ��������� ���ݡ�socket������
* ����ֵ  �� ��
*/
void TcpSocket::readAllMessage(QByteArray& result,int& descrip)
{
	qint32 tcpSocketSize = 0;
	//QDataStream in(this);

	//qDebug() << "Socket�ѻ����С" << bytesAvailable();
	//�����������汾������Ҫ�ͷ���������ͬ
	//in.setVersion(QDataStream::Qt_5_3);
	//in.setByteOrder(QDataStream::LittleEndian);
	//in.device()->seek(0);

	//in.device()->seek(0);
	//��������
	//QByteArray resultArray;

	//qDebug() << "��֮ǰ���ж������ݣ�" << bytesAvailable();
	//��ȡȫ������,���˳���
	result = this->readAll();
	descrip = this->socketDescriptor();
	tcpSocketSize = this->size();
	//qDebug() << "����󣬻��ж������ݣ�" << bytesAvailable();
	//���ͽ��յ������ݣ��Լ����׽��ֵ�������
	//emit haveReadDataSignal(result, descrip);

}
/**
* ��������
* ��������:socket����
* �������:��
* ����ֵ:��
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
 *��������:��ȡTcpSocketState
 *�������:��
 *����ֵ:  ��
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
 *��������:socket�����Ϻ�ۺ�����
 *�������:
 *����ֵ:��
 */
void TcpSocket::connectedSlot()
{
    //�����������źţ���socket������
    emit connectedSignal(this->socketDescriptor());
    qDebug()<< "TcpSocket����" << this->socketDescriptor() << " �����������ź�";
}

/**
 *��������:�ر�һ��socket���Ӻ�ۺ�����
 *�������:
 *����ֵ:��
 */
void TcpSocket::disconnectedSlot()
{
    //ɾ������֮ǰ���ѹر��ź�
    emit disconnectedBeforeDeleteSignal(socketDescriptorEternal);
    qDebug()<<"TcpSocket����" << socketDescriptorEternal << " �����ѹر��ź�";
    //ɾ���˶���
    //deleteLater();
}
