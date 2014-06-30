/**
*
* ��    Ŀ:  PET/CT��� ͨ��ģ��
* �ļ�����:  TcpServer.cpp
* �ļ�·���� NetworkCommunication/TcpServer.cpp
* ժ    Ҫ:  ͨ�ŷ��������
* ��    �ߣ� ���װ�
* ������ڣ� 2011��11��23��
* �޸��ˣ�   ���װ�
* �޸����ݣ� �����־���޸Ĳ��ֳ���
* �޸����ڣ� 2012��09��05��
* Copyright (c) 2011-2012, �п�Ժ����ҽ����ҽѧӰ���ҵ�����.All rights reserved.
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
 *��������:����ͨ�ŷ����
 *�������:��
 *����ֵ:��
 */
void TcpServer::start(int port)
{
    if(listen(QHostAddress::Any,port))
    {
        qDebug()<< "TcpServer start ThreadId:" << QThread::currentThreadId();
		//д��ϵͳ��־
		//Global::systemLog->append(tr("����ͨ�ŷ�������������ɹ�."), QString(tr("�����˿�port: %1.")).arg(port), SystemLog::INFO);
        qDebug() << "��������������ɹ�";
        emit startSuccessSignal();
        //������������ӣ������������ǰ����
        //connect(this, SIGNAL(newConnection()), this, SLOT(getAllConnection()));
		
    }
    else
    {
		//д��ϵͳ��־
		//Global::systemLog->append(tr("����ͨ�ŷ������������ʧ��."), QString(tr("�����˿�port: %1.")).arg(port), SystemLog::INFO);
        //��������������port�˿ڣ������������������Ϣ�����ر�
        qDebug() << "��������˼���ʧ��";
        //ֹͣ����
        stop();
        emit startFailSignal();
    }
}
/**
 *��������:ֹͣͨ�ŷ����
 *�������:��
 *����ֵ:��
 */
void TcpServer::stop()
{

	QString serverAddress = this->serverAddress().toString();
	int serverPort = this->serverPort();
    close();
	//д��ϵͳ��־
	//Global::systemLog->append(tr("����ͨ�ŷ����ֹͣ����."), QString(tr("����IP%1:,�����˿�port:%2.")).arg(serverAddress).arg(serverPort), SystemLog::INFO);
    emit stopSuccessSignal();
}
/**
 *��������:���������ӣ��½�һ��socket
 *�������:int socketId,�½�socket��SocketDescriptor
 *����ֵ:��
 */
void TcpServer::incomingConnection(int socketId)
{
    TcpSocket *socket = new TcpSocket(socketId,this);
	//����socket������
    socket->setSocketDescriptor(socketId);
	//д��ϵͳ��־
	//Global::systemLog->append(tr("����ͨ�ŷ�������µ���������"), QString(tr("����˽����µ���������,socket������ = %1.")).arg(socketId), SystemLog::INFO);

    qDebug()<<"��������µ�����,socketDescriptor:"<<socket->socketDescriptor();
    //�½���һ��socket����
    addServerSocket(socketId);


    //��ÿͻ�������
    connect(socket, SIGNAL(haveReadDataSignal(QByteArray,int)), this, SLOT(getClientMessage(QByteArray,int)));
	//�źŲ�:���ٷ����Socket״̬
    connect(socket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(getServerSocketState(QAbstractSocket::SocketState)));
    //�źŲ�:�����socket���ִ���
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(serverSocketError(QAbstractSocket::SocketError)));

    //��ͻ��˶Ͽ�ĳsocket���ӣ������״̬�����ı�
    connect(socket, SIGNAL(disconnectedBeforeDeleteSignal(int)), this, SLOT(removeServerSocket(int)));
    //��ͻ��˶Ͽ����ӣ������������ǰ����
    //connect(socket, SIGNAL(disconnectedBeforeDeleteSignal(int)), this, SLOT(getAllConnection()));	
	//��ͻ��������Ϻ������������ǰ����
    //connect(socket, SIGNAL(connectedForServerSignal(int)), this, SLOT(getAllConnection()));
    //��ͻ��������Ϻ������������ǰ����
    //connect(socket, SIGNAL(connectedForServerSignal(int)), this, SLOT(addServerSocket(int)));

}
/**
 *��������:��ÿͻ�������
 *�������:���յ����ֽ����� result,������׽��������� descriptor
 *����ֵ:��
 */
void TcpServer::getClientMessage(QByteArray result,int descriptor)
{
    //���յ����ֽ�����
    QByteArray resultArray = result ;
    QDataStream in(resultArray);
    in.setVersion(QDataStream::Qt_4_6);
    //�����ֽ���Little endian���������ֽڴ洢����ʼ��ַ  Big endian���������ֽڴ洢����ʼ��ַ
    in.setByteOrder(QDataStream::LittleEndian);
    //����
    qint32 length;
    //Ŀ���豸ID
    qint32 destEquipId;
    //Դ�豸Id
    qint32 sourceEquipID;
    //����
    qint32 cmd ;
    length = resultArray.size();
    in >> destEquipId;
    in >> sourceEquipID;
    in >> cmd;
	QString destEquipName = Global::getComputerDeviceName(destEquipId);
	QString sourceEquipName = Global::getComputerDeviceName(sourceEquipID);
    //qDebug() << "tcpServer �õ��ͻ������ݴ�Сlength:" <<length << "cmd" << cmd;
    //���������յ����ݣ������ź�
    //ɨ��������Ļظ�
    if( cmd >= 0x0000 && cmd <= 0x0050)
    {
        emit haveScanSignal(resultArray,descriptor);
		qDebug() << QString("����˵õ�ɨ��������,����:%1,Ŀ�����:%2,Դ�豸:%3,�����:%4").arg(cmd).arg(destEquipName).arg(sourceEquipName).arg(length);
		//д��ϵͳ��־
		//Global::systemLog->append(QString(tr("����˵õ�ɨ��������,����:%1")).arg(cmd), QString("����˵õ�ɨ�����������:%1,Ŀ�����:%2,Դ�豸:%3,�����:%4").arg(cmd).arg(destEquipName).arg(sourceEquipName).arg(length), SystemLog::LOG);

	}
    //��������Ļظ�
    else if( cmd >= 0x0051 && cmd <= 0x00A0)
    {
		qDebug() << QString("����˵õ���������,����:%1,Ŀ�����:%2,Դ�豸:%3,�����:%4").arg(cmd).arg(destEquipName).arg(sourceEquipName).arg(length);
		//д��ϵͳ��־
		//Global::systemLog->append(QString(tr("����˵õ���������,����:%1")).arg(cmd), QString("����˵õ�ɨ�����������:%1,Ŀ�����:%2,Դ�豸:%3,�����:%4").arg(cmd).arg(destEquipName).arg(sourceEquipName).arg(length), SystemLog::LOG);

    }
    //����������Ļظ�
    else
    {
		qDebug() << QString("����˵õ�����������,����:%1,Ŀ�����:%2,Դ�豸:%3,�����:%4").arg(cmd).arg(destEquipName).arg(sourceEquipName).arg(length);
		//д��ϵͳ��־
		//Global::systemLog->append(QString(tr("����˵õ�����������,����:%1")).arg(cmd), QString("����˵õ�ɨ�����������:%1,Ŀ�����:%2,Դ�豸:%3,�����:%4").arg(cmd).arg(destEquipName).arg(sourceEquipName).arg(length), SystemLog::LOG);

    }

}
/**
 *��������:�ظ��ͻ�������
 *�������:�ظ�����QByteArray result,�׽��������� descriptor
 *����ֵ:��
 */
void TcpServer::replyClientMessage(QByteArray result,int descriptor)
{
    TcpSocket *serverSocket;
    if(descriptor!=-1)
    {
        //��÷�����׽���
        serverSocket = getServerSocket(descriptor);
        //��������
        if(serverSocket)
			serverSocket->sendMessage(result);
		qDebug()<<"���ڻظ����ݡ�����������";
    }
}

/**
 *��������:��ȡ��������ָ����������socketָ��
 *�������:descriptor��socket������.
 *����ֵ:����ҵ�ָ��socket���򷵻ظ�ָ�룻���򷵻�0.
 */
TcpSocket* TcpServer::getServerSocket(int descriptor)
{
    //��ȡtcpServer����serverSocket����
    QList<TcpSocket*> serverSocketList = this->findChildren<TcpSocket*>();
    for (int i=0;i<serverSocketList.count();i++)
    {
        TcpSocket *item = serverSocketList.at(i);
        //����ҵ�ָ��socket���򷵻ظ�ָ��
        if(item->socketDescriptor()== descriptor)
        {
            //qDebug() << "��Ѱ�ҵ�ͨ�ŷ������socketָ�� socketDescriptor:" << item->socketDescriptor();
            return item;
        }


    }
    qDebug() << "δѰ�ҵ�ͨ�ŷ������socketָ��";
    //δ�ҵ�ָ��socket������0
    return 0;
}

/**
 *��������:��ȡ���������й�������
 *�������:��
 *����ֵ:��
 */
void TcpServer::getAllConnection()
{
    //��ȡtcpServer����serverSocket����
    QList<TcpSocket*> serverSocketList = this->findChildren<TcpSocket*>();

    int count = 0;
    for (int i=0;i<serverSocketList.count();i++)
    {
        QTcpSocket *item = serverSocketList.at(i);
        if(item->socketDescriptor()!= -1)
        {
            qDebug() << "���������ڹ����socket���� socketDescriptor:" << item->socketDescriptor();
            count++;
        }
    }
    qDebug() << "����" <<count <<"���ͻ������ӵ���������";
}
/**
 *��������:tcpServer ���socket
 *�������:descriptor,�ı�״̬��socket������
 *����ֵ:��
 */
void TcpServer::addServerSocket(int descriptor)
{
    //tcpServer�������һ��serverSocket�ź�
    emit addServerSocketSignal(descriptor);
    qDebug()<<"tcpServer�������һ��serverSocket�ź�";
    getAllConnection();
}

/**
 *��������:tcpServer �Ƴ�socket
 *�������:descriptor,�ı�״̬��socket������
 *����ֵ:��
 */
void TcpServer::removeServerSocket(int descriptor)
{
    //tcpServer�����Ƴ���һ��serverSocket�ź�
    emit removeServerSocketSignal(descriptor);
    qDebug()<<"tcpServer�����Ƴ���һ��serverSocket�ź�";
    getAllConnection();
}
/**
 *��������:����server��socket״̬
 *�������:�����socket״̬
 *����ֵ:��
 */
void TcpServer::getServerSocketState(QAbstractSocket::SocketState socketState)
{
	QTcpSocket *serverSocket = qobject_cast<QTcpSocket *>(sender());
	QString clientIp = serverSocket->peerAddress().toString();
	int clientPort = serverSocket->peerPort();
	QString serverIp = this->serverAddress().toString();
	int serverPort = this->serverPort();
	//���Դ���  �Ƿ�������һ����Ip��port???
	QString serverIp1 = serverSocket->localAddress().toString();
	int serverPort1 = serverSocket->localPort();
	//���Դ���
    switch (socketState)
    {
    case QAbstractSocket::UnconnectedState: 
		qDebug() << "����ˣ�UnconnectedState:The socket is not connected.";
		//Global::systemLog->append(QString(tr("��������״̬���Ͽ�����״̬,δ���Ͽͻ���Socket.�ͻ���IP:%1")).arg(clientIp), QString(tr("��ͻ��˼�����Ͽ����ӣ��ͻ���IP:%1,port:%2,UnconnectedState:The socket is not connected.")).arg(clientIp).arg(clientPort), SystemLog::INFO);
		break;
    case QAbstractSocket::HostLookupState: 
		qDebug()  << "����ˣ�HostLookupState:The socket is performing a host name lookup.";
		//Global::systemLog->append(QString(tr("��������״̬�����ڲ�ѯ�������......�ͻ���IP:%1")).arg(clientIp), QString(tr("���ڲ�ѯ�ͻ��˼����IP:%1,port:%2,HostLookupState:The socket is performing a host name lookup.")).arg(clientIp).arg(clientPort), SystemLog::INFO);
		break;
	case QAbstractSocket::ConnectingState: 
		qDebug()  << "����ˣ�ConnectingState:The socket has started establishing a connection.";
		//Global::systemLog->append(QString(tr("��������״̬�����ڴ�����������......�ͻ���IP:%1")).arg(clientIp), QString(tr("���ڴ����������ӣ��ͻ��˼����IP:%1,port:%2,ConnectingState:The socket has started establishing a connection.")).arg(clientIp).arg(clientPort), SystemLog::INFO);
		break;
	case QAbstractSocket::ConnectedState: 
		qDebug()  << "����ˣ�ConnectedState:A connection is established."; 
		//Global::systemLog->append(QString(tr("��������״̬��TCP���Ӵ����ɹ�.�ͻ���IP:%1")).arg(clientIp), QString(tr("�����Ѿ����ӳɹ����ͻ��˼����IP:%1,port:%2,ConnectedState:A connection is established.")).arg(clientIp).arg(clientPort), SystemLog::INFO);
		break;
    case QAbstractSocket::BoundState: 
		qDebug()  << "����ˣ�BoundState:The socket is bound to an address and port (for servers)."; 
		//Global::systemLog->append(QString(tr("��������״̬��������Ѱ�TCP Socket.�����IP:%1,port:%2.")).arg(serverIp).arg(serverPort), QString(tr("�����Ѿ����ӳɹ������ط����IP:%1,port:%2,�ͻ��˼����IP:%3,port:%4,BoundState:The socket is bound to an address and port (for servers).")).arg(serverIp).arg(serverPort).arg(clientIp).arg(clientPort), SystemLog::INFO);
		break;
    case QAbstractSocket::ClosingState: 
		qDebug()  << "����ˣ�ClosingState:The socket is about to close (data may still be waiting to be written)."; 
		//Global::systemLog->append(QString(tr("��������״̬�������ر�һ��TCP Socket.�ͻ���IP:%1")).arg(clientIp), QString(tr("���缴���ر�,Զ�̼����IP:%1,port:%2,ClosingState:The socket is about to close (data may still be waiting to be written).")).arg(clientIp).arg(clientPort), SystemLog::INFO);
		break;
	case QAbstractSocket::ListeningState: 
		qDebug()  << "����ˣ�ListeningState:For internal use only."; 
		//Global::systemLog->append(QString(tr("��������״̬��Socket����״̬.�ͻ���IP:%1")).arg(clientIp), QString(tr("��������״̬,Զ�̼����IP:%1,port:%2")).arg(clientIp).arg(clientPort), SystemLog::INFO);
		break;
    default: 
		qDebug()<<"����ˣ���������״̬";
		//Global::systemLog->append(QString(tr("��������״̬������״̬.�ͻ���IP:%1")).arg(clientIp), QString(tr("��������״̬,Զ�̼����IP:%1,port:%2")).arg(clientIp).arg(clientPort), SystemLog::INFO);
    }

	serverSocket = 0;
}


/**
 *��������:�����socket����
 *�������:��
 *����ֵ:  ��
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
		//Global::systemLog->append(QString(tr("�������˳����ܾ�����.")).arg(clientIp), QString(tr("�ͻ��˼����IP:%1,port:%2�ܾ�����,The connection was refused by the peer (or timed out).")).arg(clientIp).arg(clientPort), SystemLog::ERROR);
		break;
    case QAbstractSocket::RemoteHostClosedError:   
		//Global::systemLog->append(QString(tr("�������˳���Զ�������ر�������.")).arg(clientIp), QString(tr("�ͻ��˼����IP:%1,port:%2�ر���SOCKET����,�����SOCKETҲ�����ر�,The remote host closed the connection. ")).arg(clientIp).arg(clientPort), SystemLog::ERROR);
		break;
    case QAbstractSocket::HostNotFoundError:   
		//Global::systemLog->append(QString(tr("�������˳����Ҳ���Զ������.")).arg(clientIp), QString(tr("�Ҳ����ͻ��˼����IP:%1,port:%2,The host address was not found. ")).arg(clientIp).arg(clientPort), SystemLog::ERROR);
		break;
	case QAbstractSocket::SocketResourceError:  
		//Global::systemLog->append(QString(tr("�������˳���Socket��Դ����.")).arg(clientIp), QString(tr("����Socket��Դ�������ͻ��˼����IP:%1,port:%2,The local system ran out of resources (e.g., too many sockets). ")).arg(clientIp).arg(clientPort), SystemLog::ERROR);
		break;
    case QAbstractSocket::SocketTimeoutError:  
		//Global::systemLog->append(QString(tr("�������˳���������ʱ.")).arg(clientIp), QString(tr("��������������ʱ���ͻ��˼����IP:%1,port:%2,The socket operation timed out. ")).arg(clientIp).arg(clientPort), SystemLog::ERROR);
		break;
	case QAbstractSocket::DatagramTooLargeError:  
		//Global::systemLog->append(QString(tr("�������˳������ݰ�����.")).arg(clientIp), QString(tr("������������ݰ����󣬿ͻ��˼����IP:%1,port:%2,The socket operation timed out. ")).arg(clientIp).arg(clientPort), SystemLog::ERROR);
		break;
	case QAbstractSocket::NetworkError:  
		//Global::systemLog->append(QString(tr("�������˳���������������.")).arg(clientIp), QString(tr("��������������߶Ͽ��ˣ��ͻ��˼����IP:%1,port:%2,The datagram was larger than the operating system's limit (which can be as low as 8192 bytes).")).arg(clientIp).arg(clientPort), SystemLog::ERROR);
		break;
    default:
		int i = 0;
		//Global::systemLog->append(QString(tr("�������˳���δ֪����,SocketError:%2")).arg(clientIp).arg(socketError), QString(tr("δ֪���󣬿ͻ��˼����IP:%1,port:%2")).arg(clientIp).arg(clientPort), SystemLog::ERROR);

    }
    qDebug() << "�����socket����";
}
