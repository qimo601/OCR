#include "BllDataIdentity.h"
#include <QDebug>
#include "Include/HorseDataStruct.h"
BllDataIdentity::BllDataIdentity(QObject *parent)
	: QObject(parent)
{
	stopIdentityTag = false;//初始化
}

BllDataIdentity::~BllDataIdentity()
{

}
/**
* @brief 初始化算法
*/
void BllDataIdentity::init()
{
	//string str("C:\\Users\\ZhouZY\\Desktop\\OCR\\frame200.jpg");
	//Mat imageMat = imread(str);


	//uchar* data = (uchar*)imageMat.data;


	//int width = imageMat.cols;
	//int height = imageMat.rows;
	//int length = width * height * 3;

	//clock_t startTime = clock();

	//
	//dataIdentity.read(data, length, height, width);

	//if (true)													// need to get the position of origin			
	//	dataIdentity.originPosition();
	//if (true)
	//{
	//	dataIdentity.setRect1();								// need to get each rect of region 1, region 2 and region 3
	//	dataIdentity.setRect2();
	//	dataIdentity.setRect3();
	//}

	//dataIdentity.Identity();

	//clock_t lastingTime = clock() - startTime;
	//qDebug() << lastingTime << endl;
}

/**
* @brief 开始识别
*/
void BllDataIdentity::start()
{
	Global::stopIdentityTag = false;//开始跑
	int width = IMAGE_WIDTH;
	int height = IMAGE_HEIGHT;
	int length = width * height * 3;
	uchar* data = new uchar[length];
	while (!Global::stopIdentityTag  )
	{
		//初始化Mat
		//string str("D:\\VS2013WorkSpace\\OCRProject\\OCRProject\\1.jpg");
		//Mat imageMat = imread(str);
		//uchar* data = (uchar*)imageMat.data;

		
		
		if (Global::S_CCycleBuffer->getUsedSize() >= length)
		{
			Global::S_CCycleBuffer->read((char*)data, length);	


			//算法
			DataIdentity dataIdentity;
			dataIdentity.read(data, length, height, width);

			dataIdentity.isHistoryVideo = false;// live video or history video

			if (true)// need to get the position of origin			
				dataIdentity.originPosition();

			if (true)
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

			//算法识别
			dataIdentity.Identity();
 
			//注册该对象为元对象可识别系统，元对象将会将该参数保存起来，供队列连接调用。特别针对多线程
			qRegisterMetaType<DataOutput>("DataOutput");

			//获取算法数据
			DataOutput outputStruct = dataIdentity.dataOutput;
			//数据处理，屏蔽无效数据为-1
			int horseNum = 12;
			for (int i = 0; i < 7; i++)
			{
				for (int k = horseNum + 1; k < 15; k++)
					outputStruct.QPL_QIN[i][k] = -1;//无效
				outputStruct.QPL_QIN[i][i] = -1;
				outputStruct.QPL_QIN[i][i + 1] = -1;
				if (i == 5)
				{
					for (int k = 0; k < 6; k++)
						outputStruct.QPL_QIN[i][k] = -1;
				}
				if (i == 6)
				{
					for (int k = 0; k < 7; k++)
						outputStruct.QPL_QIN[i][k] = -1;
				}
			}

			QByteArray byteArray;
			byteArray.append((char *)data, length);
			emit readyRead(outputStruct, byteArray);
			qDebug() << "【BllDataIdentity】一帧图像识别时间：" << endl;
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