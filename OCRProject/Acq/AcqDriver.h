// 源代码编码必须是: UTF-8(BOM)  
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef ACQDRIVER_H
#define ACQDRIVER_H

#pragma once
#include <QtWidgets/QMainWindow>
#include "windows.h"
#include "AVSDK/AVerCapAPI.h"
#include "Include/CCycleBuffer.h"
#include <QTimerEvent>
//#define	OFFLINE_DEBUG 
#define CALLBACK_MODE 0

class AcqDriver :public QObject
{
	Q_OBJECT
private:
	char * pbData;
	QImage localImage;
	// 设备句柄
	HANDLE hSDCaptureDevice;
	WCHAR wcDeviceName[MAX_PATH];
	DWORD dwDeviceNum;
	DWORD dwDeviceIndex;
	VIDEO_SAMPLE_INFO * cpVideoInfo;
	char * imageDataBuf;
	LONG imageDataBufLeng;

	VIDEO_CAPTURE_INFO VideoCaptureInfo;

#ifdef OFFLINE_DEBUG
	void createFalseData();
	//真正的定时器
	int m_timerId;
	int count;
	QString fileName;
#endif

public:
	AcqDriver(QObject *parent = 0);
	~AcqDriver();
	// 非callback模式下，停止单幅图片采集 标志位，停止while循环
	BOOL stopCaputureFlag ;

	// 初始化驱动
	LONG init();

	// 打开设备
	LONG open();

	// 读取图像数据 RGB888
	LONG read(char * buffer, LONG * size);

	//关闭设备 ，释放内存
	LONG close();
	// 环形缓冲区相关

	LONG getCcbUsedSize();

	LONG ccbRead(char * buffer, int size);
	//call back 函数
	void writeData(VIDEO_SAMPLE_INFO VideoInfo, BYTE *pbData, LONG lLength, LONG lUserData);
	
	static BOOL WINAPI readBmpData(VIDEO_SAMPLE_INFO VideoInfo, BYTE *pbData,
		LONG lLength, __int64 tRefTime, LONG lUserData);

 
protected:
#ifdef  OFFLINE_DEBUG
	virtual void timerEvent(QTimerEvent *event);
#endif //  OFFLINE_DEBUG
		



};

#endif