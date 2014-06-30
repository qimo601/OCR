#include "Global.h"
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QApplication>
Global::Global(QObject *parent)
	: QObject(parent)
{
      
}

Global::~Global()
{
	myIAcq->unLoadDevice();
	delete myIAcq;
}

//主控制器网络通讯接口类
Network *Global::mcsNetClient;
//全局客户端状态
ClientCmdStatus Global::client_cmd_status;
//全局缓冲区
CCycleBuffer* Global::S_CCycleBuffer = 0;


//初始化采集
IAcq* Global::myIAcq = 0;
ThreadAcq* Global::threadAcq = 0;
bool Global::acqStop = false;//模拟采集标志符,开始模拟:false,停止模拟true


bool Global::stopIdentityTag = false;//识别标识符


 /***********比赛数据***********/
qint32 Global::raceId;//比赛唯一识别ID，服务端获得
QList<TagHorseInfo> Global::horseInfoList;//赛马信息：HorseID，HorseName，服务端获得

 /***********比赛数据***********/

/**
 *刘兆邦-添加
 *函数介绍: 全局初始化
 *输入参数: 无
 *返回值: 无
 */
void Global::init()
{

	//初始化样式表
	initQss();

	//服务器网络通讯接口
	mcsNetClient = new Network("Server", "58.67.161.109", 9068);	
	S_CCycleBuffer = new CCycleBuffer();

	//初始化采集
	myIAcq = new IAcq();
	//threadAcq = new ThreadAcq();
	//myIAcq->moveToThread(threadAcq);
	

}

/**
* @brief qss初始化
*/
void Global::initQss()
{
	//全局qss先清空
	//QString ss = qApp->styleSheet();
	//qApp->setStyleSheet("");
	QDir dir;
	QString current = dir.currentPath();
	QFile file("Resources/StyleSheet.qss");
	if (!file.open(QFile::ReadOnly))
	{

		QMessageBox msgBox;
		msgBox.setText("程序出现错误.");
		msgBox.setInformativeText("系统初始化错误，qss文件无法打开，请确认Resources/StyleSheet.qss文件是否存在。\
								  								  								   出错程序:/Include/Global.cpp的initQss()函数");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Ok);
		int ret = msgBox.exec();
	}
	QString styleSheet = file.readAll().data();
	//设定全局qss风格
	qApp->setStyleSheet(styleSheet);
}
/**
 *刘兆邦-添加
 *函数介绍: 通过计算机Id获取计算机设备名称，一般用于系统日志，界面书写
 *输入参数: 枚举类型Global::ComputerId
 *返回值: 无
 */
QString Global::getComputerDeviceName(Global::ComputerId computerId)
{
	QString deviceName;
	switch (computerId)
	{
	case 0x0001:
		deviceName = tr("控制台");
		break;
	case 0x0002:
		deviceName = tr("主控制器");
		break;
	case 0x0003:
		deviceName = tr("CT-ARS");
		break;
	case 0x0004:
		deviceName = tr("PET-ARS");
		break;
	case 0x0005:
		deviceName = tr("控制盒");
		break;
	default:
		deviceName = tr("未明设备");
	}
	return deviceName;
}
/**
 *刘兆邦-添加
 *函数介绍: 通过计算机Id获取计算机设备名称，一般用于系统日志，界面书写
 *输入参数: int,computerId
 *返回值: 无
 */
QString Global::getComputerDeviceName(int computerId)
{
	QString deviceName;
	switch (computerId)
	{
	case 0x0001:
		deviceName = tr("控制台");
		break;
	case 0x0002:
		deviceName = tr("主控制器");
		break;
	case 0x0003:
		deviceName = tr("CT-ARS");
		break;
	case 0x0004:
		deviceName = tr("PET-ARS");
		break;
	case 0x0005:
		deviceName = tr("控制盒");
		break;
	default:
		deviceName = tr("未明设备");
	}
	return deviceName;
}
