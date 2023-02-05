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
#include <fstream>
#define _USE_MATH_DEFINES

using namespace std;
using namespace cv;

typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;

typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;

class Side
{
	public:
		Side(vector<Point> contour, Point a, Point b, int num)
		{
			_contour = contour;
			A = a;
			B = b;

			_id = num;
		}

		vector<Point> _contour;
		Point A;
		Point B;

		
		int _id;
		string matchId;
};
