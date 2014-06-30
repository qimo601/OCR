#include "ocrproject.h"
#include <string>
OCRProject::OCRProject(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	serverIp = "58.67.161.109";
	serverPort = 9068;
	 
	memset(&clientProtocolMsg, 0,sizeof(PROTOCOLMSG));
	
	
}

OCRProject::~OCRProject()
{

}


void OCRProject::on_connectHostBtn_clicked()
{
	
	qDebug("conncectHostBtn clicked");
	 

	Global::mcsNetClient->initClient();
	//Global::mcsNetClient->initServer();
	Global::mcsNetClient->setRemoteHostIp(serverIp);
	Global::mcsNetClient->setRemoteHostPort(serverPort) ;

	Global::mcsNetClient->connectToHost(serverIp, serverPort);



}
void  OCRProject::on_disconnectBtn_clicked()
{
	qDebug("on_disconnectBtn_clicked clicked");
	if (Global::mcsNetClient->isConnectedToServer())
	{
		qDebug(" \n Status: Connected to server \n ");
	}
	else
	{
		qDebug("\n Status : Not Connected to server \n");
	}
}
void OCRProject::on_sendDataBtn_clicked()
{
	qDebug("on_sendDataBtn_clicked clicked");

	char checkStr[5];
		
	clientProtocolMsg.MsgID = IDENTIFY_LOGIN_MSG ;
	clientProtocolMsg.nDataSize = 0;
	strcpy(clientProtocolMsg.Check,"RDBS");
	strcpy(clientProtocolMsg.Param, "");
	
	sendHosrseData(clientProtocolMsg.Check, sizeof(PROTOCOLMSG));

}

void OCRProject::sendHosrseData(char * buffer, int length)
{
	qDebug("Enter sendHorseData Function ");
	BOOL rtValue = TRUE ;
	QByteArray sendDataArray( buffer);

	Global::mcsNetClient->sendData(sendDataArray, rtValue);
	if (rtValue == FALSE)
		qDebug(" data send error ");
	else
		qDebug("data send success ");

}