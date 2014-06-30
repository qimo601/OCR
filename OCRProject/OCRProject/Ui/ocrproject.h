#ifndef OCRPROJECT_H
#define OCRPROJECT_H

#include <QtWidgets/QMainWindow>
#include "ui_ocrproject.h"
#include <windows.h>
#include "Include/HorseDataStruct.h"
#include "Include/Global.h"

#define IDENTIFY_LOGIN_MSG 4 
#define IDENTIFY_REQUEST_HORSEINFO 5
#define IDENTIFY_REQUEST_RACEID 6 
#define IDENTIFY_SEND_RACETIME 7 
#define IDENTIFY_SEND_REALTIMEDATA 8 




class OCRProject : public QMainWindow
{
	Q_OBJECT

public:
	OCRProject(QWidget *parent = 0);
	~OCRProject();

	QString serverIp ;
	qint32 serverPort  ;

	PROTOCOLMSG clientProtocolMsg ;

	void sendHosrseData(char * buffer, int length);

public slots:
void on_connectHostBtn_clicked();
void on_disconnectBtn_clicked();
void on_sendDataBtn_clicked();



private:
	Ui::OCRProjectClass ui;
};

#endif // OCRPROJECT_H
