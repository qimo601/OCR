#ifndef BllDataIdentity_H
#define BllDataIdentity_H

#include <QObject>
#include "Include/Global.h"
#include "DataIdentity.h"

//#define  CALLBACK_MODE
#define WRITE_IMAGES_BEFORE_IDENTITY

/*
算法色彩说明 
进入DataIdentity read函数的时候，色彩为反色。
进入have data 函数为了识别广告，先将色彩 cvtColor反一下
然后识别完广告，再反回来。
yp 20140701
*/ 
class BllDataIdentity : public QObject
{
	Q_OBJECT

public:
	BllDataIdentity(QObject *parent = 0 );
	~BllDataIdentity();
	

public slots:
	//初始化算法
	void init();

	//开始识别
	void start();

	//停止识别
	void stop();
signals:
	void readyRead(DataOutput output, QByteArray byteArray);
	void readyReadBmp(DataOutput output, QByteArray byteArray);
private:
	//DataIdentity dataIdentity;//识别算法
	/**
	* @brief 检测 是否图片数据发生变化
	*/
	LONG  isDataOutputNew(DataOutput &outputStruct);
	/**
	* @brief 检测数据输出
	*/
	LONG  handleDataOutput(DataOutput &outputStruct);
	/**
	* @brief 从多次识别出的倒计时、场次号中选出正确的
	*/
	LONG chooseRightRaceTimeRaceSession(DataOutput &outputStruct);

	DataOutput priDataOutput;
	bool stopIdentityTag;//标识符

	// 储存比赛结果信息  最大支持场次号20场  倒计时 30 min
	struct raceNumTimeStruct  myRaceNumberStruct[20];
	struct raceNumTimeStruct  myRaceTimeStruct[30];
	// 数据更新次数统计
	int		dataNewCount; 
#ifdef WRITE_IMAGES_BEFORE_IDENTITY
	int  bmpCount;
#endif
};

#endif // BllDataIdentity_H
