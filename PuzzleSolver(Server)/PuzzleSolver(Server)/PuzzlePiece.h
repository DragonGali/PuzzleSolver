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

class PuzzlePiece
{
private:
	Mat _pic;
	vector<Point> _contour;
	Point _center;
	vector<vector<Point>> _subContours;
	string type;
	int _counter;
	Mat _mask;

	double L(Point A, Point B);
	double angle(Point A, Point B, Point C);
	double Area(vector<Point> corners);
	double distance(Point A, Point B);

public:
	void findEdgePoints();
	void seperateSubContours(vector<Point> points);
	void calcDistance();
	void fixRotation();

	PuzzlePiece(vector<Point> contour, Point center, Mat pic, Mat mask);


};
