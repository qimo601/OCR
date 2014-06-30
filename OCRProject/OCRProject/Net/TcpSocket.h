/**
*
* ��   Ŀ:   PET/CT��� ͨ��ģ��
* �ļ�����:  TcpSocket.h
* �ļ�·���� NetworkCommunication/TcpSocket.h
* ժ   Ҫ:   socketͨѶ�࣬��Ҫʵ�ַ��������ӣ�
*            ��ȡ�ͻ������ݣ��������ݵȹ���
* ��   �ߣ�  ���װ�
* ������ڣ� 2011��11��23��
* �޸���:    ���װ�
* �޸����ݣ� ɾ�����ຯ��getMessageList()��
* �޸����ڣ� 2012-09-06
* Copyright (c) 2011-2012, �п�Ժ����ҽ����ҽѧӰ���ҵ�����.All rights reserved.
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
    //Ĭ�ϲ���decriptor,tcpServer��������ʱ����Ҫ��ֵ��TcpSocket��socketDescriptorEternal��Ա
    TcpSocket(int descriptor = -1, QObject *parent = 0);
    ~TcpSocket();
    //��ȡ����������
    int getSocketDescriptorEternal()
    {
        return socketDescriptorEternal;
    }
    //��������������
    void setSocketDescriptorEternal(int descriptor)
    {
        socketDescriptorEternal = descriptor;
    }

public slots:

    //����ͨ�ŷ����
    void connectToRemoteHost(QString,qint32);
    //��ȡTcpSocket�е�����
    void readMessage();
	//��ȡ�׽�������������
	void readAllMessage();
	//��ȡ�׽�������������ָ������
	void readAllMessage(QByteArray& result, int& descrip);
    //�������ݸ�TcpSocket
    qint64 sendMessage(QByteArray&);
    //�����Ϻ󣬲ۺ�������
    void connectedSlot();
    //�Ͽ����Ӻ󣬲ۺ�������
    void disconnectedSlot();

	//**********����************//
    //socket����
    void TcpSocketError(QAbstractSocket::SocketError);
    //��ȡTcpSocketState
    void getTcpSocketState(QAbstractSocket::SocketState);
	//**********����************//

signals:
    //�ź�:socket�����ݳɹ�������������
    void haveReadDataSignal(QByteArray,int);
    //�ź�:socket�ѶϿ��źţ���δɾ��֮ǰ.��������
    void disconnectedBeforeDeleteSignal(int);
    //�ź�:socket�����ӣ���������
    void connectedSignal(int);
	
    //�ź�:��һ��socket�������źţ�רΪ����˷���
    void connectedForServerSignal(int);

	//**********����************//
    //�ź�:�����ź�
    void tcpSocketErrorSignal(QAbstractSocket::SocketError);
	//**********����************//
private:

    //socket���յ������ݴ�С,����������ֵ��2���ֽ�
    qint32 nextBlockSize;
    //��socket ��������������Ҫ��ʼ��.��socket�Ͽ���״̬�����ı�󣬸��������Բ���
    int socketDescriptorEternal;


};

#endif
