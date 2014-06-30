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

	stopCaputureFlag = FALSE;


	pbData = new char[IMAGE_BUFF_LENGTH]();
	m_timerId = 0;//初始化
#ifdef OFFLINE_DEBUG

	
	count = 0;
#endif
}

#ifdef OFFLINE_DEBUG


void AcqDriver::createFalseData()
{
	if (count < 20 )
		count += 1 ;
	else
		count = 0 ;


	fileName = QString(".bmp");

	fileName.prepend(QString::number(count, 10));
	//fileName.prepend(QString("./imageSamples/"));
	fileName.prepend(QString("E://RDBS_Yp//OCRProject0627//OCRProject//OCRProject//acqImages//"));

	localImage.load(fileName);

	qDebug("\n It is %d bmp file \n", count);
	localImage = localImage.convertToFormat(QImage::Format_RGB888);
	pbData = (char *)localImage.bits();

	qDebug("AcqDriver:来一帧模拟数据... ");

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

	dwDeviceNum = 0;
	dwDeviceIndex = 0;
	ZeroMemory(&cpVideoInfo, sizeof(VIDEO_SAMPLE_INFO));
	ZeroMemory(&VideoCaptureInfo, sizeof(VIDEO_CAPTURE_INFO));
	imageDataBufLeng = 0;

	if (cpVideoInfo != NULL)
	{
		delete cpVideoInfo;
		cpVideoInfo = NULL;
	}
	if (pbData != NULL)
	{
		delete pbData;
		pbData = NULL;
	}
 
#ifdef	OFFLINE_DEBUG 
	if (m_timerId != 0)
	{
		m_timerId = 0;
		killTimer(m_timerId);
	}
#endif

}

LONG AcqDriver::init()
{
	//返回值
	LONG rtValue = 0 ;
#ifdef  QDEBUGPRINT
	qDebug("Enter init Func AcqDriver Class ");

#endif
	if (rtValue = AVerGetDeviceNum(&dwDeviceNum) != CAP_EC_SUCCESS)
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
	if (dwDeviceNum != 1)
		return CAP_EC_ERROR_STATE;
	for (DWORD dwDeviceIndex = 0; dwDeviceIndex < dwDeviceNum; dwDeviceIndex++)
	{
		QString myString;

		if (rtValue = AVerGetDeviceName(dwDeviceIndex, wcDeviceName) != CAP_EC_SUCCESS)
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
	rtValue |= AVerCreateCaptureObjectEx(dwDeviceNum-1, DEVICETYPE_SD, NULL, &hSDCaptureDevice);
	// 设置电视制式 PAL or NSTC
	rtValue |= AVerSetVideoFormat(hSDCaptureDevice, VIDEOFORMAT_PAL);
	// 设置分辨率
	rtValue |= AVerSetVideoResolution(hSDCaptureDevice, VIDEORESOLUTION_720X576);
	//设置预览
	rtValue |= AVerSetVideoPreviewEnabled(hSDCaptureDevice, TRUE);




	//AVerSetVideoWindowPosition(hSDCaptureDevice, rectClient);
	// 设置视频来源
	rtValue |= AVerSetVideoSource(hSDCaptureDevice, VIDEOSOURCE_SVIDEO);

	if (rtValue == CAP_EC_SUCCESS)
		return CAP_EC_SUCCESS;
	else
	{
		return CAP_EC_ERROR_STATE ;
	}




}


// 打开设备

LONG AcqDriver::open()
{
#ifdef  QDEBUGPRINT
	qDebug("Enter open Func AcqDriver Class ");

#endif
#ifdef OFFLINE_DEBUG
	m_timerId = startTimer(5000);
#endif // OFFLINE_DEBUG

	// 开始视频流	
	LONG rtValue = 0; 
	rtValue |= AVerStartStreaming(hSDCaptureDevice);
#ifdef CALLBACK_MODE
  
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
		rtValue |= AVerCaptureVideoSequenceStart(hSDCaptureDevice, VideoCaptureInfo);

		if (rtValue == CAP_EC_SUCCESS)
			return CAP_EC_SUCCESS;
		else
		{
			return CAP_EC_ERROR_STATE;
		}
 
#endif
#ifndef CALLBACK_MODE
	
	 
		//申请 地址 
		rtValue |= AVerCaptureSingleImageToBuffer(hSDCaptureDevice,
			NULL, &imageDataBufLeng, NULL, 50);
		imageDataBuf = new BYTE[imageDataBufLeng];
		// 500ms 启动定时器
		m_timerId = startTimer(1000);

		if (rtValue == CAP_EC_SUCCESS)
			return CAP_EC_SUCCESS;
		else
		{
			return CAP_EC_ERROR_STATE;
		}
 
#endif // !CALLBACK_MODE

 
}



BOOL WINAPI AcqDriver::readBmpData(VIDEO_SAMPLE_INFO VideoInfo, BYTE *pbData, LONG lLength, __int64 tRefTime, LONG lUserData)
{
	//qDebug("Enter readBmpData func ");
	AcqDriver *pThis = (AcqDriver*)lUserData;
	pThis->writeData(VideoInfo, pbData, lLength, lUserData);
	pThis->cpVideoInfo = &VideoInfo;
	return TRUE;
}
// 读取数据 
void AcqDriver::writeData(VIDEO_SAMPLE_INFO VideoInfo, BYTE *pbData, LONG lLength, LONG lUserData)
{

	AcqDriver *pThis = (AcqDriver*)lUserData;
 
	// 内存拷贝,添加至环形缓冲区
	if (pbData == NULL || lLength > Global::S_CCycleBuffer->getBufSize() )
	{
		qDebug("AcqDriver: writeData wrong ! \n");
	}
	//if (Global::S_CCycleBuffer->getFreeSize() >= lLength )
	{
		Global::S_CCycleBuffer->write((char *)pbData, lLength);

 
	}


}

 
//关闭设备 ，释放内存
LONG AcqDriver::close()
{

 
	//关闭定时器
	if (m_timerId != 0)
	{
		killTimer(m_timerId);
		m_timerId = 0;
	}
	if (imageDataBuf != NULL )
	{
		delete[] imageDataBuf;
		imageDataBuf = NULL;
	}
	if (bmpImageBits !=NULL)
	{
		delete[] bmpImageBits;
		bmpImageBits = NULL;
	}
	
  
#ifdef  QDEBUGPRINT
	qDebug("Enter close Func AcqDriver Class ");

#endif
	// 停止采集
	LONG rtValue = AVerCaptureVideoSequenceStop(hSDCaptureDevice);
	// 关闭
	rtValue |= AVerStopStreaming(hSDCaptureDevice);

	if (rtValue == CAP_EC_SUCCESS)
		return CAP_EC_SUCCESS;
	else
	{
		return CAP_EC_ERROR_STATE ;
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

void AcqDriver::timerEvent(QTimerEvent *event)
{
	// 每个定时器周期更新一次
	if (event->timerId() == m_timerId)
	{
#ifdef  OFFLINE_DEBUG
		createFalseData();
#endif //  OFFLINE_DEBUG
	captureSingleImage();

	}
}

void AcqDriver::captureSingleImage()
{
#ifndef	OFFLINE_DEBUG 
 
	 
	LONG rtValue = AVerCaptureSingleImageToBuffer(hSDCaptureDevice,
		imageDataBuf, &imageDataBufLeng, NULL, 50);
 
	localImage = QImage::fromData((uchar *)imageDataBuf, (int)(imageDataBufLeng));

	localImage = localImage.convertToFormat(QImage::Format_RGB888);
	int imageWidth = localImage.width();
	int imageHeight = localImage.height();
	int imageLength = imageWidth * imageHeight * 3 ;
	localImage.save("acq.bmp");
	//睡眠调节 采集图片时间 1秒两次 
	 
	// 内存拷贝,添加至环形缓冲区
	if (localImage.bits() == NULL || imageLength > Global::S_CCycleBuffer->getBufSize())
	{
		qDebug("AcqDriver: captureSingleImage func wrong ! \n");
	}
	//if (Global::S_CCycleBuffer->getFreeSize() >= lLength )
	{
		Global::S_CCycleBuffer->write((char *)localImage.bits(), imageLength);


	}
 
#endif 
 
}