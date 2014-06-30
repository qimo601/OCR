#include "iacq.h"
//
IAcq::IAcq(QObject *parent)
	: QObject(parent)
{
	myAcqDriver = new AcqDriver;
	init();
	setObjectName("IAcq123456");
}

IAcq::~IAcq()
{
	if (myAcqDriver != NULL )
	{
	 	//delete myAcqDriver;
		myAcqDriver = NULL;
	}

}

//初始化
LONG IAcq :: init()
{
	LONG rtValue = myAcqDriver->init(); 
	if (rtValue != CAP_EC_SUCCESS)
	{
		qDebug("IAcq: init driver failed error state \n");
		return CAP_EC_ERROR_STATE;
	}
		
	return rtValue;
	

}
// 打开设备
LONG IAcq :: read()
{
	myAcqDriver->stopCaputureFlag = TRUE ;
	LONG rtValue = myAcqDriver->open();
	if (rtValue != CAP_EC_SUCCESS)
	{
		qDebug("IAcq: read driver failed error state \n");
		return CAP_EC_ERROR_STATE;
	}

	return rtValue;

}
// 卸载设备
LONG IAcq :: unLoadDevice()
{
	myAcqDriver->stopCaputureFlag = FALSE;
	LONG rtValue = myAcqDriver->close();

	if (rtValue != CAP_EC_SUCCESS)
	{
		qDebug("IAcq: unLoadDevice driver failed error state \n");
		return CAP_EC_ERROR_STATE;
	}
 
}