
#ifndef OCRCONTROL_H
#define OCRCONTROL_H

#include <QWidget>
#include "ui_OcrControl.h"
#include "Bll/BllRealTimeTrans.h"
#include "Include/HorseDataStruct.h"
#include "Bll/ThreadRealTime.h"
#include "Include/Global.h"
#include "Bll/BllDataIdentity.h"
#include "Bll/ThreadDataIdentity.h"
#define  VERSION_NUM "版本:1.0 2014/06/28 21:45 YP " //
#define  SHOW_ADBMP 1

class OcrControl : public QWidget
{
	Q_OBJECT

public:
	OcrControl(QWidget *parent = 0) ;
	~OcrControl() ;
public slots:
	//连接服务器
	void on_connectBtn_clicked();
	//断开服务器
	void on_disconnectBtn_clicked();
	//登陆服务器
	void on_loginBtn_clicked();
	//请求马信息
	void on_requestHorseInfoBtn_clicked();
	/**
	* @brief 请求RaceId
	*/
	void on_requestRaceIdBtn_clicked();
	/**
	* @brief 提交比赛时长
	*/
	void on_submitRaceTimeBtn_clicked();
	/**
	* @brief 提交实时数据
	*/
	void on_submitRealBtn_clicked();
	//追加网络状态
	void appendStatus(QString status);

	/**
	* @brief 开始采集
	*/
	void on_startAcqBtn_clicked();
	/**
	* @brief 停止采集
	*/
	void on_stopAcqBtn_clicked();
	/**
	* @brief 更新界面
	*/
	void updateData(DataOutput, QByteArray);
	// 更新广告图片
	void updateADData(DataOutput output, QByteArray array);
	void updateUiData(DataOutput& output, QByteArray& array);
	void updateQINQPLData(DataOutput& output, QByteArray& array);
	 
	/**
	* @brief 断开重连
	*/
	void reConnect();
signals:
	void connect(QString,qint32);
	void disconnect();
	void login();
	void requestHorseInfo();
	void requestRaceId(qint32 raceNO);
	void submitRaceTime(qint32 raceTime);
	void submitReal();

	void startAcq();
	void stopAcq();

	void startIdentity();//开始识别
	void stopIdentity();//停止识别

private:
	Ui::OcrControl ui;
	BllRealTimeTrans* bllRealTimeTrans;//实时采集
	ThreadRealTime* threadRealTime;//实时采集线程
	BllDataIdentity* bllDataIdentity;//数据识别
	ThreadDataIdentity* threadDataIdentity;//数据识别线程

	//***马信息**//
	QList<QLabel*> indexLabelList;
	QList<QTextEdit*> horseNameEditList;
	QList<QLabel*> winLableList;
	QList<QLabel*> plaLableList;

	//QIN信息
	QList<QList<QLabel*>> qinList;
	//QPL信息
	QList<QList<QLabel*>> qplList;


};

#endif // OCRCONTROL_H
