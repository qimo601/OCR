#include <QtWidgets/QApplication>
#include "Include/Global.h"
#include "Ui/OcrControl.h"
//#include "Include/HorseDataStruct.h"
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//Mat img = imread("pp.jpg");
	//if (img.empty())
	//{
	//	cout << "error";
	//	return -1;
	//}
	//imshow("pp的靓照", img);
	//waitKey();



	Global global;
	global.init();

	OcrControl w;
	w.show();
	return a.exec();
}
