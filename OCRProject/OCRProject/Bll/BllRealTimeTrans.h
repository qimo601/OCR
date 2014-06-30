#ifndef BLLREALTIMETRANS_H
#define BLLREALTIMETRANS_H

#include <QObject>
#include "Include/Global.h"
#include "Include/HorseDataStruct.h"
class BllRealTimeTrans : public QObject
{
	Q_OBJECT

public:
	BllRealTimeTrans(QObject *parent = 0 );
	~BllRealTimeTrans();
public slots:

	/**
	* @brief 连接服务器
	* @param ip,port
	*/
	void connectToHost(QString serverIp, qint32 serverPort);
	/**
	* @brief 断开服务器
	*/
	void disconnectToHost();
	/**
	* @brief 识别端登录请求指令
	*/
	void clientLogin();

	/**
	* @brief 识别端处理服务端返回的数据
	*/
	void handleLogin(QByteArray result, int descriptor);
	/**
	* @brief 识别端请求马信息表指令
	*/
	void requestHorse();
	/**
	* @brief 识别端处理服务端-请求马信息表指令
	*/
	void handleRequestHorse(QByteArray result, int descriptor);
	/**
	* @brief 识别端根据RaceNO(场次号)请求RaceID指令
	* @param qint32 raceNo 场次号
	*/
	void requestRaceID(qint32 raceNO);
	/**
	* @brief 识别端处理服务端-请求RaceID指令
	*/
	void handleRequestRaceID(QByteArray result, int descriptor);
	/**
	* @brief 识别端提交比赛时长指令
	* @param qint32 raceTime 比赛时长
	*/
	void submitRaceTime(qint32 raceTime);
	/**
	* @brief 识别端处理服务端-提交比赛时长指令
	*/
	void handleSubmitRaceTime(QByteArray result, int descriptor);

	/**
	* @brief 识别端发送提交实时数据指令
	*/
	void submitRealData(DataOutput outputStruct);
	/**
	* @brief 提交win实时数据
	*/
	void submitWINOrPLA(DataOutput& ouputStruct,QString type ="WIN");
	/**
	* @brief 提交实时数据-QIN或QPL
	* @param ouputStruct：算法传递来的数据，type:传送类型默认QIN
	*/
	void submitQINOrQPL(DataOutput& ouputStruct, QString type = "QIN");
	/**
	* @brief 识别端处理服务端-提交实时数据指令
	*/
	void handleSubmitRealData(QByteArray result, int descriptor);
	/**
	* @brief 识别端处理服务端返回的数据
	* @param QByteArray:数据，int:socket的描述符
	*/
	void handleReceiveData(QByteArray result, int descriptor);
	/**
	* @brief 识别端处理服务端返回的数据
	*/
	void handleConnect();
	/**
	* @brief 识别端处理服务端返回的数据
	*/
	void handleDisConnect();
signals:
	void statuChanged(QString status);
private:
};

#endif // BLLREALTIMETRANS_H
