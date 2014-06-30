#include "BllRealTimeTrans.h"
#include "Include/HorseDataStruct.h"
#include "qmath.h"
#include "math.h"
BllRealTimeTrans::BllRealTimeTrans(QObject *parent)
	: QObject(parent)
{
	//正常接收到服务端回复
	//connect(Global::mcsNetClient, SIGNAL(clientReceiveDataSignal(QByteArray, int)), this, SLOT(handleReceiveData(QByteArray, int)));
	//客户端连接上服务端
	connect(Global::mcsNetClient, SIGNAL(connectToHostSuccessSignal()), this, SLOT(handleConnect()));
	//客户端断开了服务端
	connect(Global::mcsNetClient, SIGNAL(disConnectToHostSuccessSignal()), this, SLOT(handleDisConnect()));
}

BllRealTimeTrans::~BllRealTimeTrans()
{

}
/**
* @brief 连接服务器
*/
void BllRealTimeTrans::connectToHost(QString serverIp,qint32 serverPort)
{
	Global::client_cmd_status = ClientCmdStatus::connect_status;
	Global::mcsNetClient->connectToHost(serverIp, serverPort);

}
/**
* @brief 断开服务器
*/
void BllRealTimeTrans::disconnectToHost()
{
	Global::client_cmd_status = ClientCmdStatus::disconnect_status;
	Global::mcsNetClient->disConnectToHost();
}
/**
* @brief 识别端登录请求指令
*/
void BllRealTimeTrans::clientLogin()
{

	TagProtocolMsg msg;
	msg.MsgID = 4;
	msg.nDataSize = 0;
	strcpy(msg.Param, "Username\n Password");
	strcpy(msg.Check, "RDBS");

	QByteArray byteArray;
	int m = sizeof(TagProtocolMsg);
	byteArray.append((char*)&msg, sizeof(TagProtocolMsg));

	//测试结构体
	TagProtocolMsg msg1;
	memcpy(&msg1, byteArray.data(), sizeof(TagProtocolMsg));

	Global::client_cmd_status = ClientCmdStatus::login_status;
	Global::mcsNetClient->sendData(byteArray,false);//发送数据，且不需要关闭socket
	emit statuChanged("识别端：正常，尝试登录中...");
	bool success = Global::mcsNetClient->waitForReadyRead(3000);//阻塞等待
	if (success)
	{
		QByteArray result;
		int descriptor;
		Global::mcsNetClient->readAllMessage(result, descriptor);//读取数据
		handleLogin(result, descriptor);//处理login返回数据
	}
	else
		emit statuChanged("识别端：错误，登陆失败。");
}
/**
* @brief 识别端处理服务端返回的数据
*/
void BllRealTimeTrans::handleLogin(QByteArray result, int descriptor)
{
	/**************/
	/*1. 识别端登录请求指令
	例：第1步发送获取赛程表的指令： PROTOCOLMSG msg;
	msg.MsgID = 4;
	msg.nDataSize = 0;
	msg.Param = "Username\n Password";
	msg.Check = "RDBS";
	第2步收到服务端回应信息：OK(验证通过)	NO(验证失败)
	第3步根据返回结果继续下一步操作*/
	/**************/

	QString reply;
	reply = result.data();
	emit statuChanged(QString("识别端：正常，服务端回复登陆，%1").arg(reply));
}
/**
* @brief 识别端请求马信息表指令
*/
void BllRealTimeTrans::requestHorse()
{
	
	TagProtocolMsg msg;
	msg.MsgID = 5;
	msg.nDataSize = 0;
	strcpy(msg.Param, "");
	strcpy(msg.Check, "RDBS");

	QByteArray byteArray;
	int m = sizeof(TagProtocolMsg);
	byteArray.append((char*)&msg, sizeof(TagProtocolMsg));
	//测试结构体
	TagProtocolMsg msg1;
	memcpy(&msg1, byteArray.data(), sizeof(TagProtocolMsg));

	Global::client_cmd_status = ClientCmdStatus::request_horse_status;
	Global::mcsNetClient->sendData(byteArray, false);//发送数据，且不需要关闭socket



	bool success = Global::mcsNetClient->waitForReadyRead(3000);//阻塞等待
	if (success)
	{
		QByteArray result;
		int descriptor;
		Global::mcsNetClient->readAllMessage(result, descriptor);//读取数据
		handleRequestHorse(result, descriptor);//处理login返回数据
	}
	else
		emit statuChanged("识别端：错误,请求马信息表指令失败。");
}
/**
* @brief 识别端处理服务端-请求马信息表指令
*/
void BllRealTimeTrans::handleRequestHorse(QByteArray result, int descriptor)
{
	/**************/
	/*2. 识别端请求马信息表指令
		例：第1步发送获取马信息表的指令： PROTOCOLMSG msg;
	msg.MsgID = 5;
	msg.nDataSize = 0;
	msg.Param = "";
	msg.Check = "RDBS";
	第2步收到服务端返回的数据大小：int(数据大小)
	第3步开始接收赛程表信息：N个HORSEINFO
	第4步验证信息完整性，如不完整跳至第1步继续*/
	/**************/

	
	//返回大小
	int horseNum = 12;
	qint32 size = horseNum * sizeof(TagHorseInfo);//初始化默认模拟数据

#if moni_test == 0
	//真正采集
	memcpy(&size, result.data(), sizeof(qint32));
	for (int i = 0; i < size / sizeof(TagHorseInfo); i++ //真正解析
	{
	TagHorseInfo horse;
	memcpy(&horse, result.data(), sizeof(TagHorseInfo));
	Global::horseInfoList.append(horse);
	}
#else
	//测试代码
	for (int i = 0; i < size / sizeof(TagHorseInfo); i++)//模拟马匹
	{
		TagHorseInfo horse;
		horse.HorseID = i;
		strcpy(horse.HorseName, QString("马%1").arg(i).toLocal8Bit().data());
		Global::horseInfoList.append(horse);
	}
#endif

	
	

	emit statuChanged(QString("服务端：回复，马信息，%1匹马").arg(size / sizeof(TagHorseInfo)));
}
/**
* @brief 识别端根据RaceNO(场次号)请求RaceID指令
*/
void BllRealTimeTrans::requestRaceID(qint32 raceNO)
{
	TagProtocolMsg msg;
	msg.MsgID = 6;
	msg.nDataSize = 1;// RaceNO
	strcpy(msg.Param, "");
	strcpy(msg.Check, "RDBS");

	QByteArray byteArray;
	int m = sizeof(TagProtocolMsg);
	byteArray.append((char*)&msg, sizeof(TagProtocolMsg));
	//测试结构体
	TagProtocolMsg msg1;
	memcpy(&msg1, byteArray.data(), sizeof(TagProtocolMsg));

	Global::client_cmd_status = ClientCmdStatus::request_race_id_status;
	Global::mcsNetClient->sendData(byteArray, false);//发送数据，且不需要关闭socket


	bool success = Global::mcsNetClient->waitForReadyRead(3000);//阻塞等待
	if (success)
	{
		QByteArray result;
		int descriptor;
		Global::mcsNetClient->readAllMessage(result, descriptor);//读取数据
		handleRequestRaceID(result, descriptor);//处理login返回数据
	}
	else
		emit statuChanged("识别端：错误，请求RaceID指令失败。");
}

/**
* @brief 识别端处理服务端-请求RaceID指令
*/
void BllRealTimeTrans::handleRequestRaceID(QByteArray result, int descriptor)
{
	/**************/
	/*3.识别端根据RaceNO(场次号)请求RaceID指令
		例：第1步发送请求RaceID指令：  PROTOCOLMSG msg;
		msg.MsgID = 6;
		msg.nDataSize = RaceNO;
		msg.Param = "";
		msg.Check = "RDBS";
		第2步接收数据： int(RaceID)*/
	/**************/

	//raceId
	qint32 raceId;
	memcpy(&raceId, result.data(), sizeof(qint32));
	Global::raceId = raceId;
	emit statuChanged(QString("服务端：回复，raceId，%1").arg(raceId));
}
/**
* @brief 识别端提交比赛时长指令
*/
void BllRealTimeTrans::submitRaceTime(qint32 raceTime)
{
	 
	TagProtocolMsg msg;
	msg.MsgID = 7;
	msg.nDataSize = 0;
	strcpy(msg.Param, "35");//比赛分钟数
	strcpy(msg.Check, "RDBS");

	QByteArray byteArray;
	int m = sizeof(TagProtocolMsg);
	byteArray.append((char*)&msg, sizeof(TagProtocolMsg));
	//测试结构体
	TagProtocolMsg msg1;
	memcpy(&msg1, byteArray.data(), sizeof(TagProtocolMsg));

	Global::client_cmd_status = ClientCmdStatus::submit_race_time_status;
	Global::mcsNetClient->sendData(byteArray, false);//发送数据，且不需要关闭socket



	bool success = Global::mcsNetClient->waitForReadyRead(3000);//阻塞等待
	if (success)
	{
		QByteArray result;
		int descriptor;
		Global::mcsNetClient->readAllMessage(result, descriptor);//读取数据
		handleSubmitRaceTime(result, descriptor);//处理login返回数据
	}
	else
		emit statuChanged("识别端：错误，提交比赛时长指令失败。");
}
/**
* @brief 识别端处理服务端-提交比赛时长指令
*/
void BllRealTimeTrans::handleSubmitRaceTime(QByteArray result, int descriptor)
{
	/**************/
	/*4.识别端提交比赛时长指令
		例：第1步发送提交比赛时长指令： PROTOCOLMSG msg;
	msg.MsgID = 7;
	msg.nDataSize = 0;
	msg.Param = "比赛分钟数";
	msg.Check = "RDBS";
	第2步接收回应： OK*/
	/**************/

	//回复OK
	QString reply = result.data();

	emit statuChanged(QString("服务端：回复，提交比赛时长指令，%1").arg(reply));

}

/**
* @brief 识别端发送提交实时数据指令
*/
void BllRealTimeTrans::submitRealData(DataOutput outputStruct)
{
	 
	 
	//提交实时WIN数据
	if (outputStruct.changeStatus == WIN_CHANGED)
	{
		submitWINOrPLA(outputStruct, "WIN");
	}
	else if (outputStruct.changeStatus == PLA_CHANGED)
	{
		submitWINOrPLA(outputStruct, "PLA");
	}
	else if (outputStruct.changeStatus == WIN_PLA_CHANGED)
	{
		submitWINOrPLA(outputStruct, "WIN");
		submitWINOrPLA(outputStruct, "PLA");
	}
	else if (outputStruct.changeStatus == QIN_QPL_CHANGED)
	{
		if (outputStruct.isQPL)
		{
			submitQINOrQPL(outputStruct, "QPL");
		}
		else
		{
			submitQINOrQPL(outputStruct, "QIN");

		}
	}
	else if (outputStruct.changeStatus == WIN_QIN_QPL_CHANGED)
	{
		submitWINOrPLA(outputStruct, "WIN");
		if (outputStruct.isQPL)
		{
			submitQINOrQPL(outputStruct, "QPL");
		}
		else
		{
			submitQINOrQPL(outputStruct, "QIN");

		}
	}
	else if (outputStruct.changeStatus == PLA_QIN_QPL_CHANGED)
	{
		submitWINOrPLA(outputStruct, "PLA");
		if (outputStruct.isQPL)
		{
			submitQINOrQPL(outputStruct, "QPL");
		}
		else
		{
			submitQINOrQPL(outputStruct, "QIN");

		}
	}
	else if (outputStruct.changeStatus == WIN_PLA_QIN_QPL_CHANGED)
	{
		submitWINOrPLA(outputStruct, "WIN");
		submitWINOrPLA(outputStruct, "PLA");
		if (outputStruct.isQPL)
		{
			submitQINOrQPL(outputStruct, "QPL");
		}
		else
		{
			submitQINOrQPL(outputStruct, "QIN");

		}

	}


}
/**
* @brief 提交实时数据-WIN或PLA
* @param ouputStruct：算法传递来的数据，type:传送类型默认win
*/
void BllRealTimeTrans::submitWINOrPLA(DataOutput& ouputStruct,QString type)
{
	TagProtocolMsg msg;
	msg.MsgID = 8;
	msg.nDataSize = REALHORSENUM *sizeof(TagWPDataInfo);// N个WPDATAINFO或QDATAINFO结构数据，按马编号
	if (type == "WIN")
		strcpy(msg.Param, "WIN");//"WIN(或PLA或QIN或QPL)";
	else if (type == "PLA")
		strcpy(msg.Param, "PLA");//"WIN(或PLA或QIN或QPL)";
	strcpy(msg.Check, "RDBS");
	

	QByteArray byteArray;
	int m = sizeof(TagProtocolMsg);
	byteArray.append((char*)&msg, sizeof(TagProtocolMsg));

	Global::client_cmd_status = ClientCmdStatus::submit_real_data_status;
	Global::mcsNetClient->sendData(byteArray, false);//发送数据，且不需要关闭socket


	//稍微需要处理一下循环发送数据//
	bool success = Global::mcsNetClient->waitForReadyRead(3000);//阻塞等待
	if (success)
	{
		QByteArray result;
		int descriptor;//引用
		Global::mcsNetClient->readAllMessage(result, descriptor);//读取数据

		QString reply = result.data();
		emit statuChanged(QString("服务端：回复，提交实时数据指令，%1").arg(reply));
		if (reply == "OK")//提交WIN
		{
			//*************还得发送数据：WIN(或PLA或QIN或QPL)*********//
			QByteArray sendBlock;
		
			for (int i = 1; i <= ouputStruct.horseNum; /* HORSENUMBER_1; */i++)
			{
				//封装一个WIN
				TagWPDataInfo WPData;
				WPData.HorseID = i;
				WPData.HorseNO = i;
				int dataBigger10 = 0;
				float dataSmaller10 = 0;
				float dataTemp = 0;
				if (type == "WIN")
				{
					dataTemp  = ouputStruct.WIN[i - 1] /10;
					if (dataTemp >= 10)
						WPData.WinValue = (int)dataTemp;
					else
					{
						dataBigger10 = (int)ouputStruct.WIN[i - 1];

						WPData.WinValue = dataBigger10 / 10.0;
					}
						
					 
				}
					
				else if (type == "PLA")
				{
					dataTemp = ouputStruct.PLA[i - 1] / 10;
					if (dataTemp >= 10)
						WPData.WinValue = (int)dataTemp;
					else
					{
						dataBigger10 = (int)ouputStruct.PLA[i - 1];

						WPData.WinValue = dataBigger10 / 10.0;
					}


				} 
				WPData.RaceID = Global::raceId;
				WPData.AtTime = 1;

				sendBlock.append((char*)&WPData, sizeof(TagWPDataInfo));
			}
			//****************************************************//
			Global::mcsNetClient->sendData(sendBlock, false);//发送数据，且不需要关闭socket
			emit statuChanged(QString("服务端：回复，提交实时数据-%1").arg(type));


			//**若对方有回复****//
			//bool success = Global::mcsNetClient->waitForReadyRead(3000);//阻塞等待
			//if (success)
			//{
			//	QByteArray result;
			//	Global::mcsNetClient->readAllMessage(result, descriptor);//读取数据

			//	QString reply = result.data();
			//	emit statuChanged(QString("服务端：回复，提交实时数据-%1，%2").arg(type).arg(reply));
			//}
			//else
			//{
			//	emit statuChanged(QString("服务端：错误，提交实时数据--%1，%2，14个.").arg(type).arg(reply));
			//}
			//**若对方有回复****//
		}

	}
	else
		emit statuChanged("识别端：错误，提交实时数据指令失败.");
}

/**
* @brief 提交实时数据-QIN或QPL
* @param ouputStruct：算法传递来的数据，type:传送类型默认win
*/
void BllRealTimeTrans::submitQINOrQPL(DataOutput& ouputStruct, QString type)
{
	TagProtocolMsg msg;
	msg.MsgID = 8;
	
	msg.nDataSize = (ouputStruct.horseNum - 1)*ouputStruct.horseNum   * sizeof(TagQDataInfo);// N个WPDATAINFO或QDATAINFO结构数据，按马编号
	if (type == "QIN")
		strcpy(msg.Param, "QIN");//"WIN(或PLA或QIN或QPL)";
	else if (type == "QPL")
		strcpy(msg.Param, "QPL");//"WIN(或PLA或QIN或QPL)";
	strcpy(msg.Check, "RDBS");


	QByteArray byteArray;
	int m = sizeof(TagProtocolMsg);
	byteArray.append((char*)&msg, sizeof(TagProtocolMsg));

	Global::client_cmd_status = ClientCmdStatus::submit_real_data_status;
	Global::mcsNetClient->sendData(byteArray, false);//发送数据，且不需要关闭socket


	//**稍微需要处理一下循环发送数据****//
	bool success = Global::mcsNetClient->waitForReadyRead(3000);//阻塞等待
	if (success)
	{
		QByteArray result;
		int descriptor;
		Global::mcsNetClient->readAllMessage(result, descriptor);//读取数据

		QString reply = result.data();
		emit statuChanged(QString("服务端：回复，提交实时数据指令-%1,%2").arg(type).arg(reply));
		if (reply == "OK")//提交QIN
		{
			//*************还得发送数据：WIN(或PLA或QIN或QPL)*********//
			QByteArray sendBlock;
			//每一列

			for (int i = 1; i <= ouputStruct.horseNum; /* HORSENUMBER_1; */ i++)
			{
				for (int j = i + 1; j <= ouputStruct.horseNum; /* HORSENUMBER_1; */ j++)
				{
					
					//封装一个WIN
					TagQDataInfo QDataInfo;
					QDataInfo.RaceID = Global::raceId;//所属赛事ID
					QDataInfo.HorseID = i;//马的唯一编号可关联马信息表
					QDataInfo.HorseNO = i;//本场比赛中马的序号，比如第3号，1-13
					QDataInfo.YNO = j;//在Y轴上的第几号，跟它组合得出的数据 2-14
					QDataInfo.AtTime = 1;
					if (i <=  7) // 正表
					{
						if (type == "QIN")//数据值，由XNO与YNO组合得出 QPL+QIN[7][15]
							QDataInfo.QinValue = ouputStruct.QPL_QIN[i - 1][j];
						else if (type == "QPL")
							QDataInfo.QinValue = ouputStruct.QPL_QIN[i - 1][j];
					}
					else //补充图表
					{
						if (type == "QIN")//数据值，由XNO与YNO组合得出 QPL+QIN[7][15]
							QDataInfo.QinValue = ouputStruct.QPL_QIN[j-8][i-8];
						else if (type == "QPL")
							QDataInfo.QinValue = ouputStruct.QPL_QIN[j-8][i-8];
					}


					//发送
					sendBlock.append((char*)&QDataInfo, sizeof(TagQDataInfo));
				}
			}


			// 发送另外一半数据
			for (int i = 1; i <= ouputStruct.horseNum; /* HORSENUMBER_1; */ i++)
			{
				for (int j = i + 1; j <= ouputStruct.horseNum; /* HORSENUMBER_1; */ j++)
				{

					//封装一个WIN
					TagQDataInfo QDataInfo;
					QDataInfo.RaceID = Global::raceId;//所属赛事ID
					QDataInfo.HorseID = i;//马的唯一编号可关联马信息表
					QDataInfo.HorseNO = j;//本场比赛中马的序号，比如第3号，1-13
					QDataInfo.YNO = i;//在Y轴上的第几号，跟它组合得出的数据 2-14
					QDataInfo.AtTime = 1;
					if (i <= 7) // 正表
					{
						if (type == "QIN")//数据值，由XNO与YNO组合得出 QPL+QIN[7][15]
							QDataInfo.QinValue = ouputStruct.QPL_QIN[i - 1][j];
						else if (type == "QPL")
							QDataInfo.QinValue = ouputStruct.QPL_QIN[i - 1][j];
					}
					else //补充图表
					{
						if (type == "QIN")//数据值，由XNO与YNO组合得出 QPL+QIN[7][15]
							QDataInfo.QinValue = ouputStruct.QPL_QIN[j - 8][i - 8];
						else if (type == "QPL")
							QDataInfo.QinValue = ouputStruct.QPL_QIN[j - 8][i - 8];
					}


					//发送
					sendBlock.append((char*)&QDataInfo, sizeof(TagQDataInfo));
				}
			}

			/*
			for (int i = 0; i < QIN_QPL_ROW_1; i++)
			{
				for (int j = 0; j < QIN_QPL_COL_1; j++)
				{
					
					//封装一个WIN
					TagQDataInfo QDataInfo;
					QDataInfo.RaceID = Global::raceId;//所属赛事ID
					QDataInfo.HorseID = i;//马的唯一编号可关联马信息表
					QDataInfo.HorseNO = i;//本场比赛中马的序号，比如第3号马
					if (type == "QIN")//数据值，由XNO与YNO组合得出
						QDataInfo.QinValue = ouputStruct.QPL_QIN[i][j];
					else if (type == "QPL")
						QDataInfo.QinValue = ouputStruct.QPL_QIN[i][j];
					QDataInfo.YNO = i;//在Y轴上的第几号，跟它组合得出的数据
					QDataInfo.AtTime = 1;

					sendBlock.append((char*)&QDataInfo, sizeof(TagQDataInfo));
				}
			}
			*/
			//****************************************************//
			Global::mcsNetClient->sendData(sendBlock, false);//发送数据，且不需要关闭socket
			emit statuChanged(QString("识别端：正常，提交实时数据-%1，14个.").arg(type));


			//**若对方有回复****//
			//bool success = Global::mcsNetClient->waitForReadyRead(3000);//阻塞等待
			//if (success)
			//{
			//	QByteArray result;
			//	Global::mcsNetClient->readAllMessage(result, descriptor);//读取数据

			//	QString reply = result.data();
			//	emit statuChanged(QString("服务端：回复，提交实时数据-%1，%2").arg(type).arg(reply));
			//}
			//else
			//{
			//	emit statuChanged(QString("服务端：错误，提交实时数据--%1，%2，14个.").arg(type).arg(reply));
			//}
			//**若对方有回复****//
		}

	}
	else
		emit statuChanged(QString("识别端：错误，提交实时数据指令-%1,失败.").arg(type));
}

/**
* @brief 识别端处理服务端-提交实时数据指令
*/
void BllRealTimeTrans::handleSubmitRealData(QByteArray result, int descriptor)
{
	/**************/
	/*5. 识别端发送提交实时数据指令
		例：第1步发送提交数据指令：  	 PROTOCOLMSG msg;
	msg.MsgID = 8;
	msg.nDataSize = N;
	msg.Param = "WIN(或PLA或QIN或QPL)";
	msg.Check = "RDBS";
	第2步接收回应：OK
		第3步开始发送数据： N(马数)个WPDATAINFO或QDATAINFO结构数据，按马编号						顺序排列
		第4步不断循环识别到新数据后再提交*/
	/**************/

	//回复OK
	QString reply = result.data();
	emit statuChanged(QString("服务端：回复，实时数据指令，%1").arg(reply));

	//*************还得发送数据：WIN(或PLA或QIN或QPL)*********//
	/*tagWPDataInfo或者tagQDataInfo*/
	//****************************************************//
	Global::mcsNetClient->sendData(result, false);//发送数据，且不需要关闭socket
}
/**
* @brief 识别端处理服务端返回的数据
*/
void BllRealTimeTrans::handleReceiveData(QByteArray result, int descriptor)
{
	switch (Global::client_cmd_status)
	{
	case no_status:
		break;
	case connect_status:
		break;
	case login_status:
		handleLogin(result, descriptor);
		break;
	case request_horse_status:
		handleRequestHorse(result, descriptor);
		break;
	case request_race_id_status:
		handleRequestRaceID(result, descriptor);
		break;
	case submit_race_time_status:
		handleSubmitRaceTime(result, descriptor);
		break;
	case submit_real_data_status:
		handleSubmitRealData(result, descriptor);
		break;
	default:
		break;
	}
}	
/**
* @brief 识别端处理服务端返回的数据
*/
void BllRealTimeTrans::handleConnect()
{
	emit statuChanged("识别端：正常，客户端连接上服务端，.");
}
/**
* @brief 识别端处理服务端返回的数据
*/
void BllRealTimeTrans::handleDisConnect()
{
	emit statuChanged("识别端:正常，客户端已断开连接。");
}

