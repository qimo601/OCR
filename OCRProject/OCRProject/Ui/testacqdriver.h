#ifndef TESTACQDRIVER_H
#define TESTACQDRIVER_H

#include <QtWidgets/QMainWindow>
#include "ui_testacqdriver.h"
#include "Acq/AcqDriver.h"
#include "Acq/iacq.h"

class testAcqDriver : public QMainWindow
{
	Q_OBJECT

public:
	testAcqDriver(QWidget *parent = 0);
	~testAcqDriver();
	QImage myImage;
	
	QPixmap pixmap;
	IAcq * myIAcq  ;
private slots:
void on_initBtn_clicked();
void on_startCapBtn_clicked();
void on_releaseBtn_clicked();
void on_readDataBtn_clicked();

private:
	Ui::testAcqDriverClass ui;
	
};

#endif // TESTACQDRIVER_H
