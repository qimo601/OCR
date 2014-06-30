#include <QString>
# include "opencv2/opencv.hpp"
# include "opencv/cv.h"
# include "opencv/cvaux.h"
# include "opencv/highgui.h"
# include "opencv/ml.h"
//#include "svm.h"
#include "./Include/HorseDataStruct.h"
# include "./Bll/algorithmParam.h"

using namespace cv;

struct HorseInfo
{
	int horseNum;						// the total number of horses in the image
	int* horseID;						// the horse ID
	QString* horseName;
};


struct ImageInfo_1
{
	int deltaX, deltaY;					// the x-shift and y-shift of image region 1 relative to the image origin
	int shiftX, shiftY;
	int height, width[3];
	CvRect rect[HORSENUMBER][3];						// the characters regions
};

struct ImageInfo_2
{
	int deltaX, deltaY;					// the x-shift and y-shift of image region 2 relative to the image origin
	CvRect rect[QIN_QPL_ROW][QIN_QPL_COL];
	CvRect QPL_QINRect;
};

struct ImageInfo_3
{
	int deltaX, deltaY;
	CvRect rect[2];
};


class DataIdentity
{
public:
	DataIdentity();
	~DataIdentity();

	// 对外的接口参数
	HorseInfo horseInfo;
	DataOutput dataOutput;

	int isProcessed;																// -1 processed,but no data, 0 processing, 1 processed
	bool isHistoryVideo;															// true: history video, false: live video 
	bool haveDataFlag;																// identify the frame has data or not
	bool isQPL;
	int horseNum;																	// the horse total number from video


	bool read(uchar* data, int length, int height = 480, int width = 640);			// return the error type, if all right, then return 0
	void haveData();

	int Identity();																// the core algorithm(0--normal,1--the frame has no data)
	int output(HorseInfo* info);
	void isReady();												//return the error type, if all right, then return 0

	void originPosition(/*void* imageData, int x, int y*/);							// return the position of the image origin

	void setRect1_history();
	void setRect2_history();
	void setRect3_history();

	void setRect1_live();
	void setRect2_live();
	void setRect3_live();

private:

	Mat image;																		// current original image
	int dataLength;																	// the original data length	
	int imageHeight, imageWidth;
	int originX, originY;															// the position of the image origin;

	ImageInfo_1 imageInfo1;
	ImageInfo_2 imageInfo2;
	ImageInfo_3 imageInfo3;



	HOGDescriptor hog;
	Size winStride;
	Size padding;
	vector<float> descriptorVector;
	Mat hogMat;

	SVM numSVM;
	SVM LNSVM;
	SVM nameSVM;

	// true:QPL, false:QIN


	// ===============================
	// history video

	void getHorseName_history();
	bool identifyDot_history(int i, Mat* edge);										// identify dot for region 1 and region 2 (QPL), i = 1, region 1, i = 2, region 2(QPL)
	int  identifyDot_QIN_history(Mat* edge);										// identify dot for region 2(QIN),  int i = 1, first identify, i = 2, identify again
	// return 0-- two number with dot,  1-- two number without dot, 2-- three number									  

	int identifyPeak_history(Mat* edge);											// difficult to identify a number whether contain a dot, this function is designed to 
	// identify a dot when identifyDOt_QIN return 0

	bool judgeQPL_QIN_history();													// return 0: QPL, 1: QIN
	void getImageInfo1_history();													// get the image region information(except horse name)
	void getImageInfo2_QPL_history();
	void getImageInfo2_QIN_history();
	void getSession_history();
	void getMinute_history();
	void getHorseNum_history();


	// ===============================
	// live video
	void getHorseName_live();
	bool identifyImageInfo1_Dot_live(int i, Mat* edge);							// identify dot for region 1 and region 2 (QPL), i = 1, region 1, i = 2, region 2(QPL)
	int  identifyImageInfor2_Dot_live(Mat* edge);								// identify dot for region 2(QIN),  int i = 1, first identify, i = 2, identify again
	// return 0-- two number with dot,  1-- two number without dot, 2-- three number									  

	int identifyPeak_live(Mat* edge);											// difficult to identify a number whether contain a dot, this function is designed to 
	// identify a dot when identifyDOt_QIN return 0

	void judgeQPL_QIN_live();													// return 0: QPL, 1: QIN
	void getImageInfo1_live();													// get the image region information(except horse name)
	void getImageInfo2_live();

	void getSession_live();
	void getMinute_live();
	void getHorseNum_live();




};

