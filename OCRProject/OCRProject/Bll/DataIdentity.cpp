#include "DataIdentity.h"
//#include "algorithmParam.h"
using namespace std;



DataIdentity::DataIdentity()
{
	dataLength = 0;
	imageHeight = 0;
	imageWidth = 0;

	// initialize the HorseInfo
	horseInfo.horseNum = HORSENUMBER;
	horseInfo.horseID = new int[horseInfo.horseNum];
	horseInfo.horseName = new QString[horseInfo.horseNum];
	for (int i = 0; i < horseInfo.horseNum; i++)
	{
		horseInfo.horseID[i] = 0;
		horseInfo.horseName[i] = "";
	}

	// initialize the DataOutput
	dataOutput.session = 0;
	dataOutput.raceTime = 0;

	for (int i = 0; i < horseInfo.horseNum; i++)
	{
		dataOutput.svmResult[i] = -1;
		dataOutput.WIN[i] = 0.0;
		dataOutput.PLA[i] = 0.0;
	}
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 12; j++)
			dataOutput.QPL_QIN[i][j] = 0;
	}

	// initialize the image region 1
	imageInfo1.deltaX = HISTORY_IMAGEINFO1_DELTAX;								// the relative shift of the first vertex to the origin
	imageInfo1.deltaY = HISTORY_IMAGEINFO1_DELTAY;
	imageInfo1.height = HISTORY_IMAGEINFO1_HEIGHT;								// the region height
	imageInfo1.width[0] = HISTORY_IMAGEINFO1_WIDTH1;							// the region width
	imageInfo1.width[1] = HISTORY_IMAGEINFO1_WIDTH2;
	imageInfo1.width[2] = HISTORY_IMAGEINFO1_WIDTH2;

	for (int i = 0; i < horseInfo.horseNum; i++)
	{
		for (int j = 0; j < 3; j++)
			imageInfo1.rect[i][j] = cvRect(0, 0, 0, 0);
	}

	// initialize the image region 2
	imageInfo2.deltaX = 0;
	imageInfo2.deltaY = 0;
	for (int i = 0; i < QIN_QPL_ROW; i++)
	{
		for (int j = 0; j < QIN_QPL_COL; j++)
			imageInfo2.rect[i][j] = cvRect(0, 0, 0, 0);
	}

	// initialize the image region 3
	imageInfo3.deltaX = 0;
	imageInfo3.deltaY = 0;
	for (int i = 0; i < 2; i++)
		imageInfo3.rect[i] = cvRect(0, 0, 0, 0);

	//initialize the HOG feature vector
	hog.winSize = Size(10, 20);
	hog.blockSize = Size(10, 10);
	hog.blockStride = Size(5, 5);
	hog.cellSize = Size(5, 5);
	hog.nbins = 9;
	winStride = Size(1, 1);
	padding = Size(0, 0);
	float vectorSize = hog.getDescriptorSize();
	vector<float> descriptorVector(vectorSize);
	Mat HOG(1, 108, CV_32FC1, Scalar(0));
	this->descriptorVector = descriptorVector;
	this->hogMat = HOG;

	// initialize the svm
	// 	numSVM.load("C:\\Users\\ZhouZY\\Desktop\\number_SVM_1.xlm");
	// 	LNSVM.load("C:\\Users\\ZhouZY\\Desktop\\LN_SVM_1.xlm");
	numSVM.load("number_SVM_1.xlm");
	LNSVM.load("LN_SVM_1.xlm");

}

DataIdentity::~DataIdentity()
{

}

// ===========================================================
// public function 
// ===========================================================
bool DataIdentity::read(uchar* data, int length, int height, int width)
{
	Mat image_temp(height, width, CV_8UC3, data);
	bool emptyFlag = image_temp.empty();
	if (emptyFlag)
		return emptyFlag;
	else
	{
		image = image_temp;
		dataLength = length;
		imageHeight = height;
		imageWidth = width;

		//cvtColor(image, image, CV_RGB2BGR);

		return emptyFlag;
	}
}


int DataIdentity::output(HorseInfo* info)
{
	return 1;
}

int DataIdentity::Identity()
{
	haveData();
	if (haveDataFlag == false)						// the frame has not any data, return 1
		return 1;

	if (isHistoryVideo)
	{
		getImageInfo1_history();

		isQPL = judgeQPL_QIN_history();
		if (isQPL)
			getImageInfo2_QPL_history();
		else
			getImageInfo2_QIN_history();

		getMinute_history();
		getSession_history();
	}
	else
	{
		getImageInfo1_live();

		isQPL = judgeQPL_QIN_live();
		getImageInfo2_live();

		getSession_live();
		getMinute_live();
	}

	isReady();
	return 0;
}

void  DataIdentity::isReady()
{
	isProcessed = true;
}


// ===========================================================
// private function
// ===========================================================

// identify the current frame has or not has any data
void DataIdentity::haveData()
{
	uchar bluePixel[HAVEDATA_PIXELNUMBER];
	uchar greenPixel[HAVEDATA_PIXELNUMBER];
	uchar blueMean = 0, greenMean = 0;

	for (int i = 0; i < HAVEDATA_PIXELNUMBER; i++)
	{
		Vec3b bgr = image.at<Vec3b>(HAVEDATA_YINDEX * (i + 1), HAVEDATA_XINDEX);							// identify the blue and green channel of the pixels( x:30, y:40*i ) 
		bluePixel[i] = bgr[0];
		greenPixel[i] = bgr[1];
		blueMean += bluePixel[i] / HAVEDATA_PIXELNUMBER;
		greenMean += greenPixel[i] / HAVEDATA_PIXELNUMBER;
	}

	if (blueMean >= HAVEDATA_BLUETHRESHOLD && greenMean < HAVEDATA_GREENTHRESHOLD)										// 
		haveDataFlag = true;
	else
		haveDataFlag = false;
}


// get the origin position
// return the coodinate of the origin
void DataIdentity::originPosition()
{
	int regionWidth = ORIGINPOSITION_REGIONWIDTH, regionHeight = ORIGINPOSITION_REGIONHEIGHT;
	// 
	// 	imshow("a",image);
	// 	waitKey();

	Mat region(image, Rect(0, 0, regionWidth, regionHeight));
	Mat regionGray(regionHeight, regionWidth, CV_8UC1, Scalar::all(0));

	cvtColor(image, regionGray, CV_BGR2GRAY);

	//	imshow("a", regionGray);

	int* colSum = new int[regionHeight];
	int* rowSum = new int[regionWidth];

	// calculate the row sum
	for (int i = 0; i < regionHeight; i++)
	{
		rowSum[i] = 0;
		for (int j = 0; j < regionWidth; j++)
			rowSum[i] += regionGray.at<uchar>(i, j);

		rowSum[i] = rowSum[i] / regionWidth;
	}
	//	qDebug() << endl;

	// calculate the col sum
	for (int i = 0; i < regionWidth; i++)
	{
		colSum[i] = 0;
		for (int j = 0; j < regionHeight; j++)
			colSum[i] += regionGray.at<uchar>(j, i);

		colSum[i] = colSum[i] / regionHeight;
	}

	// identify the originX
	for (int i = 0; i < regionWidth; i++)
	{
		if (colSum[i]>ORIGINPOSITION_COLSUM_THRESHOLD)
		{
			originX = i - 1;
			break;
		}
	}
	// identify the originY
	for (int i = 0; i < regionHeight; i++)
	{
		if (rowSum[i]>ORIGINPOSITION_ROWSUM_THRESHOLD)
		{
			originY = i - 1;
			break;
		}
	}

	CvRect rect = cvRect(originX, originY, image.cols - originX, image.rows - originY);
	Mat roi(image, rect);

	delete[] colSum;
	delete[] rowSum;
	return;
}

// set the x,y,width and height for each number region 
void DataIdentity::setRect1_history()
{
	isProcessed = false;											// start data process

	// get the relative position of the three vertex in the first row, relative to the origin 
	CvPoint point[3];
	point[0].x = HISTORY_IMAGEINFO1_DELTAX;
	point[0].y = HISTORY_IMAGEINFO1_DELTAY;
	point[1].x = HISTORY_IMAGEINFO1_DELTAX + HISTORY_IMAGEINFO1_WIDTH1;
	point[1].y = HISTORY_IMAGEINFO1_DELTAY;
	point[2].x = HISTORY_IMAGEINFO1_DELTAX + HISTORY_IMAGEINFO1_WIDTH1 + HISTORY_IMAGEINFO1_WIDTH2 * 2 - 4;
	point[2].y = HISTORY_IMAGEINFO1_DELTAY;

	// get each rect in the original image
	CvRect rect_temp = cvRect(0, 0, 0, 0);
	for (int i = 0; i < horseInfo.horseNum; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			rect_temp.x = point[j].x + originX;
			if (i < 4)
				rect_temp.y = point[j].y + originY + i * (HISTORY_IMAGEINFO1_HEIGHT + 4);

			if (i >= 4)
				rect_temp.y = point[j].y + originY + i * (HISTORY_IMAGEINFO1_HEIGHT + 3) + 4;

			if (j == 0)
				rect_temp.width = HISTORY_IMAGEINFO1_WIDTH1;
			else
				rect_temp.width = HISTORY_IMAGEINFO1_WIDTH2;
			rect_temp.height = HISTORY_IMAGEINFO1_HEIGHT;
			imageInfo1.rect[i][j] = rect_temp;
		}
	}
}


void DataIdentity::setRect2_history()
{

	CvPoint point = cvPoint(originX + HISTORY_IMAGEINFO2_DELTAX, originY + HISTORY_IMAGEINFO2_DELTAY);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			imageInfo2.rect[i][j].x = point.x + j * HISTORY_IMAGEINFO2_QPL_LENGTH + 1;
			imageInfo2.rect[i][j].y = point.y + i * (HISTORY_IMAGEINFO2_HEIGTH);
			imageInfo2.rect[i][j].height = HISTORY_IMAGEINFO2_HEIGTH;
			imageInfo2.rect[i][j].width = HISTORY_IMAGEINFO2_WIDTH;

			if (j == 1 || j == 3 || j == 4)
				imageInfo2.rect[i][j].x += 1;
			if (j == 1 || j == 6 || j == 7 || j == 8)
				imageInfo2.rect[i][j].x -= 2;
			if (j == 9 || j == 10)
				imageInfo2.rect[i][j].x -= 3;
			if (j == 11)
				imageInfo2.rect[i][j].x -= 4;
		}
	}
}


void DataIdentity::setRect3_history()
{
	imageInfo3.rect[0].x = 183 + originX;
	imageInfo3.rect[0].y = 4 + originY;
	imageInfo3.rect[0].height = 25;
	imageInfo3.rect[0].width = 25;

	imageInfo3.rect[1].x = 450 + originX;
	imageInfo3.rect[1].y = 0 + originY;
	imageInfo3.rect[1].height = 16;
	imageInfo3.rect[1].width = 10;
}


void DataIdentity::getHorseName_history()
{

}

bool DataIdentity::identifyDot_history(int i, Mat* edge)			// i -- the current processing image region
{
	int len = 0;
	if (i == 1)									// processing the region 1
		len = HISTORY_IMAGEINFO1_DOT_LEN;

	if (i == 2)									// processing the region 2(QPL)		
		len = HISTORY_IMAGEINFO2_QPL_DOT_LEN;

	int* graySum = new int[edge->cols];
	for (int c = 0; c < edge->cols; c++)
	{
		graySum[c] = 0;
		for (int r = 0; r < edge->rows; r++)
			graySum[c] += edge->at<uchar>(r, c);
		graySum[c] = graySum[c] / edge->cols;
	}
	graySum[0] = 0, graySum[edge->cols] = 0;

	// 计算数字占据的像素长度
	int length;
	int index1 = 0, index2 = edge->cols;
	int c1 = 0, c2 = edge->cols;
	while (graySum[c1] < EDGE_IMAGE_GRAY_THRESHOLD)
	{
		index1++;		c1++;
	}
	while (graySum[c2] < EDGE_IMAGE_GRAY_THRESHOLD)
	{
		index2--; c2--;
	}
	length = c2 - c1;

	// identify contain a dot or not
	if (length > len)
		return true;
	else
		return false;
}

// 3 cases( 0--two number with dot, 1--two number without dot, 2--three number )
int DataIdentity::identifyDot_QIN_history(Mat* edge)
{
	int* graySum = new int[edge->cols];
	for (int c = 0; c < edge->cols; c++)
	{
		graySum[c] = 0;
		for (int r = 0; r < edge->rows; r++)
			graySum[c] += edge->at<uchar>(r, c);
		graySum[c] = graySum[c] / edge->cols;
	}
	graySum[0] = 0;		graySum[1] = 0;
	graySum[edge->cols] = 0;	graySum[edge->cols - 1] = 0;

	// 计算数字占据的像素长度
	int length;
	int index1 = 0, index2 = edge->cols;
	int c1 = 0, c2 = edge->cols;
	while (graySum[c1] < EDGE_IMAGE_GRAY_THRESHOLD)
	{
		index1++;		c1++;
	}
	while (graySum[c2] < EDGE_IMAGE_GRAY_THRESHOLD)
	{
		index2--; c2--;
	}
	length = c2 - c1;


	if (length <= HISTORY_IMAGEINFO2_QPL_DOT_LEN)
		return 1;
	else if (length >= HISTORY_IMAGEINFO2_QIN_DOT_LEN2)
		return 2;
	else
		return 0;

}

int DataIdentity::identifyPeak_history(Mat* edge)
{
	int* graySum = new int[edge->cols];
	for (int c = 0; c < edge->cols; c++)
	{
		graySum[c] = 0;
		for (int r = 0; r < edge->rows; r++)
			graySum[c] += edge->at<uchar>(r, c);
		graySum[c] = graySum[c] / edge->cols;

		if (graySum[c] > EDGE_IMAGE_GRAY_THRESHOLD)
			graySum[c] = 1;
		else
			graySum[c] = 0;
	}
	graySum[0] = 0;		graySum[1] = 0;
	graySum[edge->cols] = 0;	graySum[edge->cols - 1] = 0;

	int gap = 0;
	for (int i = 4; i < edge->cols; i++)											// get the total number of gap between single numbers
	{
		if (graySum[i - 4] == 0 && graySum[i - 3] == 0 && graySum[i - 2] == 0 && graySum[i - 1] == 0 && graySum[i] == 1)
			gap++;
	}

	int jump = 0;																	// get the total number of jump between single numbers
	for (int i = 2; i < edge->cols; i++)
	{
		if (graySum[i - 2] == 0 && graySum[i - 1] == 0 && graySum[i] == 1/* && graySum[i] == 1*/)
			jump++;
	}

	if (gap == 2 && jump == 2)
		return 0;
	else
		return 2;
}


// get the information of the image region 1(WIN and PLA)
void DataIdentity::getImageInfo1_history()
{
	CvRect rectDot[3];
	CvRect rectNoDot[3];

	rectDot[0].x = 3;	rectDot[1].x = 12;		rectDot[2].x = 27;
	rectNoDot[0].x = 3; rectNoDot[1].x = 14;	rectNoDot[2].x = 26;
	for (int i = 0; i < 3; i++)													// set the rect for single number in number region
	{
		rectDot[i].y = 0;
		rectDot[i].width = HISTORY_IMAGEINFO1_SINGLE_WIDTH;
		rectDot[i].height = HISTORY_IMAGEINFO1_HEIGHT;

		rectNoDot[i].y = 0;
		rectNoDot[i].width = HISTORY_IMAGEINFO1_SINGLE_WIDTH;
		rectNoDot[i].height = HISTORY_IMAGEINFO1_HEIGHT;
	}

	float factor[2][3] = { { 10, 1, 0.1 }, { 100, 10, 1 } };							// the first line for dot, the second line for no dat

	// svm identify each number
	Mat edge;
	for (int i = 0; i < horseInfo.horseNum; i++)
	{
		for (int j = 1; j < 3; j++)
		{
			Mat roi(image, imageInfo1.rect[i][j]);

			cvtColor(roi, roi, CV_RGB2GRAY);
			Canny(roi, edge, 400, 360, 3, true);

			bool dotFlag = identifyDot_history(1, &edge);

			float tempSum = 0.0;
			if (dotFlag)															// contain a dot
			{
				for (int k = 0; k < 3; k++)											// segment each single number and svm
				{
					if (k == 2 && rectDot[k].x + rectDot[k].width >= roi.cols)	// cross the boarder
						rectDot[k].width = roi.cols - rectDot[k].x;
					Mat singleNum(roi, rectDot[k]);									// the single number image

					// 					stringstream si, sj, sk;
					// 					string  str_i, str_j, str_k;
					// 					si << i; si >> str_i;
					// 					sj << j; sj >> str_j;
					// 					sk << k; sk >> str_k;
					// 					string str("C:\\Users\\ZhouZY\\Desktop\\sample\\");
					// 					string suffix(".bmp");
					// 					string temp = str + str_i + str_j + str_k + suffix;
					// 					imwrite(temp, singleNum);

					resize(singleNum, singleNum, cvSize(10, 20));
					hog.compute(singleNum, descriptorVector, winStride, padding);
					for (int m = 0; m < HOGFEATURENUMBER; m++)
						hogMat.at<float>(0, m) = descriptorVector[m];

					float result = numSVM.predict(hogMat);
					tempSum += result * factor[0][k];
				}
			}
			else                                                                 // have no dot
			{
				for (int k = 0; k < 3; k++)
				{
					if (k == 2 && rectNoDot[k].x + rectNoDot[k].width >= roi.cols)
						rectNoDot[k].width = roi.cols - rectNoDot[k].x;
					Mat singleNum(roi, rectNoDot[k]);

					// 					stringstream si, sj, sk;
					// 					string  str_i, str_j, str_k;
					// 					si << i; si >> str_i;
					// 					sj << j; sj >> str_j;
					// 					sk << k; sk >> str_k; 
					// 					string str("C:\\Users\\ZhouZY\\Desktop\\sample\\");
					// 					string suffix(".bmp"); 
					// 					string temp = str + str_i + str_j + str_k + suffix;
					// 					imwrite(temp, singleNum);

					resize(singleNum, singleNum, cvSize(10, 20));
					hog.compute(singleNum, descriptorVector, winStride, padding);
					for (int m = 0; m < HOGFEATURENUMBER; m++)
						hogMat.at<float>(0, m) = descriptorVector[m];

					float result = numSVM.predict(hogMat);
					tempSum += result * factor[1][k];
				}
			}

			if (i == 1)
				dataOutput.WIN[j] = tempSum;
			if (i == 2)
				dataOutput.PLA[j] = tempSum;
			cout << tempSum << "  ";

		}			// end j
		cout << endl;
	}				// end i
	cout << "============================" << endl;
}

// get the current QIN
bool DataIdentity::judgeQPL_QIN_history()
{
	imageInfo2.QPL_QINRect = cvRect(originX + HISTORY_QPL_QIN_DELTAX, originY + HISTORY_QPL_QIN_DELTAY, 13, 20);
	Mat roi(image, imageInfo2.QPL_QINRect);

	/*	imwrite("C:\\Users\\ZhouZY\\Desktop\\L.bmp", roi);*/

	cvtColor(roi, roi, CV_RGB2GRAY);

	resize(roi, roi, cvSize(10, 20));
	hog.compute(roi, descriptorVector, winStride, padding);
	for (int m = 0; m < HOGFEATURENUMBER; m++)
		hogMat.at<float>(0, m) = descriptorVector[m];

	float result = numSVM.predict(hogMat);
	if (int(result) == 0)
		return true;
	else
		return false;
}

// get the information of the image region 2(QPL)
void DataIdentity::getImageInfo2_QPL_history()
{

	CvRect rectDot[2];
	CvRect rectNoDot[2];
	rectDot[0].x = 6;	rectDot[1].x = 19;
	rectNoDot[0].x = 5; rectNoDot[1].x = 16;
	for (int i = 0; i < 3; i++)													// set the rect for single number in number region
	{
		rectDot[i].y = 0;
		rectDot[i].width = HISTORY_IMAGEINFO1_SINGLE_WIDTH;
		rectDot[i].height = HISTORY_IMAGEINFO2_HEIGTH;

		rectNoDot[i].y = 0;
		rectNoDot[i].width = HISTORY_IMAGEINFO1_SINGLE_WIDTH;
		rectNoDot[i].height = HISTORY_IMAGEINFO2_HEIGTH;
	}

	float factor[3][3] = { { 1, 0.1 }, { 10, 1 } };							// the first line for dot, the second line for no dat

	// svm identify each number
	Mat edge;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			Mat roi(image, imageInfo2.rect[i][j]);
			cvtColor(roi, roi, CV_RGB2GRAY);
			Canny(roi, edge, 220, 190, 3, false);

			bool dotFlag = identifyDot_history(2, &edge);

			float tempSum = 0.0;
			if (dotFlag)														// contain a dot
			{
				for (int k = 0; k < 2; k++)										// segment each single number and svm
				{
					if (k == 1 && rectDot[k].x + rectDot[k].width >= roi.cols)	// cross the boarder
						rectDot[k].width = roi.cols - rectDot[k].x;
					Mat singleNum(roi, rectDot[k]);								// the single number image

					// 					stringstream si, sj, sk;
					// 					string  str_i, str_j, str_k;
					// 					si << i; si >> str_i;
					// 					sj << j; sj >> str_j;
					// 					sk << k; sk >> str_k;
					// 					string str("C:\\Users\\ZhouZY\\Desktop\\sample\\");
					// 					string suffix(".bmp");
					// 					string temp = str + str_i + str_j + str_k + suffix;
					// 					imwrite(str + str_i + str_j + str_k + suffix, singleNum);

					resize(singleNum, singleNum, cvSize(10, 20));
					hog.compute(singleNum, descriptorVector, winStride, padding);
					for (int m = 0; m < HOGFEATURENUMBER; m++)
						hogMat.at<float>(0, m) = descriptorVector[m];

					float result = numSVM.predict(hogMat);
					tempSum += result * factor[0][k];
				}
			}
			else                                                                 // have no dot
			{
				for (int k = 0; k < 2; k++)
				{
					if (k == 1 && rectDot[k].x + rectDot[k].width >= roi.cols)
						rectDot[k].width = roi.cols - rectDot[k].x;
					Mat singleNum(roi, rectNoDot[k]);

					// 					stringstream si, sj, sk;
					// 					string  str_i, str_j, str_k;
					// 					si << i; si >> str_i;
					// 					sj << j; sj >> str_j;
					// 					sk << k; sk >> str_k;
					// 					string str("C:\\Users\\ZhouZY\\Desktop\\sample\\");
					// 					string suffix(".bmp");
					// 					string temp = str + str_i + str_j + str_k + suffix;
					// 					imwrite(str + str_i + str_j + str_k + suffix, singleNum);

					resize(singleNum, singleNum, cvSize(10, 20));
					hog.compute(singleNum, descriptorVector, winStride, padding);
					for (int m = 0; m < HOGFEATURENUMBER; m++)
						hogMat.at<float>(0, m) = descriptorVector[m];

					float result = numSVM.predict(hogMat);
					tempSum += result * factor[1][k];
				}
			}

			dataOutput.QPL_QIN[i][j] = tempSum;
			cout << tempSum << "  ";

		}			// end j
		cout << endl;
	}				// end i
	cout << "================================" << endl;

}


// get the information of the image region 2(QIN)
void DataIdentity::getImageInfo2_QIN_history()
{
	CvRect rect[3][3];
	rect[0][0].x = 7;	rect[0][1].x = 20;		rect[0][2].x = 0;			// for two number with dot	
	rect[1][0].x = 9;	rect[1][1].x = 17;		rect[1][2].x = 0;			// for two number without dot
	rect[2][0].x = 4;	rect[2][1].x = 13;		rect[2][2].x = 22;			// for three number without dot

	for (int i = 0; i < 3; i++)													// set the rect for single number in number region
	{
		for (int j = 0; j < 3; j++)
		{
			rect[i][j].y = 0;
			rect[i][j].width = HISTORY_IMAGEINFO2_SINGLE_WIDTH;
			rect[i][j].height = HISTORY_IMAGEINFO2_HEIGTH;
		}
	}
	float factor[3][3] = { { 1, 0.1, 0 }, { 10, 1, 0 }, { 100, 10, 1 } };							// the first line for dot, the second line for no dat

	// svm identify each number
	Mat edge;
	int dotFlag;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			Mat roi(image, imageInfo2.rect[i][j]);
			cvtColor(roi, roi, CV_RGB2GRAY);
			Canny(roi, edge, 350, 260, 3, true);

			dotFlag = identifyDot_QIN_history(&edge);
			if (dotFlag == 0)
			{
				Canny(roi, edge, 440, 300, 3, true);
				dotFlag = identifyPeak_history(&edge);
			}

			float tempSum = 0.0;
			if (dotFlag == 0)													// two number with dot
			{
				for (int k = 0; k < 3; k++)										// segment each single number and svm
				{
					if (k == 2 && rect[0][k].x + rect[0][k].width >= roi.cols)	// cross the boarder
						rect[0][k].width = roi.cols - rect[0][k].x;
					Mat singleNum(roi, rect[0][k]);								// the single number image

					// 					stringstream si, sj, sk;
					// 					string  str_i, str_j, str_k;
					// 					si << i; si >> str_i;
					// 					sj << j; sj >> str_j;
					// 					sk << k; sk >> str_k;
					// 					string str("C:\\Users\\ZhouZY\\Desktop\\sample\\");
					// 					string suffix(".bmp");
					// 					string temp = str + str_i + str_j + str_k + suffix;
					// 					imwrite(str + str_i + str_j + str_k + suffix, singleNum);

					resize(singleNum, singleNum, cvSize(10, 20));
					hog.compute(singleNum, descriptorVector, winStride, padding);
					for (int m = 0; m < HOGFEATURENUMBER; m++)
						hogMat.at<float>(0, m) = descriptorVector[m];

					float result = numSVM.predict(hogMat);
					tempSum += result * factor[0][k];
				}
			}
			// 
			if (dotFlag == 1)										// two number without dot
			{
				for (int k = 0; k < 3; k++)										// segment each single number and svm
				{
					if (k == 2 && rect[1][k].x + rect[1][k].width >= roi.cols)	// cross the boarder
						rect[1][k].width = roi.cols - rect[1][k].x;
					Mat singleNum(roi, rect[1][k]);								// the single number image

					// 					stringstream si, sj, sk;
					// 					string  str_i, str_j, str_k;
					// 					si << i; si >> str_i;
					// 					sj << j; sj >> str_j;
					// 					sk << k; sk >> str_k;
					// 					string str("C:\\Users\\ZhouZY\\Desktop\\sample\\");
					// 					string suffix(".bmp");
					// 					string temp = str + str_i + str_j + str_k + suffix;
					// 					imwrite(str + str_i + str_j + str_k + suffix, singleNum);

					resize(singleNum, singleNum, cvSize(10, 20));
					hog.compute(singleNum, descriptorVector, winStride, padding);
					for (int m = 0; m < HOGFEATURENUMBER; m++)
						hogMat.at<float>(0, m) = descriptorVector[m];

					float result = numSVM.predict(hogMat);
					tempSum += result * factor[1][k];
				}
			}
			// 
			if (dotFlag == 2)										// three number without dot
			{
				for (int k = 0; k < 3; k++)										// segment each single number and svm
				{
					if (k == 2 && rect[2][k].x + rect[2][k].width >= roi.cols)	// cross the boarder
						rect[2][k].width = roi.cols - rect[2][k].x;
					Mat singleNum(roi, rect[2][k]);								// the single number image

					// 					stringstream si, sj, sk;
					// 					string  str_i, str_j, str_k;
					// 					si << i; si >> str_i;
					// 					sj << j; sj >> str_j;
					// 					sk << k; sk >> str_k;
					// 					string str("C:\\Users\\ZhouZY\\Desktop\\sample\\");
					// 					string suffix(".bmp");
					// 					string temp = str + str_i + str_j + str_k + suffix;
					// 					imwrite(str + str_i + str_j + str_k + suffix, singleNum);

					resize(singleNum, singleNum, cvSize(10, 20));
					hog.compute(singleNum, descriptorVector, winStride, padding);
					for (int m = 0; m < HOGFEATURENUMBER; m++)
						hogMat.at<float>(0, m) = descriptorVector[m];

					float result = numSVM.predict(hogMat);
					tempSum += result * factor[2][k];
				}
			}


			dataOutput.QPL_QIN[i][j] = tempSum;
			cout << tempSum << "  ";
		}			// end j
		cout << endl;
	}				// end i
	cout << "================================" << endl;
}

// get the current session
void DataIdentity::getSession_history()
{
	imageInfo3.rect[1] = cvRect(450 + originX, 0 + originY, 10, 15);
	Mat roi(image, imageInfo3.rect[1]);
	cvtColor(roi, roi, CV_RGB2GRAY);
	resize(roi, roi, cvSize(10, 20));
	hog.compute(roi, descriptorVector, winStride, padding);
	for (int m = 0; m < HOGFEATURENUMBER; m++)
		hogMat.at<float>(0, m) = descriptorVector[m];

	float result = numSVM.predict(hogMat);
	dataOutput.session = int(result);

	cout << dataOutput.session << endl;

}

// get the minute
void DataIdentity::getMinute_history()
{
	imageInfo3.rect[1] = cvRect(188 + originX, 6 + originY, 15, 22);
	Mat roi(image, imageInfo3.rect[1]);

	cvtColor(roi, roi, CV_RGB2GRAY);
	resize(roi, roi, cvSize(10, 20));
	hog.compute(roi, descriptorVector, winStride, padding);
	for (int m = 0; m < HOGFEATURENUMBER; m++)
		hogMat.at<float>(0, m) = descriptorVector[m];

	float result = numSVM.predict(hogMat);
	dataOutput.raceTime = int(result);
	cout << dataOutput.raceTime << endl;
}


// ==============================================
// live video
// ==============================================

void DataIdentity::setRect1_live()
{
	isProcessed = false;											// start data process

	// get the relative position of the three vertex in the first row, relative to the origin 
	CvPoint point[3];
	point[0].x = LIVE_IMAGEINFO1_DELTAX;
	point[0].y = LIVE_IMAGEINFO1_DELTAY;
	point[1].x = LIVE_IMAGEINFO1_DELTAX + LIVE_IMAGEINFO1_WIDTH1;
	point[1].y = LIVE_IMAGEINFO1_DELTAY;
	point[2].x = LIVE_IMAGEINFO1_DELTAX + LIVE_IMAGEINFO1_WIDTH1 + LIVE_IMAGEINFO1_WIDTH2 * 2 - 4;
	point[2].y = LIVE_IMAGEINFO1_DELTAY;

	// get each rect in the original image
	CvRect rect_temp = cvRect(0, 0, 0, 0);
	for (int i = 0; i < horseInfo.horseNum; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			rect_temp.x = point[j].x + originX;
			if (i < 4)
				rect_temp.y = point[j].y + originY + i * (LIVE_IMAGEINFO1_HEIGHT + 4);

			if (i >= 4)
				rect_temp.y = point[j].y + originY + i * (LIVE_IMAGEINFO1_HEIGHT + 3) + 4;

			if (j == 0)
				rect_temp.width = LIVE_IMAGEINFO1_WIDTH1;
			else
				rect_temp.width = LIVE_IMAGEINFO1_WIDTH2;

			rect_temp.height = LIVE_IMAGEINFO1_HEIGHT;
			imageInfo1.rect[i][j] = rect_temp;
		}
	}
}

void DataIdentity::setRect2_live()
{
	CvPoint point = cvPoint(originX + LIVE_IMAGEINFO2_DELTAX, originY + LIVE_IMAGEINFO2_DELTAY);
	for (int i = 0; i < QIN_QPL_ROW; i++)
	{
		for (int j = 0; j < QIN_QPL_COL; j++)
		{
			imageInfo2.rect[i][j].x = point.x + j * LIVE_IMAGEINFO2_LENGTH;
			imageInfo2.rect[i][j].y = point.y + i * (LIVE_IMAGEINFO2_HEIGTH);
			imageInfo2.rect[i][j].height = LIVE_IMAGEINFO2_HEIGTH;
			imageInfo2.rect[i][j].width = LIVE_IMAGEINFO2_WIDTH;

			// 			if (j == 1 || j == 2 || j == 3 || j == 4 || j == 5 || j == 6)
			// 				imageInfo2.rect[i][j].x -= 2 - 2;
			if (j == 7 || j == 8 || j == 9)
				imageInfo2.rect[i][j].x -= 2;
			if (j == 10)
				imageInfo2.rect[i][j].x -= 3;
			if (j == 11)
				imageInfo2.rect[i][j].x -= 4;
			if (j == 12)
				imageInfo2.rect[i][j].x -= 5;
		}
	}
}

void DataIdentity::setRect3_live()
{
	imageInfo3.rect[0].x = 183 + originX;
	imageInfo3.rect[0].y = 4 + originY;
	imageInfo3.rect[0].height = 25;
	imageInfo3.rect[0].width = 25;

	imageInfo3.rect[1].x = 450 + originX;
	imageInfo3.rect[1].y = 0 + originY;
	imageInfo3.rect[1].height = 16;
	imageInfo3.rect[1].width = 10;
}

void DataIdentity::getHorseName_live()
{

}

bool DataIdentity::identifyImageInfo1_Dot_live(int i, Mat* edge)
{
	int len = 0;
	if (i == 1)									// processing the region 1
		len = LIVE_IMAGEINFO1_DOT_LEN;

	// 	if (i == 2)									// processing the region 2(QPL)		
	// 		len = LIVE_IMAGEINFO2_DOT_LEN;

	int* graySum = new int[edge->cols];
	for (int c = 0; c < edge->cols; c++)
	{
		graySum[c] = 0;
		for (int r = 0; r < edge->rows; r++)
			graySum[c] += edge->at<uchar>(r, c);
		graySum[c] = graySum[c] / edge->cols;
	}
	graySum[0] = 0, graySum[edge->cols] = 0;

	// 计算数字占据的像素长度
	int length;
	int index1 = 0, index2 = edge->cols;
	int c1 = 0, c2 = edge->cols;
	while (graySum[c1] < EDGE_IMAGE_GRAY_THRESHOLD)
	{
		index1++;		c1++;
	}
	while (graySum[c2] < EDGE_IMAGE_GRAY_THRESHOLD)
	{
		index2--; c2--;
	}
	length = c2 - c1;

	// identify contain a dot or not
	if (length > len)
		return true;
	else
		return false;
}


int  DataIdentity::identifyImageInfor2_Dot_live(Mat* edge)
{
	int* graySum = new int[edge->cols];
	for (int c = 0; c < edge->cols; c++)
	{
		graySum[c] = 0;
		for (int r = 0; r < edge->rows; r++)
			graySum[c] += edge->at<uchar>(r, c);
		graySum[c] = graySum[c] / edge->cols;
	}
	graySum[0] = 0;		graySum[1] = 0;
	graySum[edge->cols] = 0;	graySum[edge->cols - 1] = 0;

	// 计算数字占据的像素长度
	int length;
	int index1 = 0, index2 = edge->cols;
	int c1 = 0, c2 = edge->cols;
	while (graySum[c1] < EDGE_IMAGE_GRAY_THRESHOLD)
	{
		index1++;		c1++;
	}
	while (graySum[c2] < EDGE_IMAGE_GRAY_THRESHOLD)
	{
		index2--; c2--;
	}
	length = c2 - c1;

	if (length <= LIVE_IMAGEINFO2_DOT_LEN1)
		return 1;
	else if (length >= LIVE_IMAGEINFO2_DOT_LEN2)
		return 2;
	else
		return 0;
}


int DataIdentity::identifyPeak_live(Mat* edge)
{
	return 1;
}

bool DataIdentity::judgeQPL_QIN_live()
{
	imageInfo2.QPL_QINRect = cvRect(originX + LIVE_QPL_QIN_DELTAX, originY + LIVE_QPL_QIN_DELTAY, 13, 20);
	Mat roi(image, imageInfo2.QPL_QINRect);
	cvtColor(roi, roi, CV_RGB2GRAY);

	resize(roi, roi, cvSize(10, 20));
	hog.compute(roi, descriptorVector, winStride, padding);
	for (int m = 0; m < HOGFEATURENUMBER; m++)
		hogMat.at<float>(0, m) = descriptorVector[m];

	float result = numSVM.predict(hogMat);
	if (int(result) == 0)
		return true;
	else
		return false;
}

void DataIdentity::getImageInfo1_live()
{
	CvRect rectDot[3];
	CvRect rectNoDot[3];

	rectDot[0].x = 3;	rectDot[1].x = 12;		rectDot[2].x = 27;
	rectNoDot[0].x = 3; rectNoDot[1].x = 14;	rectNoDot[2].x = 26;
	for (int i = 0; i < 3; i++)													// set the rect for single number in number region
	{
		rectDot[i].y = 0;
		rectDot[i].width = HISTORY_IMAGEINFO1_SINGLE_WIDTH;
		rectDot[i].height = HISTORY_IMAGEINFO1_HEIGHT;

		rectNoDot[i].y = 0;
		rectNoDot[i].width = HISTORY_IMAGEINFO1_SINGLE_WIDTH;
		rectNoDot[i].height = HISTORY_IMAGEINFO1_HEIGHT;
	}
	float factor[2][3] = { { 10, 1, 0.1 }, { 100, 10, 1 } };							// the first line for dot, the second line for no dat

	// svm identify each number
	Mat edge;
	for (int i = 0; i < horseInfo.horseNum; i++)
	{
		for (int j = 1; j < 3; j++)
		{
			Mat roi(image, imageInfo1.rect[i][j]);

			cvtColor(roi, roi, CV_RGB2GRAY);
			Canny(roi, edge, 400, 360, 3, true);

			bool dotFlag = identifyImageInfo1_Dot_live(1, &edge);

			float tempSum = 0.0;
			if (dotFlag)															// contain a dot
			{
				for (int k = 0; k < 3; k++)											// segment each single number and svm
				{
					if (k == 2 && rectDot[k].x + rectDot[k].width >= roi.cols)	// cross the boarder
						rectDot[k].width = roi.cols - rectDot[k].x;
					Mat singleNum(roi, rectDot[k]);									// the single number image

					// 					stringstream si, sj, sk;
					// 					string  str_i, str_j, str_k;
					// 					si << i; si >> str_i;
					// 					sj << j; sj >> str_j;
					// 					sk << k; sk >> str_k;
					// 					string str("C:\\Users\\ZhouZY\\Desktop\\sample\\");
					// 					string suffix(".bmp");
					// 					string temp = str + str_i + str_j + str_k + suffix;
					// 					imwrite(temp, singleNum);

					resize(singleNum, singleNum, cvSize(10, 20));
					hog.compute(singleNum, descriptorVector, winStride, padding);
					for (int m = 0; m < HOGFEATURENUMBER; m++)
						hogMat.at<float>(0, m) = descriptorVector[m];

					float result = numSVM.predict(hogMat);
					tempSum += result * factor[0][k];
				}
			}
			else                                                                 // have no dot
			{
				for (int k = 0; k < 3; k++)
				{
					if (k == 2 && rectNoDot[k].x + rectNoDot[k].width >= roi.cols)
						rectNoDot[k].width = roi.cols - rectNoDot[k].x;
					Mat singleNum(roi, rectNoDot[k]);

					// 					stringstream si, sj, sk;
					// 					string  str_i, str_j, str_k;
					// 					si << i; si >> str_i;
					// 					sj << j; sj >> str_j;
					// 					sk << k; sk >> str_k;
					// 					string str("C:\\Users\\ZhouZY\\Desktop\\sample\\");
					// 					string suffix(".bmp");
					// 					string temp = str + str_i + str_j + str_k + suffix;
					// 					imwrite(temp, singleNum);

					resize(singleNum, singleNum, cvSize(10, 20));
					hog.compute(singleNum, descriptorVector, winStride, padding);
					for (int m = 0; m < HOGFEATURENUMBER; m++)
						hogMat.at<float>(0, m) = descriptorVector[m];

					float result = numSVM.predict(hogMat);
					tempSum += result * factor[1][k];
				}
			}

			if (j == 1)
				dataOutput.WIN[i] = tempSum;
			if (j == 2)
				dataOutput.PLA[i] = tempSum;
			cout << tempSum << "  ";

		}			// end j
		cout << endl;
	}				// end i
	cout << "============================" << endl;
}

void DataIdentity::getImageInfo2_live()
{
	CvRect rect[3][3];
	rect[0][0].x = 7;	rect[0][1].x = 20;		rect[0][2].x = 0;			// for two number with dot	
	rect[1][0].x = 6;	rect[1][1].x = 16;		rect[1][2].x = 0;			// for two number without dot
	rect[2][0].x = 0;	rect[2][1].x = 11;		rect[2][2].x = 22;			// for three number without dot

	for (int i = 0; i < 3; i++)													// set the rect for single number in number region
	{
		for (int j = 0; j < 3; j++)
		{
			rect[i][j].y = 0;
			rect[i][j].width = LIVE_IMAGEINFO2_SINGLE_WIDTH;
			rect[i][j].height = LIVE_IMAGEINFO2_HEIGTH;
		}
	}
	float factor[3][3] = { { 1, 0.1, 0 }, { 10, 1, 0 }, { 100, 10, 1 } };							// the first line for dot, the second line for no dat

	// svm identify each number
	Mat edge;
	int dotFlag;
	for (int i = 0; i < QIN_QPL_ROW; i++)
	{
		for (int j = 0; j < QIN_QPL_COL; j++)
		{
			Mat roi(image, imageInfo2.rect[i][j]);

			cvtColor(roi, roi, CV_RGB2GRAY);
			Canny(roi, edge, 450, 350, 3, true);

			// 			stringstream si, sj;
			// 			string  str_i, str_j, str_k;
			// 			si << i; si >> str_i;
			// 			sj << j; sj >> str_j;
			// 			string str("C:\\Users\\ZhouZY\\Desktop\\sample\\");
			// 			string suffix(".bmp");
			// 			string temp = str + str_i + str_j + suffix;
			// 			imwrite(temp, edge);

			dotFlag = identifyImageInfor2_Dot_live(&edge);
			float tempSum = 0.0;
			if (dotFlag == 0)													// two number with dot
			{
				for (int k = 0; k < 2; k++)										// segment each single number and svm
				{
					if (k == 1 && rect[0][k].x + rect[0][k].width >= roi.cols)	// cross the boarder
						rect[0][k].width = roi.cols - rect[0][k].x;
					Mat singleNum(roi, rect[0][k]);								// the single number image

					// 					stringstream si, sj, sk;
					// 					string  str_i, str_j, str_k;
					// 					si << i; si >> str_i;
					// 					sj << j; sj >> str_j;
					// 					sk << k; sk >> str_k;
					// 					string str("C:\\Users\\ZhouZY\\Desktop\\sample\\");
					// 					string suffix(".bmp");
					// 					string temp = str + str_i + str_j + str_k + suffix;
					// 					imwrite(temp, singleNum);

					resize(singleNum, singleNum, cvSize(10, 20));
					hog.compute(singleNum, descriptorVector, winStride, padding);
					for (int m = 0; m < HOGFEATURENUMBER; m++)
						hogMat.at<float>(0, m) = descriptorVector[m];

					float result = numSVM.predict(hogMat);
					tempSum += result * factor[0][k];
				}
			}

			if (dotFlag == 1)										// two number without dot
			{
				for (int k = 0; k < 2; k++)										// segment each single number and svm
				{
					if (k == 1 && rect[1][k].x + rect[1][k].width >= roi.cols)	// cross the boarder
						rect[1][k].width = roi.cols - rect[1][k].x;
					Mat singleNum(roi, rect[1][k]);								// the single number image

					// 					stringstream si, sj, sk;
					// 					string  str_i, str_j, str_k;
					// 					si << i; si >> str_i;
					// 					sj << j; sj >> str_j;
					// 					sk << k; sk >> str_k;
					// 					string str("C:\\Users\\ZhouZY\\Desktop\\sample\\");
					// 					string suffix(".bmp");
					// 					string temp = str + str_i + str_j + str_k + suffix;
					// 					imwrite(temp, singleNum);

					resize(singleNum, singleNum, cvSize(10, 20));
					hog.compute(singleNum, descriptorVector, winStride, padding);
					for (int m = 0; m < HOGFEATURENUMBER; m++)
						hogMat.at<float>(0, m) = descriptorVector[m];

					float result = numSVM.predict(hogMat);
					tempSum += result * factor[1][k];
				}
			}

			if (dotFlag == 2)										// three number without dot
			{
				for (int k = 0; k < 3; k++)										// segment each single number and svm
				{
					if (k == 2 && rect[2][k].x + rect[2][k].width >= roi.cols)	// cross the boarder
						rect[2][k].width = roi.cols - rect[2][k].x;
					Mat singleNum(roi, rect[2][k]);								// the single number image

					// 					stringstream si, sj, sk;
					// 					string  str_i, str_j, str_k;
					// 					si << i; si >> str_i;
					// 					sj << j; sj >> str_j;
					// 					sk << k; sk >> str_k;
					// 					string str("C:\\Users\\ZhouZY\\Desktop\\sample\\");
					// 					string suffix(".bmp");
					// 					string temp = str + str_i + str_j + str_k + suffix;
					// 					imwrite(temp, singleNum);

					resize(singleNum, singleNum, cvSize(10, 20));
					hog.compute(singleNum, descriptorVector, winStride, padding);
					for (int m = 0; m < HOGFEATURENUMBER; m++)
						hogMat.at<float>(0, m) = descriptorVector[m];

					float result = numSVM.predict(hogMat);
					tempSum += result * factor[2][k];
				}
			}


			dataOutput.QPL_QIN[i][j] = tempSum;
			cout << tempSum << "  ";
		}			// end j
		cout << endl;
	}				// end i
	cout << "================================" << endl;
}


void DataIdentity::getSession_live()
{
	imageInfo3.rect[1] = cvRect(211 + originX, 9 + originY, 15, 20);
	Mat roi(image, imageInfo3.rect[1]);

	// 	imshow("a", roi);
	// 	waitKey();

	cvtColor(roi, roi, CV_RGB2GRAY);
	resize(roi, roi, cvSize(10, 20));
	hog.compute(roi, descriptorVector, winStride, padding);
	for (int m = 0; m < HOGFEATURENUMBER; m++)
		hogMat.at<float>(0, m) = descriptorVector[m];

	float result = numSVM.predict(hogMat);
	dataOutput.session = int(result);

	cout << dataOutput.session << endl;
}

void DataIdentity::getMinute_live()
{
	imageInfo3.rect[1] = cvRect(510 + originX, 4 + originY, 12, 17);
	Mat roi(image, imageInfo3.rect[1]);

	imwrite("C:\\Users\\ZhouZY\\Desktop\\3.bmp", roi);

	cvtColor(roi, roi, CV_RGB2GRAY);
	resize(roi, roi, cvSize(10, 20));
	hog.compute(roi, descriptorVector, winStride, padding);
	for (int m = 0; m < HOGFEATURENUMBER; m++)
		hogMat.at<float>(0, m) = descriptorVector[m];

	float result = numSVM.predict(hogMat);
	dataOutput.raceTime = int(result);
	cout << dataOutput.raceTime << endl;
}











