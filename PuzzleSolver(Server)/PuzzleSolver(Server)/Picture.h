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
//#include <amp_graphics.h>
//#include <dos.h>

using namespace std;
using namespace cv;

typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;

typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;

class Picture
{
private:

	vector<Mat> _pieces;
	Mat _image;
	Mat angleMap;
	vector<vector<Point>> BoundaryPoints;

	Mat CreateGrayScale();
	Mat EdgeDetection();
	Mat sobelFilter(Mat grayImage);
	Mat applyNonMaxSupression(Mat& srcImage);
	Mat threshold(Mat imgin, int low, int high);
	vector<vector<Point>> findContours(Mat grid);
	Mat bitwise_and_255(Mat mask, int f);

	vector<Point> neighbors(const Point& p) {
		return {
				{p.x - 1, p.y - 1}, {p.x, p.y - 1}, {p.x + 1, p.y - 1},
				{p.x - 1, p.y},                 {p.x + 1, p.y},
				{p.x - 1, p.y + 1}, {p.x, p.y + 1}, {p.x + 1, p.y + 1}
		};
	}

public:
	Picture(string link);
	void CreateMask();
	void ShowPicture(Mat image);
	void ResizeCanvas();

	


};
