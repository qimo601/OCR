#include "AcqDriver.h"
#include <QTimer>
#include "Include/Global.h"

AcqDriver::AcqDriver(QObject *parent)
: QObject(parent)
{
	hSDCaptureDevice = NULL;
	imageDataBufLeng = 0;
	imageDataBuf = NULL;

	cpVideoInfo = new VIDEO_SAMPLE_INFO;
	
	//myCCyclieBuffer = new CCycleBuffer;

	//设置环形缓冲区大小
	// RGB888 分辨率 640*480  
	//myCCyclieBuffer->setBufferSize(3 * 640 * 480 + 100) ;


	pbData = new char[IMAGE_BUFF_LENGTH]();

#ifdef OFFLINE_DEBUG


	localImage.load("1.bmp");

	localImage = localImage.convertToFormat(QImage::Format_RGB888);

	pbData = (char *)localImage.bits();

#endif
}

#ifdef OFFLINE_DEBUG


void AcqDriver::createFalseData()
{
	qDebug("AcqDriver:来一帧模拟数据... " );

	if (pbData == NULL)
		qDebug("pbData is NULL err! \n");
	Global::S_CCycleBuffer->write((char *)pbData, IMAGE_BUFF_LENGTH);

	cpVideoInfo->dwHeight = IMAGE_HEIGHT;
	cpVideoInfo->dwWidth = IMAGE_WIDTH;
	//delete[] pbData;
}

#endif


AcqDriver::~AcqDriver()
{
	hSDCaptureDevice = NULL;
	imageDataBufLeng = 0;
	imageDataBuf = NULL;

	dwDeviceNum = 0 ;
	dwDeviceIndex = 0 ;
	ZeroMemory(&cpVideoInfo, sizeof(VIDEO_SAMPLE_INFO));	 
	ZeroMemory(&VideoCaptureInfo, sizeof(VIDEO_CAPTURE_INFO));
	imageDataBufLeng = 0;

	delete cpVideoInfo;
	delete[] pbData;
	//delete myCCyclieBuffer ;

#ifdef OFFLINE_DEBUG
	if (m_nTimerId != 0)
		killTimer(m_nTimerId);
#endif
}

#ifdef OFFLINE_DEBUG
void AcqDriver::timerEvent(QTimerEvent * event)
{
	qDebug("timer event, id ");
	 
	Global::S_CCycleBuffer->write((char *)pbData, IMAGE_BUFF_LENGTH);

	cpVideoInfo->dwHeight = 480;
	cpVideoInfo->dwWidth = 640;
}

#endif
LONG AcqDriver::init()
{
	//返回值
	LONG rtValue;
#ifdef  QDEBUGPRINT
	qDebug("Enter init Func AcqDriver Class ");

#endif
	if (AVerGetDeviceNum(&dwDeviceNum) != CAP_EC_SUCCESS)
	{
#ifdef  QDEBUGPRINT
		qDebug("Can't get the number of devices.");
#endif
		return 2;
	}
	else
	{
#ifdef  QDEBUGPRINT
		qDebug(" get the number of devices.%d ", dwDeviceNum);
#endif
	}
	for (DWORD dwDeviceIndex = 0; dwDeviceIndex < dwDeviceNum; dwDeviceIndex++)
	{
		QString myString;

		if (AVerGetDeviceName(dwDeviceIndex, wcDeviceName) != CAP_EC_SUCCESS)
		{
#ifdef  QDEBUGPRINT
			qDebug("can not get the name of device.");
#endif
			return 2;
		}
		else
		{
			myString = myString.fromWCharArray(wcDeviceName);
#ifdef  QDEBUGPRINT
			qDebug(" get the name of device. %s", qPrintable(myString));
#endif
		}
		
	}
	//创建 设备
	AVerCreateCaptureObjectEx(0, DEVICETYPE_SD, NULL, &hSDCaptureDevice);
	// 设置电视制式 PAL or NSTC
	AVerSetVideoFormat(hSDCaptureDevice, VIDEOFORMAT_PAL);
	// 设置分辨率
	AVerSetVideoResolution(hSDCaptureDevice, VIDEORESOLUTION_720X576);
	//设置预览
	AVerSetVideoPreviewEnabled(hSDCaptureDevice, TRUE);


	

	//AVerSetVideoWindowPosition(hSDCaptureDevice, rectClient);
	// 设置视频来源
	rtValue = AVerSetVideoSource(hSDCaptureDevice, VIDEOSOURCE_SVIDEO);

	if (rtValue == CAP_EC_SUCCESS)
		return 1;
	else
	{
		return 2;
	}




}
// 打开设备

LONG AcqDriver::open()
{

#ifdef OFFLINE_DEBUG
	/*
	Global::acqStop = false;//开始模拟采集
	while (!Global::acqStop)
	{
		createFalseData();
		Sleep(1000);
	}*/
	m_nTimerId = startTimer(1000);
#endif

#ifdef  QDEBUGPRINT
	qDebug("Enter open Func AcqDriver Class ");

#endif
	// 开始视频流	
	AVerStartStreaming(hSDCaptureDevice);
	//设置采集信息
	ZeroMemory(&VideoCaptureInfo, sizeof(VIDEO_CAPTURE_INFO));
	VideoCaptureInfo.bOverlayMix = FALSE;
	VideoCaptureInfo.dwDurationMode = DURATION_TIME; //
	VideoCaptureInfo.dwDuration = 20;
	VideoCaptureInfo.dwCaptureType = CT_SEQUENCE_FRAME;// CT_SEQUENCE_FRAME;
	VideoCaptureInfo.dwSaveType = ST_CALLBACK_RGB24;
	//设置回调函数
	VideoCaptureInfo.lpCallback = readBmpData;
	VideoCaptureInfo.lCallbackUserData = (LONG)this;
	
		
	//开始采集
	LONG rtValue = AVerCaptureVideoSequenceStart(hSDCaptureDevice, VideoCaptureInfo);

	if (rtValue == CAP_EC_SUCCESS)
		return 1;
	else
	{
		return 2;
	}
}



BOOL WINAPI AcqDriver::readBmpData(VIDEO_SAMPLE_INFO VideoInfo, BYTE *pbData, LONG lLength, __int64 tRefTime, LONG lUserData)
{
	//qDebug("Enter readBmpData func ");
	AcqDriver *pThis = (AcqDriver*)lUserData;
	pThis->writeData(VideoInfo, pbData, lLength, lUserData);
	pThis->cpVideoInfo = & VideoInfo ;
	return TRUE;
}
// 读取数据 
void AcqDriver::writeData(VIDEO_SAMPLE_INFO VideoInfo, BYTE *pbData, LONG lLength, LONG lUserData)
{

	AcqDriver *pThis = (AcqDriver*)lUserData;

	//pThis->imageDataBuf = new char[lLength];
	// 内存拷贝,添加至环形缓冲区
	//if (Global::S_CCycleBuffer->getFreeSize() >= lLength )
	{
		Global::S_CCycleBuffer->write((char *)pbData, lLength);
		

	}
	

}

// 读取图像数据 RGB888
// 输入源 数据 地址指针，返回 数据 和 size 大小 
LONG AcqDriver::read(char * buffer, LONG  * size)
{
	int DataLength = 1000*1000 ;
	 
	*size = imageDataBufLeng;
	if (memcpy(buffer, imageDataBuf, imageDataBufLeng))
		return 1;
	else
		return 2;

}

//关闭设备 ，释放内存
LONG AcqDriver::close()
{

#ifdef OFFLINE_DEBUG
	acqStop = true;//停止模拟
#endif
#ifdef  QDEBUGPRINT
	qDebug("Enter close Func AcqDriver Class ");

#endif
	// 停止采集
	AVerCaptureVideoSequenceStop(hSDCaptureDevice);
	// 关闭
	LONG rtValue = AVerStopStreaming(hSDCaptureDevice);
	/*
	hSDCaptureDevice = NULL;
	imageDataBufLeng = 0;
	imageDataBuf = NULL;

	dwDeviceNum = 0;
	dwDeviceIndex = 0;
	ZeroMemory(&cpVideoInfo, sizeof(VIDEO_SAMPLE_INFO));
	ZeroMemory(&VideoCaptureInfo, sizeof(VIDEO_CAPTURE_INFO));
	imageDataBufLeng = 0;
	*/
	if (rtValue == CAP_EC_SUCCESS)
		return 1;
	else
	{
		return 2;
	}
}

LONG AcqDriver::getCcbUsedSize()
{

	return Global::S_CCycleBuffer->getUsedSize();

}

LONG AcqDriver::ccbRead(char * buffer, int size)
{
	return 	Global::S_CCycleBuffer->read(buffer, size);
}