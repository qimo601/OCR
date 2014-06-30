#include "testacqdriver.h"

testAcqDriver::testAcqDriver(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	myIAcq = new IAcq;

	myImage = QImage(640, 480, QImage::Format_RGB888); 
}

testAcqDriver::~testAcqDriver()
{

	myIAcq->unLoadDevice();
	delete myIAcq;
}


void testAcqDriver::on_initBtn_clicked()
{
	//初始化
	myIAcq->init();
	
	

}

void testAcqDriver::on_startCapBtn_clicked()
{
	char *buffer;
	buffer = new char[1000*1000]; 
	//ZeroMemory(buffer);
	*buffer = 0xdeadbf ;
	*(buffer + 1000 * 1000 - 3 ) = 0xdeadbf ;
	LONG size;
	// 打开设备进行截取图像数据
	myIAcq->read();
 }
void testAcqDriver::on_releaseBtn_clicked()
{
	myIAcq->unLoadDevice();
}

void testAcqDriver::on_readDataBtn_clicked()
{
	BYTE * buffer;
	buffer = new BYTE[640 * 480 * 3];
	
	//读取环形缓冲区:示波器一个数据包大小 640*480 *3 
	if (myIAcq->myAcqDriver->getCcbUsedSize() >= 640 * 480 * 3)
	{
		myIAcq->myAcqDriver->ccbRead((char *)buffer, 640 * 480 * 3);
		
		// 转换RGB888 到QIMAGE
		for (int h = 0; h < myIAcq->myAcqDriver->cpVideoInfo->dwHeight; h++) {
			// scanLine returns a ptr to the start of the data for that row 
			memcpy(myImage.scanLine(h), (buffer + myIAcq->myAcqDriver->cpVideoInfo->dwWidth * 3 * h),
				myIAcq->myAcqDriver->cpVideoInfo->dwWidth * 3);
		}

		pixmap = pixmap.fromImage(myImage);

		ui.imageLabel->setPixmap(pixmap);


	}


	
}
