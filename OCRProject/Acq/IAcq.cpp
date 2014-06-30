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
	return myAcqDriver->init();
	

}
// 打开设备
LONG IAcq :: read()
{
	return myAcqDriver->open();

}
// 卸载设备
LONG IAcq :: unLoadDevice()
{
	return myAcqDriver->close();
}