#include <iostream>
#define CV_IGNORE_DEBUG_BUILD_GUARD
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

#include <opencv2/opencv.hpp>
#include <stack>
#include <cstdint>
#include <stdint.h>

#include <cmath>
#include <complex>
#define _USE_MATH_DEFINES

using namespace std;
using namespace cv;

typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;

typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;

class Picture
{
private:

	//Dont think i need the size and type of the image for now
	int _numOfPuzPieces;
	Mat _image;
	Mat angleMap;

	Mat CreateGrayScale();
	void RemoveImageNoise();
	void EdgeDetection();
	void BlurrImage();
	Mat sobelFilter(Mat grayImage);
	void applyNonMaxSupression(Mat& srcImage, Mat& srcAngleMap, Mat& dstImage);
	Mat threshold(Mat imgin, int low, int high);

public:
	Picture(string link);
	Mat CreateMask();
	stack<Mat> CutOutPuzzlePieces();
	void ShowPicture();
	void ResizeCanvas();

	


};
