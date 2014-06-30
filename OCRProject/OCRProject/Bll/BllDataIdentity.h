#ifndef BllDataIdentity_H
#define BllDataIdentity_H

#include <QObject>
#include "Include/Global.h"
#include "DataIdentity.h"
class BllDataIdentity : public QObject
{
	Q_OBJECT

public:
	BllDataIdentity(QObject *parent = 0 );
	~BllDataIdentity();
	bool stopIdentityTag;//标识符
public slots:
	//初始化算法
	void init();

	//开始识别
	void start();

	//停止识别
	void stop();
signals:
	void readyRead(DataOutput output, QByteArray byteArray);
private:
	//DataIdentity dataIdentity;//识别算法

};

#endif // BllDataIdentity_H
