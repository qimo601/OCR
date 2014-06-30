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


	QObject::connect(Global::mcsNetClient, SIGNAL(disConnectToHostSuccessSignal()), this, SLOT(reConnect()));//断开重连



	//采集
	//QObject::connect(this, SIGNAL(startAcq()), Global::myIAcq, SLOT(read()));//开始采集
	//QObject::connect(this, SIGNAL(stopAcq()), Global::myIAcq,  SLOT(unLoadDevice()));//停止采集

	//算法
	bllDataIdentity = new BllDataIdentity();//数据识别
	threadDataIdentity = new ThreadDataIdentity();//数据识别线程
	bllDataIdentity->moveToThread(threadDataIdentity);
	QObject::connect(bllDataIdentity, SIGNAL(readyRead(DataOutput,QByteArray)), bllRealTimeTrans, SLOT(submitRealData(DataOutput)));//开始发送
	QObject::connect(bllDataIdentity, SIGNAL(readyRead(DataOutput, QByteArray)), this, SLOT(updateData(DataOutput, QByteArray)));//停止计算

	//显示广告	
	QObject::connect(bllDataIdentity, SIGNAL(readyReadBmp(DataOutput, QByteArray)), this, SLOT(updateData(DataOutput, QByteArray)));//停止计算

	QObject::connect(this, SIGNAL(startIdentity()), bllDataIdentity, SLOT(start()));//开始计算
	QObject::connect(this, SIGNAL(stopIdentity()), bllDataIdentity, SLOT(stop()));//停止计算

	


	//初始化马信息
	for (int i = 0; i < 14; i++)
	{
		QFrame* frame = new QFrame(ui.horseFrame);
		frame->setObjectName(QStringLiteral("frame"));
		frame->setStyleSheet(QLatin1String("QFrame#frame\n"
			"{\n"
			"	border-bottom: 0px solid #9D9D9D;\n"
			"	border-radius:0px;\n"
			"    padding:0 0px;\n"
			"	margin-right: 0px;\n"
			"\n"
			"}\n"
			""));
		frame->setFrameShape(QFrame::StyledPanel);
		frame->setFrameShadow(QFrame::Plain);
		QHBoxLayout* horizontalLayout_2 = new QHBoxLayout(frame);
		horizontalLayout_2->setSpacing(6);
		horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
		horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
		horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
		QLabel* indexLbel_3 = new QLabel(frame);
		indexLbel_3->setObjectName(QStringLiteral("indexLbel_3"));
		QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
		sizePolicy.setHorizontalStretch(0);
		sizePolicy.setVerticalStretch(0);
		sizePolicy.setHeightForWidth(indexLbel_3->sizePolicy().hasHeightForWidth());
		indexLbel_3->setSizePolicy(sizePolicy);
		indexLbel_3->setAlignment(Qt::AlignLeft);

		indexLbel_3->setMinimumSize(QSize(40, 20));
		indexLbel_3->setMaximumSize(QSize(40, 20));
		indexLabelList.append(indexLbel_3);
		horizontalLayout_2->addWidget(indexLbel_3);

		QTextEdit* horseNameEdit_3 = new QTextEdit(frame);
		horseNameEdit_3->setObjectName(QStringLiteral("horseNameEdit_3"));
		QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
		sizePolicy1.setHorizontalStretch(0);
		sizePolicy1.setVerticalStretch(0);
		sizePolicy1.setHeightForWidth(horseNameEdit_3->sizePolicy().hasHeightForWidth());
		horseNameEdit_3->setSizePolicy(sizePolicy1);
		horseNameEdit_3->setMinimumSize(QSize(16777215, 20));
		horseNameEdit_3->setMaximumSize(QSize(16777215, 20));
		horseNameEditList.append(horseNameEdit_3);
		horizontalLayout_2->addWidget(horseNameEdit_3);

		QLabel* winLbl_3 = new QLabel(frame);
		winLbl_3->setObjectName(QStringLiteral("winLbl_3"));
		sizePolicy.setHeightForWidth(winLbl_3->sizePolicy().hasHeightForWidth());
		winLbl_3->setSizePolicy(sizePolicy);
		QFont font1;
		font1.setPointSize(14);
		winLbl_3->setFont(font1);
		winLbl_3->setAlignment(Qt::AlignLeft);
		winLbl_3->setMinimumSize(QSize(40, 20));
		winLbl_3->setMaximumSize(QSize(40, 20));
		winLableList.append(winLbl_3);
		horizontalLayout_2->addWidget(winLbl_3);

		QLabel* PLALbl_3 = new QLabel(frame);
		PLALbl_3->setObjectName(QStringLiteral("PLALbl_3"));
		sizePolicy.setHeightForWidth(PLALbl_3->sizePolicy().hasHeightForWidth());
		PLALbl_3->setSizePolicy(sizePolicy);
		PLALbl_3->setFont(font1);
		PLALbl_3->setAlignment(Qt::AlignLeft);

		PLALbl_3->setMinimumSize(QSize(40, 20));
		PLALbl_3->setMaximumSize(QSize(40, 20));
		plaLableList.append(PLALbl_3);
		horizontalLayout_2->addWidget(PLALbl_3);

		horizontalLayout_2->setStretch(0, 1);
		horizontalLayout_2->setStretch(1, 3);
		horizontalLayout_2->setStretch(2, 3);
		horizontalLayout_2->setStretch(3, 3);

		ui.verticalLayout_4->addWidget(frame);


		
	}

	QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

	ui.verticalLayout_4->addItem(verticalSpacer);



	//初始化Qin信息
	/*for (int i = 0; i < 7; i++)
	{*/
		for (int j = 0; j < 7; j++)
		{
			QList<QLabel*> list;
			QHBoxLayout* horizontalLayout_3 = new QHBoxLayout();
			horizontalLayout_3->setSpacing(6);
			horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
			QLabel* qinLbl_1 = new QLabel(ui.qinFrame);
			qinLbl_1->setObjectName(QStringLiteral("qinLbl_1"));
			QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
			sizePolicy2.setHorizontalStretch(0);
			sizePolicy2.setVerticalStretch(0);
			sizePolicy2.setHeightForWidth(qinLbl_1->sizePolicy().hasHeightForWidth());

			qinLbl_1->setSizePolicy(sizePolicy2);

			qinLbl_1->setMinimumSize(QSize(36, 14));
			qinLbl_1->setMaximumSize(QSize(36, 14));
			qinLbl_1->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));

			list.append(qinLbl_1);
			horizontalLayout_3->addWidget(qinLbl_1);

			QLabel* qinLbl_2 = new QLabel(ui.qinFrame);
			qinLbl_2->setObjectName(QStringLiteral("qinLbl_2"));
			sizePolicy2.setHeightForWidth(qinLbl_2->sizePolicy().hasHeightForWidth());
			qinLbl_2->setSizePolicy(sizePolicy2);
			qinLbl_2->setMinimumSize(QSize(36, 14));
			qinLbl_2->setMaximumSize(QSize(36, 14));
			qinLbl_2->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
			list.append(qinLbl_2);
			horizontalLayout_3->addWidget(qinLbl_2);

			QLabel* qinLbl_3 = new QLabel(ui.qinFrame);
			qinLbl_3->setObjectName(QStringLiteral("qinLbl_3"));
			sizePolicy2.setHeightForWidth(qinLbl_3->sizePolicy().hasHeightForWidth());
			qinLbl_3->setSizePolicy(sizePolicy2);

			qinLbl_3->setMinimumSize(QSize(36, 14));
			qinLbl_3->setMaximumSize(QSize(36, 14));
			qinLbl_3->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
			list.append(qinLbl_3);
			horizontalLayout_3->addWidget(qinLbl_3);

			QLabel* qinLbl_4 = new QLabel(ui.qinFrame);
			qinLbl_4->setObjectName(QStringLiteral("qinLbl_4"));
			sizePolicy2.setHeightForWidth(qinLbl_4->sizePolicy().hasHeightForWidth());
			qinLbl_4->setSizePolicy(sizePolicy2);
			qinLbl_4->setMinimumSize(QSize(36, 14));
			qinLbl_4->setMaximumSize(QSize(36, 14));
			qinLbl_4->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
			list.append(qinLbl_4);
			horizontalLayout_3->addWidget(qinLbl_4);

			QLabel* qinLbl_5 = new QLabel(ui.qinFrame);
			qinLbl_5->setObjectName(QStringLiteral("qinLbl_5"));
			sizePolicy2.setHeightForWidth(qinLbl_5->sizePolicy().hasHeightForWidth());
			qinLbl_5->setSizePolicy(sizePolicy2);
			qinLbl_5->setMinimumSize(QSize(36, 14));
			qinLbl_5->setMaximumSize(QSize(36, 14));
			qinLbl_5->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
			list.append(qinLbl_5);
			horizontalLayout_3->addWidget(qinLbl_5);

			QLabel* qinLbl_6 = new QLabel(ui.qinFrame);
			qinLbl_6->setObjectName(QStringLiteral("qinLbl_6"));
			sizePolicy2.setHeightForWidth(qinLbl_6->sizePolicy().hasHeightForWidth());
			qinLbl_6->setSizePolicy(sizePolicy2);
			qinLbl_6->setMinimumSize(QSize(36, 14));
			qinLbl_6->setMaximumSize(QSize(36, 14));
			qinLbl_6->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
			list.append(qinLbl_6);
			horizontalLayout_3->addWidget(qinLbl_6);

			QLabel* qinLbl_7 = new QLabel(ui.qinFrame);
			qinLbl_7->setObjectName(QStringLiteral("qinLbl_7"));
			sizePolicy2.setHeightForWidth(qinLbl_7->sizePolicy().hasHeightForWidth());
			qinLbl_7->setSizePolicy(sizePolicy2);
			qinLbl_7->setMinimumSize(QSize(36, 14));
			qinLbl_7->setMaximumSize(QSize(36, 14));
			qinLbl_7->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
			list.append(qinLbl_7);
			horizontalLayout_3->addWidget(qinLbl_7);

			QLabel* qinLbl_8 = new QLabel(ui.qinFrame);
			qinLbl_8->setObjectName(QStringLiteral("qinLbl_8"));
			sizePolicy2.setHeightForWidth(qinLbl_8->sizePolicy().hasHeightForWidth());
			qinLbl_8->setSizePolicy(sizePolicy2);
			qinLbl_8->setMinimumSize(QSize(36, 14));
			qinLbl_8->setMaximumSize(QSize(36, 14));
			qinLbl_8->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
			list.append(qinLbl_8);
			horizontalLayout_3->addWidget(qinLbl_8);

			QLabel* qinLbl_9 = new QLabel(ui.qinFrame);
			qinLbl_9->setObjectName(QStringLiteral("qinLbl_9"));
			sizePolicy2.setHeightForWidth(qinLbl_9->sizePolicy().hasHeightForWidth());
			qinLbl_9->setSizePolicy(sizePolicy2);
			qinLbl_9->setMinimumSize(QSize(36, 14));
			qinLbl_9->setMaximumSize(QSize(36, 14));
			qinLbl_9->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
			list.append(qinLbl_9);
			horizontalLayout_3->addWidget(qinLbl_9);

			QLabel* qinLbl_10 = new QLabel(ui.qinFrame);
			qinLbl_10->setObjectName(QStringLiteral("qinLbl_10"));
			sizePolicy2.setHeightForWidth(qinLbl_10->sizePolicy().hasHeightForWidth());
			qinLbl_10->setSizePolicy(sizePolicy2);
			qinLbl_10->setMinimumSize(QSize(36, 14));
			qinLbl_10->setMaximumSize(QSize(36, 14));
			qinLbl_10->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
			list.append(qinLbl_10);
			horizontalLayout_3->addWidget(qinLbl_10);

			QLabel* qinLbl_11 = new QLabel(ui.qinFrame);
			qinLbl_11->setObjectName(QStringLiteral("qinLbl_11"));
			sizePolicy2.setHeightForWidth(qinLbl_11->sizePolicy().hasHeightForWidth());
			qinLbl_11->setSizePolicy(sizePolicy2);
			qinLbl_11->setMinimumSize(QSize(36, 14));
			qinLbl_11->setMaximumSize(QSize(36, 14));
			qinLbl_11->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
			list.append(qinLbl_11);
			horizontalLayout_3->addWidget(qinLbl_11);

			QLabel* qinLbl_12 = new QLabel(ui.qinFrame);
			qinLbl_12->setObjectName(QStringLiteral("qinLbl_12"));
			sizePolicy2.setHeightForWidth(qinLbl_12->sizePolicy().hasHeightForWidth());
			qinLbl_12->setSizePolicy(sizePolicy2);
			qinLbl_12->setMinimumSize(QSize(36, 14));
			qinLbl_12->setMaximumSize(QSize(36, 14));
			qinLbl_12->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
			list.append(qinLbl_12);
			horizontalLayout_3->addWidget(qinLbl_12);

			QLabel* qinLbl_13 = new QLabel(ui.qinFrame);
			qinLbl_13->setObjectName(QStringLiteral("qinLbl_13"));
			sizePolicy2.setHeightForWidth(qinLbl_13->sizePolicy().hasHeightForWidth());
			qinLbl_13->setSizePolicy(sizePolicy2);
			qinLbl_13->setMinimumSize(QSize(36, 14));
			qinLbl_13->setMaximumSize(QSize(36, 14));
			qinLbl_13->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
			list.append(qinLbl_13);
			horizontalLayout_3->addWidget(qinLbl_13);

			QLabel* qinLbl_14 = new QLabel(ui.qinFrame);
			qinLbl_14->setObjectName(QStringLiteral("qinLbl_14"));
			sizePolicy2.setHeightForWidth(qinLbl_14->sizePolicy().hasHeightForWidth());
			qinLbl_14->setSizePolicy(sizePolicy2);
			qinLbl_14->setMinimumSize(QSize(36, 14));
			qinLbl_14->setMaximumSize(QSize(36, 14));
			qinLbl_14->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
			list.append(qinLbl_14);
			horizontalLayout_3->addWidget(qinLbl_14);

			QLabel* qinLbl_15 = new QLabel(ui.qinFrame);
			qinLbl_15->setObjectName(QStringLiteral("qinLbl_15"));
			sizePolicy2.setHeightForWidth(qinLbl_15->sizePolicy().hasHeightForWidth());
			qinLbl_15->setSizePolicy(sizePolicy2);
			qinLbl_15->setMinimumSize(QSize(36, 14));
			qinLbl_15->setMaximumSize(QSize(36, 14));
			qinLbl_15->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
			list.append(qinLbl_15);
			horizontalLayout_3->addWidget(qinLbl_15);

			qinList.append(list);
			ui.verticalLayout_5->addLayout(horizontalLayout_3);
		}
	//}
	QSpacerItem* verticalSpacer1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	ui.verticalLayout_5->addItem(verticalSpacer1);

	//初始化QPL
	for (int j = 0; j < 7; j++)
	{
		QList<QLabel*> list;
		QHBoxLayout* horizontalLayout_3 = new QHBoxLayout();
		horizontalLayout_3->setSpacing(6);
		horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
		QLabel* qinLbl_1 = new QLabel(ui.qplFrame);
		qinLbl_1->setObjectName(QStringLiteral("qinLbl_1"));
		QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
		sizePolicy2.setHorizontalStretch(0);
		sizePolicy2.setVerticalStretch(0);
		sizePolicy2.setHeightForWidth(qinLbl_1->sizePolicy().hasHeightForWidth());

		qinLbl_1->setSizePolicy(sizePolicy2);

		qinLbl_1->setMinimumSize(QSize(36, 14));
		qinLbl_1->setMaximumSize(QSize(36, 14));
		qinLbl_1->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));

		list.append(qinLbl_1);
		horizontalLayout_3->addWidget(qinLbl_1);

		QLabel* qinLbl_2 = new QLabel(ui.qplFrame);
		qinLbl_2->setObjectName(QStringLiteral("qinLbl_2"));
		sizePolicy2.setHeightForWidth(qinLbl_2->sizePolicy().hasHeightForWidth());
		qinLbl_2->setSizePolicy(sizePolicy2);
		qinLbl_2->setMinimumSize(QSize(36, 14));
		qinLbl_2->setMaximumSize(QSize(36, 14));
		qinLbl_2->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
		list.append(qinLbl_2);
		horizontalLayout_3->addWidget(qinLbl_2);

		QLabel* qinLbl_3 = new QLabel(ui.qplFrame);
		qinLbl_3->setObjectName(QStringLiteral("qinLbl_3"));
		sizePolicy2.setHeightForWidth(qinLbl_3->sizePolicy().hasHeightForWidth());
		qinLbl_3->setSizePolicy(sizePolicy2);

		qinLbl_3->setMinimumSize(QSize(36, 14));
		qinLbl_3->setMaximumSize(QSize(36, 14));
		qinLbl_3->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
		list.append(qinLbl_3);
		horizontalLayout_3->addWidget(qinLbl_3);

		QLabel* qinLbl_4 = new QLabel(ui.qplFrame);
		qinLbl_4->setObjectName(QStringLiteral("qinLbl_4"));
		sizePolicy2.setHeightForWidth(qinLbl_4->sizePolicy().hasHeightForWidth());
		qinLbl_4->setSizePolicy(sizePolicy2);
		qinLbl_4->setMinimumSize(QSize(36, 14));
		qinLbl_4->setMaximumSize(QSize(36, 14));
		qinLbl_4->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
		list.append(qinLbl_4);
		horizontalLayout_3->addWidget(qinLbl_4);

		QLabel* qinLbl_5 = new QLabel(ui.qplFrame);
		qinLbl_5->setObjectName(QStringLiteral("qinLbl_5"));
		sizePolicy2.setHeightForWidth(qinLbl_5->sizePolicy().hasHeightForWidth());
		qinLbl_5->setSizePolicy(sizePolicy2);
		qinLbl_5->setMinimumSize(QSize(36, 14));
		qinLbl_5->setMaximumSize(QSize(36, 14));
		qinLbl_5->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
		list.append(qinLbl_5);
		horizontalLayout_3->addWidget(qinLbl_5);

		QLabel* qinLbl_6 = new QLabel(ui.qplFrame);
		qinLbl_6->setObjectName(QStringLiteral("qinLbl_6"));
		sizePolicy2.setHeightForWidth(qinLbl_6->sizePolicy().hasHeightForWidth());
		qinLbl_6->setSizePolicy(sizePolicy2);
		qinLbl_6->setMinimumSize(QSize(36, 14));
		qinLbl_6->setMaximumSize(QSize(36, 14));
		qinLbl_6->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
		list.append(qinLbl_6);
		horizontalLayout_3->addWidget(qinLbl_6);

		QLabel* qinLbl_7 = new QLabel(ui.qinFrame);
		qinLbl_7->setObjectName(QStringLiteral("qinLbl_7"));
		sizePolicy2.setHeightForWidth(qinLbl_7->sizePolicy().hasHeightForWidth());
		qinLbl_7->setSizePolicy(sizePolicy2);
		qinLbl_7->setMinimumSize(QSize(36, 14));
		qinLbl_7->setMaximumSize(QSize(36, 14));
		qinLbl_7->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
		list.append(qinLbl_7);
		horizontalLayout_3->addWidget(qinLbl_7);

		QLabel* qinLbl_8 = new QLabel(ui.qplFrame);
		qinLbl_8->setObjectName(QStringLiteral("qinLbl_8"));
		sizePolicy2.setHeightForWidth(qinLbl_8->sizePolicy().hasHeightForWidth());
		qinLbl_8->setSizePolicy(sizePolicy2);
		qinLbl_8->setMinimumSize(QSize(36, 14));
		qinLbl_8->setMaximumSize(QSize(36, 14));
		qinLbl_8->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
		list.append(qinLbl_8);
		horizontalLayout_3->addWidget(qinLbl_8);

		QLabel* qinLbl_9 = new QLabel(ui.qplFrame);
		qinLbl_9->setObjectName(QStringLiteral("qinLbl_9"));
		sizePolicy2.setHeightForWidth(qinLbl_9->sizePolicy().hasHeightForWidth());
		qinLbl_9->setSizePolicy(sizePolicy2);
		qinLbl_9->setMinimumSize(QSize(36, 14));
		qinLbl_9->setMaximumSize(QSize(36, 14));
		qinLbl_9->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
		list.append(qinLbl_9);
		horizontalLayout_3->addWidget(qinLbl_9);

		QLabel* qinLbl_10 = new QLabel(ui.qplFrame);
		qinLbl_10->setObjectName(QStringLiteral("qinLbl_10"));
		sizePolicy2.setHeightForWidth(qinLbl_10->sizePolicy().hasHeightForWidth());
		qinLbl_10->setSizePolicy(sizePolicy2);
		qinLbl_10->setMinimumSize(QSize(36, 14));
		qinLbl_10->setMaximumSize(QSize(36, 14));
		qinLbl_10->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
		list.append(qinLbl_10);
		horizontalLayout_3->addWidget(qinLbl_10);

		QLabel* qinLbl_11 = new QLabel(ui.qplFrame);
		qinLbl_11->setObjectName(QStringLiteral("qinLbl_11"));
		sizePolicy2.setHeightForWidth(qinLbl_11->sizePolicy().hasHeightForWidth());
		qinLbl_11->setSizePolicy(sizePolicy2);
		qinLbl_11->setMinimumSize(QSize(36, 14));
		qinLbl_11->setMaximumSize(QSize(36, 14));
		qinLbl_11->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
		list.append(qinLbl_11);
		horizontalLayout_3->addWidget(qinLbl_11);

		QLabel* qinLbl_12 = new QLabel(ui.qinFrame);
		qinLbl_12->setObjectName(QStringLiteral("qinLbl_12"));
		sizePolicy2.setHeightForWidth(qinLbl_12->sizePolicy().hasHeightForWidth());
		qinLbl_12->setSizePolicy(sizePolicy2);
		qinLbl_12->setMinimumSize(QSize(36, 14));
		qinLbl_12->setMaximumSize(QSize(36, 14));
		qinLbl_12->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
		list.append(qinLbl_12);
		horizontalLayout_3->addWidget(qinLbl_12);

		QLabel* qinLbl_13 = new QLabel(ui.qinFrame);
		qinLbl_13->setObjectName(QStringLiteral("qinLbl_13"));
		sizePolicy2.setHeightForWidth(qinLbl_13->sizePolicy().hasHeightForWidth());
		qinLbl_13->setSizePolicy(sizePolicy2);
		qinLbl_13->setMinimumSize(QSize(36, 14));
		qinLbl_13->setMaximumSize(QSize(36, 14));
		qinLbl_13->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
		list.append(qinLbl_13);
		horizontalLayout_3->addWidget(qinLbl_13);

		QLabel* qinLbl_14 = new QLabel(ui.qinFrame);
		qinLbl_14->setObjectName(QStringLiteral("qinLbl_14"));
		sizePolicy2.setHeightForWidth(qinLbl_14->sizePolicy().hasHeightForWidth());
		qinLbl_14->setSizePolicy(sizePolicy2);
		qinLbl_14->setMinimumSize(QSize(36, 14));
		qinLbl_14->setMaximumSize(QSize(36, 14));
		qinLbl_14->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
		list.append(qinLbl_14);
		horizontalLayout_3->addWidget(qinLbl_14);

		QLabel* qinLbl_15 = new QLabel(ui.qinFrame);
		qinLbl_15->setObjectName(QStringLiteral("qinLbl_15"));
		sizePolicy2.setHeightForWidth(qinLbl_15->sizePolicy().hasHeightForWidth());
		qinLbl_15->setSizePolicy(sizePolicy2);
		qinLbl_15->setMinimumSize(QSize(36, 14));
		qinLbl_15->setMaximumSize(QSize(36, 14));
		qinLbl_15->setStyleSheet(QStringLiteral("background-color: rgb(145, 130, 255);"));
		list.append(qinLbl_15);
		horizontalLayout_3->addWidget(qinLbl_15);

		qplList.append(list);
		ui.verticalLayout_12->addLayout(horizontalLayout_3);
	}


	//设置版本号 
	QPalette pe;
	pe.setColor(QPalette::WindowText, Qt::white);
	ui.versionNumLabel->setText(VERSION_NUM);
	ui.versionNumLabel->setPalette(pe);

}

OcrControl::~OcrControl()
{
	//停止实时提交
	if (threadRealTime->isRunning())
	{
		threadRealTime->quit();
	}
	//删除实时网络传输业务
	if (bllRealTimeTrans!=0)
		delete bllRealTimeTrans;
	//删除网络传输线程
	if (threadRealTime != 0)
	{
		//threadRealTime->terminate();
		threadRealTime->wait();
		delete threadRealTime;
	}
	//删除识别算法线程
	if (threadDataIdentity->isRunning())
	{
		Global::stopIdentityTag = true;//停止识别
		threadDataIdentity->quit();
	}


	if (Global::S_CCycleBuffer != 0)
	{
		delete Global::S_CCycleBuffer;
	}
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
	//Global::threadAcq->start();//采集启动
	//emit startAcq();//开始采集

	threadDataIdentity->start();//开始识别

	emit startIdentity();//开始识别
	Global::myIAcq->read();

}
/**
* @brief 停止采集
*/
void OcrControl::on_stopAcqBtn_clicked()
{
	Global::acqStop = true;//停止模拟标示符
	//emit stopAcq();//停止采集

	//停止采集 while 循环
 
	Global::myIAcq->unLoadDevice();
	//Global::threadAcq->quit();

	//emit stopIdentity();//停止识别
	

	Global::stopIdentityTag = true;//停止识别
	threadDataIdentity->quit();

}
/**
* @brief 停止采集
*/
void OcrControl::updateData(DataOutput output, QByteArray array)
{

	

	if (SHOW_ADBMP | output.haveDataFlag )
	{
		//更新图片信息
		QPixmap pixmap;
		QImage myImage;
		myImage = QImage(IMAGE_WIDTH, IMAGE_HEIGHT, QImage::Format_RGB888);
		char * buffer;
		buffer = new char[IMAGE_BUFF_LENGTH];
		memcpy(buffer, array.data(), IMAGE_BUFF_LENGTH);

		// 转换RGB888 到QIMAGE
		for (int h = 0; h < IMAGE_HEIGHT; h++) {
			// scanLine returns a ptr to the start of the data for that row 
			memcpy(myImage.scanLine(h), (buffer + IMAGE_WIDTH * 3 * h),
				IMAGE_WIDTH * 3);
		}
		myImage = myImage.scaled(IMAGE_WIDTH *0.8 , IMAGE_HEIGHT *0.8 );
		pixmap = pixmap.fromImage(myImage);
		ui.imageLbl->setPixmap(pixmap);
		delete[] buffer;
	}
	// 设置无数据区域 i 0-6 j 0-14 （0,0）（1,1）~（6,6）
	QPalette pe;
	pe.setColor(QPalette::WindowText, Qt::white);
	if (output.haveDataFlag)
	{
		
		ui.adTimeLbl->setText("raceTime");
		ui.adTimeLbl->setStyleSheet(QStringLiteral("background-color: Green;"));
		ui.adTimeLbl->setPalette(pe);
		ui.sessionLbl->setText(QString::number(Global::session));//更新全局场次号
		ui.raceTimeLbl->setText(QString::number(Global::raceTime));//更新全局比赛时间
		updateUiData(output, array);//更新马信息
		if (output.isQPL)
		{
			ui.stackedWidget->setCurrentIndex(0);
			updateQINQPLData(output, array);//更新QPL信息
		}
		else
		{
			ui.stackedWidget->setCurrentIndex(0);
			updateQINQPLData(output, array);//更新QIn信息
		}

			
	}
	else
	{
		ui.adTimeLbl->setText("ADTime");
		ui.adTimeLbl->setPalette(pe);
		ui.adTimeLbl->setStyleSheet(QStringLiteral("background-color: rgb(255, 130, 80);"));
	}
		
	

}

void OcrControl::updateUiData(DataOutput& output, QByteArray& array)
{
	//更新马信息
	for (int i = 0; i < indexLabelList.size(); i++)
	{
		indexLabelList[i]->setText(QString::number(i));
	}
	for (int i = 0; i < horseNameEditList.size(); i++)
	{
		
		horseNameEditList[i]->setText(QString("马名%1").arg(i));
	}
	for (int i = 0; i < winLableList.size(); i++)
	{

		winLableList[i]->setText(QString::number(output.WIN[i]));
	}
	for (int i = 0; i < plaLableList.size(); i++)
	{

		plaLableList[i]->setText(QString::number(output.PLA[i]));
	}
}

/**
* @brief 更新qin
*/
void OcrControl::updateQINQPLData(DataOutput& output, QByteArray& array)
{
	// 设置无数据区域 i 0-6 j 0-14 （0,0）（1,1）~（6,6）
	QPalette pe;
	pe.setColor(QPalette::WindowText, Qt::red);

	ui.QINLabel->setPalette(pe);
	if (output.isQPL)
	{
		ui.QINLabel->setText("QPL");
	}
	else
	{
		ui.QINLabel->setText("QIN");
	}
	
	for (int i = 0; i < qinList.size(); i++)
	{
		QList<QLabel*> list = qinList.at(i);
		for (int j = 0; j <  list.size(); j++)
		{
			QLabel * label = list.at(j);
			label->setText(QString::number(output.QPL_QIN[i][j]));
		}
	}
	// 设置无数据区域 i 0-6 j 0-14 （0,0）（1,1）~（6,6）
	 
	pe.setColor(QPalette::WindowText, Qt::white);
	  
	for (int i = 0; i < qinList.size(); i++)
	{
		QList<QLabel*> list = qinList.at(i);
		QLabel * label = list.at(i);
		label->setText(QString::number(i+8));
		label->setPalette(pe);
	}

	// 设置无数据区域 i 0-6 j 0-14 （0,1）（1,2）~（6,7）
	for (int i = 0; i < qinList.size(); i++)
	{
		QList<QLabel*> list = qinList.at(i);
		QLabel * label = list.at(i+1);
		label->setText(QString::number(i+1));
		label->setPalette(pe);
	}


}


void OcrControl::reConnect()
{
	qDebug("识别端：重连服务器 \n");
	emit connect("58.67.161.109", 9068) ;

}