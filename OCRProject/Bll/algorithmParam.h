#define HORSENUMBER					 14
#define QIN_QPL_ROW					 7
#define QIN_QPL_COL					 15

#define HOGFEATURENUMBER			 108
#define DATA_CONSISTENCY			 10


#define HAVEDATA_PIXELNUMBER         5				// the total number of pixels for identify the frame having the data or not
#define HAVEDATA_XINDEX              30				// the x-position of the pixel for identify the frame having the data or not
#define HAVEDATA_YINDEX			     40				// the y(40*i)-position of the pixel for identify the frame having the data or not
#define HAVEDATA_BLUETHRESHOLD	     56				// the threshold of blue channel, if >HAVEDATA_BLUETHRESHOLD and <HAVEDATA_GREENTHRESHOLD then identify this pixel is blue
#define HAVEDATA_GREENTHRESHOLD      10


#define ORIGINPOSITION_REGIONWIDTH			  100			// the
#define ORIGINPOSITION_REGIONHEIGHT			  100
#define ORIGINPOSITION_COLSUM_THRESHOLD       26				// 
#define ORIGINPOSITION_ROWSUM_THRESHOLD       30
#define EDGE_IMAGE_GRAY_THRESHOLD			  20		// the gray threshold of a edge image 

// ======================================================
// history video
#define HISTORY_IMAGEINFO1_DELTAX					  12			// the x-shift relative to the orign
#define HISTORY_IMAGEINFO1_DELTAY					  26
#define HISTORY_IMAGEINFO1_HEIGHT					  18		// the region image contain the the whole character
#define HISTORY_IMAGEINFO1_WIDTH1					  62
#define HISTORY_IMAGEINFO1_WIDTH2					  42
#define HISTORY_IMAGEINFO1_NUMBER					  3			// the total number in a whole character
#define HISTORY_IMAGEINFO1_DOT_LEN					  29		// the length threshold of a whole number region which contains a dot
#define HISTORY_IMAGEINFO1_SINGLE_WIDTH				  12		// the width of a single number


#define HISTORY_IMAGEINFO2_DELTAX					  20
#define HISTORY_IMAGEINFO2_DELTAY					  302
#define HISTORY_IMAGEINFO2_HEIGTH					  16		 
#define HISTORY_IMAGEINFO2_WIDTH					  33		// the whole number region width	
#define HISTORY_IMAGEINFO2_SINGLE_WIDTH				  10

#define HISTORY_IMAGEINFO2_QPL_NUMBER				  2
#define HISTORY_IMAGEINFO2_QPL_LENGTH				  33		// the x-distance of each character vertex
#define HISTORY_IMAGEINFO2_QPL_DOT_LEN				  17		// the length threshold of a whole number region which contains a dot

#define HISTORY_IMAGEINFO2_QIN_NUMBER				  3
#define HISTORY_IMAGEINFO2_QIN_LENGTH				  33
#define HISTORY_IMAGEINFO2_QIN_DOT_LEN1				  17
#define HISTORY_IMAGEINFO2_QIN_DOT_LEN2				  21

#define HISTORY_QPL_QIN_DELTAX						  66
#define HISTORY_QPL_QIN_DELTAY						  342


// ======================================================
// live video
#define LIVE_IMAGEINFO1_DELTAX					  12			// the x-shift relative to the orign
#define LIVE_IMAGEINFO1_DELTAY					  26
#define LIVE_IMAGEINFO1_HEIGHT					  18		// the region image contain the the whole character
#define LIVE_IMAGEINFO1_WIDTH1					  62
#define LIVE_IMAGEINFO1_WIDTH2					  42
#define LIVE_IMAGEINFO1_NUMBER					  3			// the total number in a whole character
#define LIVE_IMAGEINFO1_DOT_LEN					  29		// the length threshold of a whole number region which contains a dot
#define LIVE_IMAGEINFO1_SINGLE_WIDTH			  12		// the width of a single number


#define LIVE_IMAGEINFO2_DELTAX					  25
#define LIVE_IMAGEINFO2_DELTAY					  363
#define LIVE_IMAGEINFO2_HEIGTH					  19		 
#define LIVE_IMAGEINFO2_WIDTH					  35		// the whole number region width	
#define LIVE_IMAGEINFO2_SINGLE_WIDTH			  12

#define LIVE_IMAGEINFO2_NUMBER					  3
#define LIVE_IMAGEINFO2_LENGTH					  37
#define LIVE_IMAGEINFO2_DOT_LEN1				  19
#define LIVE_IMAGEINFO2_DOT_LEN2				  24

#define LIVE_QPL_QIN_DELTAX						  66
#define LIVE_QPL_QIN_DELTAY						  342










