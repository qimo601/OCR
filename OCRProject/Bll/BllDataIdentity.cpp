#include "BllDataIdentity.h"
#include <QDebug>
#include "Include/HorseDataStruct.h"
#include <QDir>
BllDataIdentity::BllDataIdentity(QObject *parent)
	: QObject(parent)
{
	stopIdentityTag = false;//初始化
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
* @brief 判断数据是否为新数据
*/
LONG BllDataIdentity::isDataOutputNew(DataOutput &outputStruct)
{

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
			//imshow("a",mat_temp);
			//waitKey(1000);

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

			emit readyReadBmp(emptyDataOutput, byteArray);
			//QString curPath = QDir::currentPath();
			QDir::setCurrent(QString("./acqImages/"));

			//curPath = QDir::currentPath();
#ifndef OFFLINE_DEBUG
			myImage.save(bmpFileName);
#endif // !OFFLINE_DEBUG

		
			//qDebug("curPath = %s \n", qPrintable(curPath));

			//退到上一层目录
			QDir::setCurrent("../");
		
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

					Global::session = outputStruct.session;//更新全局场次号
					Global::raceTime = outputStruct.raceTime;//更新全局比赛时间
					
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