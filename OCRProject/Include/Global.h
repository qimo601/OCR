/**
*
* 项    目:  PET/CT软件
* 文件名称:  Global.h
* 文件路径： Include/Global.h
* 摘    要:  全局类、初始化数据库、系统日志线程、网络通信、全局静态变量
* 作    者： 刘兆邦
* 完成日期： 2012年09月05日
* Copyright (c) 2011-2012, 中科院苏州医工所医学影像室电子组.All rights reserved.
* Version v2.0
*/
//为了使QString中的'+'，被当做QStringBuilder的'%'执行，提高效率
#ifdef QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_CONCATENATION
#endif
#ifdef QT_USE_FAST_OPERATOR_PLUS
#define QT_USE_FAST_OPERATOR_PLUS
#endif
// 源代码编码必须是: UTF-8(BOM)  
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef moni_test 
//若Simulation_Test=1，表示模拟测试，Simulation_Test=0表示正式采集
#define moni_test 1
#endif
//下面Qt4.8之后的方法
//#ifdef QT_USE_QSTRINGBUILDER
//#define QT_USE_QSTRINGBUILDER
//#endif


#ifndef Global_H
#define Global_H
#include <QObject>
#include "Net/Network.h"
#include "HorseDataStruct.h"
#include "CCycleBuffer.h"
#include "Acq/ThreadAcq.h"
#include "Acq/IAcq.h"


#define  IMAGE_WIDTH 720 
#define  IMAGE_HEIGHT 576 
#define	 IMAGE_BUFF_LENGTH 720*576*3

class Global : public QObject
{
	Q_OBJECT
public:
	Global(QObject *parent = 0);
	~Global();


	//PET/CT网络设备Id
	//控制台：0001H，主控制器： 0002H，CT影像工作站： 0003H，PET影像工作站0004H，控制盒0005H
	enum ComputerId {
		//Control System(控制台子系统)
		CS = 0x0001,
		//Main Control System(主控制器子系统)
		MCS = 0x0002,
		//CT-Acquisition System(CT采集重建子系统)
		CT_ARS = 0x0003,
		//PET-Acquisition System(PET采集重建子系统)
		PET_ARS = 0x0004,
		//Control Box(控制盒)
		CB = 0x0005
	};

	//**********控制台网络客户端接口*********//
	//控制台相对于主控制器、CT-ARS、PET-ARS都是客户端，主动发起连接者.
	//主控制器网络通讯接口类
	static Network *mcsNetClient;
	//**********控制台网络客户端接口*********//


	//全局缓冲区
	static CCycleBuffer* S_CCycleBuffer;

	//获取计算机设备名称，参数ComputerId枚举型
	static QString getComputerDeviceName(Global::ComputerId);
	//获取计算机设备名称，参数int
	static QString getComputerDeviceName(int computerId);
	//全局客户端状态
	static ClientCmdStatus client_cmd_status;


	static IAcq* myIAcq;//采集类
	static ThreadAcq* threadAcq;//采集线程
	static bool acqStop;//模拟采集标志符


	static bool stopIdentityTag;//识别标识符


	/***********比赛数据***********/
	static qint32 raceId;//比赛唯一识别ID，服务端获得
	static QList<TagHorseInfo> horseInfoList;//赛马信息：HorseID，HorseName，服务端获得
	static qint32 session;//场次号
	static qint32 raceTime;//比赛时间
	/***********比赛数据***********/

	//全局初始化
	void init();
	/**
	* @brief qss初始化
	*/
	void Global::initQss();
	public slots:

signals:
	//初始化采集
	void initAcq();
	//开始采集
	void startAcq();

private:
};

#endif // Global_H