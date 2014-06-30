// 源代码编码必须是: UTF-8(BOM)  
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef IACQ_H
#define IACQ_H

#include <QObject>
#include "AcqDriver.h"

//底层数据采集业务层类
class IAcq : public QObject
{
	Q_OBJECT

public:
	IAcq(QObject *parent = 0);
	~IAcq();
	//AcqDriver  * myAcqDriver;
public slots:
	//初始化
	LONG init();
	// ，打开设备
	LONG read();
	// 卸载设备
	LONG unLoadDevice();

private:
	AcqDriver  * myAcqDriver;
	 
};

#endif // IACQ_H
