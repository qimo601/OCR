#ifndef BllDataIdentity_H
#define BllDataIdentity_H

#include <QObject>
#include "Include/Global.h"
#include "DataIdentity.h"
#define WRITE_IMAGES_BEFORE_IDENTITY

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
	DataOutput priDataOutput;
	bool stopIdentityTag;//标识符
#ifdef WRITE_IMAGES_BEFORE_IDENTITY
	int  bmpCount;
#endif
};

#endif // BllDataIdentity_H
