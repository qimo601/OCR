/**
*
* ��   Ŀ:  PET/CT��� ͨ��ģ��
* �ļ�����:  TcpServer.cpp
* �ļ�·���� NetworkCommunication/TcpServer.cpp
* ժ   Ҫ:  ͨ�ŷ��������
* ��   �ߣ� ���װ�
* ������ڣ� 2011��11��23��
* �޸��ˣ����װ�
* �޸����ݣ����ϵͳ��־���޸ĺ�������ɾ�������źźͺ������޸Ŀͻ��˹ر����ӷ���˱���bug
* �޸����ڣ�2012��09��05��
* Copyright (c) 2011-2012, �п�Ժ����ҽ����ҽѧӰ���ҵ�����.All rights reserved.
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
    //��ȡָ����������socketָ��
    TcpSocket* getServerSocket(int);
	//�ظ��ͻ�����Ϣ
    void replyClientMessage(QByteArray,int);
    //����һ��serverSocket
    void addServerSocket(int);
    //�Ƴ�һ��serverSocket
    void removeServerSocket(int);
	//����server��socket״̬
	void getServerSocketState(QAbstractSocket::SocketState);
	//�����socket����
	void serverSocketError(QAbstractSocket::SocketError);
private slots:
    //��ÿͻ�����Ϣ
    void getClientMessage(QByteArray,int);
    //��ʼ������ͨѶ,Ĭ�϶˿� = 6666
    void start(int = 6666);
    //ֹͣ������ͨѶ
    void stop();
    //��ȡ���������й�������
    void getAllConnection();
signals:
    
    //�ź�: ��������˳ɹ�
    void startSuccessSignal();
    //�ź�: ���������ʧ��
    void startFailSignal();
    //�ź�: ֹͣ����˳ɹ�
    void stopSuccessSignal();
    //�ź�: �������һ��serverSocket�ź�
    void addServerSocketSignal(int);
    //�źţ��Ƴ���һ��serversocket
    void removeServerSocketSignal(int);
	//�ź�: �����socket�����ź�
	void serverSocketErrorSignal(QAbstractSocket::SocketError);
	//**************������Ӱ���ͨ�������໮���ź�*********************//
	//�źţ�����˽��յ�scan���������
    void haveScanSignal(QByteArray,int);
	
	//**************������Ӱ���ͨ�������໮���ź�*********************//
private:
    
    //���µ���������
    void incomingConnection(int socketId);



};

#endif//TCPSERVER_H
