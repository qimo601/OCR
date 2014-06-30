#include "OcrControl.h"
#include "Include/HorseDataStruct.h"
#include <QPixmap>
OcrControl::OcrControl(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//网络
	bllRealTimeTrans = new BllRealTimeTrans();
	threadRealTime = new ThreadRealTime();
	bllRealTimeTrans->moveToThread(threadRealTime);
	threadRealTime->start();
	
	QObject::connect(bllRealTimeTrans, SIGNAL(statuChanged(QString)), this, SLOT(appendStatus(QString)));//网络状态反馈
	QObject::connect(this, SIGNAL(connect(QString, qint32)), bllRealTimeTrans, SLOT(connectToHost(QString, qint32)));//连接
	QObject::connect(this, SIGNAL(disconnect()), bllRealTimeTrans, SLOT(disconnectToHost()));//断开
	QObject::connect(this, SIGNAL(login()), bllRealTimeTrans, SLOT(clientLogin()));//登录
	QObject::connect(this, SIGNAL(requestHorseInfo()), bllRealTimeTrans, SLOT(requestHorse()));//请求马信息
	QObject::connect(this, SIGNAL(requestRaceId(qint32)), bllRealTimeTrans, SLOT(requestRaceID(qint32)));//请求马信息
	QObject::connect(this, SIGNAL(submitRaceTime(qint32)), bllRealTimeTrans, SLOT(submitRaceTime(qint32)));//请求马信息
	//QObject::connect(this, SIGNAL(submitReal()), bllRealTimeTrans, SLOT(submitRealData(DataOutput)));//请求马信息



	//采集
	//QObject::connect(this, SIGNAL(startAcq()), Global::myIAcq, SLOT(read()));//开始采集
	//QObject::connect(this, SIGNAL(stopAcq()), Global::myIAcq,  SLOT(unLoadDevice()));//停止采集




	//算法
	bllDataIdentity = new BllDataIdentity();//数据识别
	threadDataIdentity = new ThreadDataIdentity();//数据识别线程
	bllDataIdentity->moveToThread(threadDataIdentity);
	QObject::connect(bllDataIdentity, SIGNAL(readyRead(DataOutput,QByteArray)), bllRealTimeTrans, SLOT(submitRealData(DataOutput)));//开始发送
	QObject::connect(bllDataIdentity, SIGNAL(readyRead(DataOutput, QByteArray)), this, SLOT(updateData(DataOutput, QByteArray)));//停止计算
	QObject::connect(this, SIGNAL(startIdentity()), bllDataIdentity, SLOT(start()));//开始计算
	QObject::connect(this, SIGNAL(stopIdentity()), bllDataIdentity, SLOT(stop()));//停止计算




	for (int i = 0; i < 14; i++)
	{
		QHBoxLayout* itemHBoxLayout_2 = new QHBoxLayout();
		itemHBoxLayout_2->setSpacing(6);
		itemHBoxLayout_2->setObjectName(QStringLiteral("itemHBoxLayout_2"));
		QLabel* indexLbel_2 = new QLabel(ui.horseFrame);
		indexLbel_2->setObjectName(QStringLiteral("indexLbel_2"));
		QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
		sizePolicy1.setHorizontalStretch(0);
		sizePolicy1.setVerticalStretch(0);
		sizePolicy1.setHeightForWidth(indexLbel_2->sizePolicy().hasHeightForWidth());
		indexLbel_2->setSizePolicy(sizePolicy1);
		indexLbel_2->setAlignment(Qt::AlignCenter);

		indexLabelList.append(indexLbel_2);
		itemHBoxLayout_2->addWidget(indexLbel_2);

		QTextEdit* horseNameEdit_2 = new QTextEdit(ui.horseFrame);
		horseNameEdit_2->setObjectName(QStringLiteral("horseNameEdit_2"));
		sizePolicy1.setHeightForWidth(horseNameEdit_2->sizePolicy().hasHeightForWidth());
		horseNameEdit_2->setSizePolicy(sizePolicy1);
		horseNameEdit_2->setMaximumSize(QSize(16777215, 20));

		horseNameLableList.append(horseNameEdit_2);
		itemHBoxLayout_2->addWidget(horseNameEdit_2);

		QLabel* winLbl_2 = new QLabel(ui.horseFrame);
		winLbl_2->setObjectName(QStringLiteral("winLbl_2"));
		sizePolicy1.setHeightForWidth(winLbl_2->sizePolicy().hasHeightForWidth());
		winLbl_2->setSizePolicy(sizePolicy1);
		winLbl_2->setAlignment(Qt::AlignCenter);

		winLableList.append(winLbl_2);
		itemHBoxLayout_2->addWidget(winLbl_2);

		QLabel* PLALbl_2 = new QLabel(ui.horseFrame);
		PLALbl_2->setObjectName(QStringLiteral("PLALbl_2"));
		sizePolicy1.setHeightForWidth(PLALbl_2->sizePolicy().hasHeightForWidth());
		PLALbl_2->setSizePolicy(sizePolicy1);
		PLALbl_2->setAlignment(Qt::AlignCenter);

		plaLableList.append(PLALbl_2);
		itemHBoxLayout_2->addWidget(PLALbl_2);

		itemHBoxLayout_2->setStretch(0, 1);
		itemHBoxLayout_2->setStretch(1, 3);
		itemHBoxLayout_2->setStretch(2, 3);
		itemHBoxLayout_2->setStretch(3, 3);

		ui.verticalLayout_4->addLayout(itemHBoxLayout_2);

		
	}

	QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

	ui.verticalLayout_4->addItem(verticalSpacer);

}

OcrControl::~OcrControl()
{
	if (threadRealTime->isRunning())
	{
		threadRealTime->quit();
	}
	delete bllRealTimeTrans;
	delete threadRealTime;
}
/**
* @brief 连接服务器
*/
void OcrControl::on_connectBtn_clicked()
{
	emit connect("58.67.161.109", 9068);
}
/**
* @brief 断开服务器
*/
void OcrControl::on_disconnectBtn_clicked()
{
	emit disconnect();
}
/**
* @brief 登陆服务器
*/
void OcrControl::on_loginBtn_clicked()
{
	emit login();
}
/**
* @brief 请求马信息
*/
void OcrControl::on_requestHorseInfoBtn_clicked()
{
	emit requestHorseInfo();
}

/**
* @brief 请求RaceId
*/
void OcrControl::on_requestRaceIdBtn_clicked()
{
	emit requestRaceId(1);//每次只有1场
}
/**
* @brief 提交比赛时长
*/
void OcrControl::on_submitRaceTimeBtn_clicked()
{
	emit submitRaceTime(35);
}
/**
* @brief 提交实时数据
*/
void OcrControl::on_submitRealBtn_clicked()
{
	emit submitReal();
}
/**
* @brief 追加网络状态
*/
void OcrControl::appendStatus(QString status)
{
	ui.textBrowser->append(status);
}
/**
* @brief 开始采集
*/
void OcrControl::on_startAcqBtn_clicked()
{
	Global::acqStop = false;//开始模拟标示符
 //	Global::threadAcq->start();//采集启动
	Global::myIAcq->read();

	//emit startAcq();//开始采集

	threadDataIdentity->start();//开始识别

	emit startIdentity();//开始识别
}
/**
* @brief 停止采集
*/
void OcrControl::on_stopAcqBtn_clicked()
{
	Global::acqStop = true;//停止模拟标示符

	//emit stopAcq();//停止采集
	Global::myIAcq->unLoadDevice();

	emit stopIdentity();//停止识别
	Global::threadAcq->quit();
	threadDataIdentity->quit();

}
/**
* @brief 停止采集
*/
void OcrControl::updateData(DataOutput output, QByteArray array)
{
	QPixmap pixmap;	
	QImage myImage;
	myImage = QImage(IMAGE_WIDTH, IMAGE_HEIGHT, QImage::Format_RGB888);  
	char * buffer;
	buffer = new char[IMAGE_BUFF_LENGTH];
	memcpy(buffer,array.data(),IMAGE_BUFF_LENGTH) ; 
	 
	// 转换RGB888 到QIMAGE
	for (int h = 0; h < IMAGE_HEIGHT; h++) {
		// scanLine returns a ptr to the start of the data for that row 
		memcpy(myImage.scanLine(h), (buffer + IMAGE_WIDTH * 3 * h),
			IMAGE_WIDTH * 3);
	}
	myImage = myImage.scaled(IMAGE_WIDTH *0.8, IMAGE_HEIGHT *0.8);
	pixmap = pixmap.fromImage(myImage);
	ui.imageLbl->setPixmap(pixmap);

 

	updateUiData(output, array);
	
	
	delete[] buffer;

}

void OcrControl::updateUiData(DataOutput& output, QByteArray& array)
{
	for (int i = 0; i < indexLabelList.size(); i++)
	{
		indexLabelList[i]->setText(QString::number(i));
	}
	for (int i = 0; i < horseNameLableList.size(); i++)
	{
		
		horseNameLableList[i]->setText(QString("马名%1").arg(i));
	}
	for (int i = 0; i < horseNameLableList.size(); i++)
	{

		winLableList[i]->setText(QString::number(output.WIN[i]));
	}
	for (int i = 0; i < horseNameLableList.size(); i++)
	{

		plaLableList[i]->setText(QString::number(output.PLA[i]));
	}
}

