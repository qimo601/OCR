#include "BllDataIdentity.h"
#include <QDebug>
#include "Include/HorseDataStruct.h"
#include <QDir>
BllDataIdentity::BllDataIdentity(QObject *parent)
	: QObject(parent)
{
	stopIdentityTag = false;//初始化

	for (int i = 0; i < 30; i++)
		memset( myRaceTimeStruct, 0, sizeof(raceNumTimeStruct)*30);
	for (int i = 0; i < 20;i++)
		memset( myRaceNumberStruct, 0, sizeof(raceNumTimeStruct)*20);
	
	dataNewCount = 0 ;
#ifdef WRITE_IMAGES_BEFORE_IDENTITY
	bmpCount = 0;
#endif
}

BllDataIdentity::~BllDataIdentity()
{

}
/**
* @brief 初始化算法
*/
void BllDataIdentity::init()
{
 
}
/**
* @brief 从多次识别出的倒计时、场次号中选出正确的
*/
LONG BllDataIdentity::chooseRightRaceTimeRaceSession(DataOutput &outputStruct)
{
	//判定场次号 以及倒计时 
	if (dataNewCount <= 30)
	{
		if (dataNewCount == 0)
		{
			for (int i = 0; i < 20; i++)
			{
				myRaceNumberStruct[i].content = 0;
				myRaceNumberStruct[i].contentCount = 0;
			}

			for (int i = 0; i < 30; i++)
			{
				myRaceTimeStruct[i].content = 0;
				myRaceTimeStruct[i].contentCount = 0;
			}
		}
		else
		{
			myRaceNumberStruct[outputStruct.session].content = outputStruct.session;
			myRaceNumberStruct[outputStruct.session].contentCount++;

			myRaceTimeStruct[outputStruct.raceTime].content = outputStruct.raceTime;
			myRaceTimeStruct[outputStruct.raceTime].contentCount++;

		}
		dataNewCount++;
	}
	else
	{
		//最大内容出现计数次数
		int maxContentCount;
		int maxContent;
		maxContentCount = myRaceNumberStruct[0].contentCount;
		maxContent = myRaceNumberStruct[0].content;
		//判决输出
		for (int i = 0; i < 20; i++)
		{

			if (maxContentCount < myRaceNumberStruct[i].contentCount)
			{
				maxContentCount = myRaceNumberStruct[i].contentCount;
				maxContent = myRaceNumberStruct[i].content;
			}


		}

		Global::session = maxContent;


		//挑出来 应该输出的  倒计时时间 
		maxContentCount = myRaceTimeStruct[0].contentCount;
		maxContent = myRaceTimeStruct[0].content;
		for (int i = 0; i < 30; i++)
		{

			if (maxContentCount < myRaceTimeStruct[i].contentCount)
			{
				maxContentCount = myRaceTimeStruct[i].contentCount;
				maxContent = myRaceTimeStruct[i].content;
			}


		}
		dataNewCount = 0;
		Global::raceTime = maxContent;
		

	}

	 
	return 1;

}

/**
* @brief 判断数据是否为新数据
*/
LONG BllDataIdentity::handleDataOutput(DataOutput &outputStruct)
{
	//无数据区域设置为0 
	for (int i = outputStruct.horseNum; i < 14;i ++ )
	{
		outputStruct.WIN[i] = 0;
		outputStruct.PLA[i] = 0;
	}
	for (int i = outputStruct.horseNum - 7; i < 7;i++)
	{
		for (int j = 0; j < i; j++)
			outputStruct.QPL_QIN[i][j] = 0;

	}
	for (int i = 0; i < 7; i++)
	{
		for (int j = outputStruct.horseNum+1; j < 15; j++)
			outputStruct.QPL_QIN[i][j] = 0;
	}

	
	chooseRightRaceTimeRaceSession(outputStruct);

	return 1 ;
}

/**
* @brief 判断数据是否为新数据
*/
LONG BllDataIdentity::isDataOutputNew(DataOutput &outputStruct)
{

	handleDataOutput( outputStruct );
	// 判断WIN数据是否变化
	outputStruct.changeStatus = 0 ;
	for (int i = 0; i < outputStruct.horseNum; i++)
	{
		if (abs(outputStruct.WIN[i] - priDataOutput.WIN[i]) > 1 )
		{
			qDebug("WIN : i=%d , new is %f pri is %f ", i,  outputStruct.WIN[i], priDataOutput.WIN[i]);
			outputStruct.changeStatus = WIN_CHANGED;
			goto JUDGE_PLA ;
		}

	}
JUDGE_PLA:

	for (int i = 0; i < outputStruct.horseNum; i++)
	{

		if (abs(outputStruct.PLA[i] - priDataOutput.PLA[i]) > 1 )
		{
			qDebug("PLA:i=%d ,new is %f pri is %f ", i,  outputStruct.PLA[i], priDataOutput.PLA[i]);
			outputStruct.changeStatus = outputStruct.changeStatus | PLA_CHANGED;
			break;
		}
	}
	JUDGE_QIN_QPL :
	for (int i = 0; i < 7; i++)
	{

		for (int j = 0; j < outputStruct.horseNum; j++)
		{
			if (i == j || i == (j + 1))
				continue;
			if (abs(outputStruct.QPL_QIN[i][j] - priDataOutput.QPL_QIN[i][j]) > 0.05)
			{
				qDebug("QIN_QPL:i=%d ,j=%d new is %f pri is %f ", i, j, outputStruct.QPL_QIN[i][j], priDataOutput.QPL_QIN[i][j]);
				outputStruct.changeStatus = outputStruct.changeStatus | QIN_QPL_CHANGED;
				goto END;
			}
		}
	}
	END:
	priDataOutput = outputStruct;
	return 1;
}
/**
* @brief 开始识别
*/
void BllDataIdentity::start()
{
	Global::stopIdentityTag = false;//开始跑
	int width = IMAGE_WIDTH;
	int height = IMAGE_HEIGHT;
	 
	uchar* data = new uchar[IMAGE_BUFF_LENGTH];
	//注册该对象为元对象可识别系统，元对象将会将该参数保存起来，供队列连接调用。特别针对多线程
	qRegisterMetaType<DataOutput>("DataOutput");

	while (!Global::stopIdentityTag)
	{
	 		
		if (Global::S_CCycleBuffer->getUsedSize() >= IMAGE_BUFF_LENGTH)
		{
			Global::S_CCycleBuffer->read((char*)data, IMAGE_BUFF_LENGTH);

#ifdef WRITE_IMAGES_BEFORE_IDENTITY
			Mat mat_temp(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC3, data);
		//	imshow("a",mat_temp);
		//	waitKey(1000);

			bmpCount++;
			QPixmap pixmap;
			QImage myImage;
			myImage = QImage(IMAGE_WIDTH, IMAGE_HEIGHT, QImage::Format_RGB888);


			QString bmpFileName;
			bmpFileName = QString(".bmp");
			bmpFileName.prepend(QString::number(bmpCount%100));
			QByteArray byteArray;
			byteArray.append((char *)data, IMAGE_BUFF_LENGTH );

			DataOutput emptyDataOutput;
			
			// 转换RGB888 到QIMAGE
			for (int h = 0; h < IMAGE_HEIGHT; h++) {
				// scanLine returns a ptr to the start of the data for that row 
				memcpy(myImage.scanLine(h), (data + IMAGE_WIDTH * 3 * h),
					IMAGE_WIDTH * 3);
			}

			
			//QString curPath = QDir::currentPath();
			QDir::setCurrent(QString("./acqImages/"));
#ifndef OFFLINE_DEBUG
			myImage.save(bmpFileName);
#endif // !OFFLINE_DEBUG
			//退到上一层目录
			QDir::setCurrent("../");
			QString curPath = QDir::currentPath();
		//	qDebug("curPath = %s \n", qPrintable(curPath))
			//curPath = QDir::currentPath();


		
			//qDebug("curPath = %s \n", qPrintable(curPath));

		;
		
#endif
			//算法
			DataIdentity dataIdentity;
			bool emptyData = dataIdentity.read(myImage.bits(), (IMAGE_BUFF_LENGTH-BMP_HEADER), height, width);
			if (emptyData == true)								// empty == true, 无图像数据
			{
				//qDebug() << "empty image data" << endl;
				break;
			}
			
			dataIdentity.isHistoryVideo = false;// live video or history video
			dataIdentity.haveData();
			if (dataIdentity.haveDataFlag)
			{
				if (true)// need to get the position of origin			
					dataIdentity.originPosition();

				if (true)													//
				{
					if (dataIdentity.isHistoryVideo)
					{
						dataIdentity.setRect1_history();// need to get each rect of region 1, region 2 and region 3
						dataIdentity.setRect2_history();
						dataIdentity.setRect3_history();
					}
					else
					{
						dataIdentity.setRect1_live();// need to get each rect of region 1, region 2 and region 3
						dataIdentity.setRect2_live();
						dataIdentity.setRect3_live();
					}
				}


				if (dataIdentity.haveDataFlag == true)					// dataIdentity.haveDataFlag == false, 无实际数据（AD time）
				{
					dataIdentity.Identity();

					//获取算法数据
					DataOutput outputStruct = dataIdentity.dataOutput;
					//数据处理，屏蔽无效数据为-1

					//Global::session = outputStruct.session;//更新全局场次号
					//Global::raceTime = outputStruct.raceTime;//更新全局比赛时间
					
					isDataOutputNew( outputStruct);

					QByteArray byteArray;
					byteArray.append((char *)data, IMAGE_BUFF_LENGTH);
					//数据有改变才会发送信号
					if (outputStruct.changeStatus>=0)
					{
						emit readyRead(outputStruct, byteArray);
					}
					
					qDebug() << "【BllDataIdentity】一帧图像识别时间：" << endl;
				}
			}
			else
			{
				emit readyReadBmp(emptyDataOutput, byteArray);
			}
				

			
		}

		//else如果没有这个等待，就会有很多空循环，CPU会很高。
		//{
		//	Global::S_CCycleBuffer->waitNotEmpty();

		//}
		

	}

	delete[] data;
	qDebug() << "【BllDataIdentity】退出识别";

}

/**
* @brief 停止识别
*/
void BllDataIdentity::stop()
{
	Global::stopIdentityTag = true;
}