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
		Side(vector<Point> contour, int num);
		double FindDifference(vector<Point> v1, vector<Point> v2);

		vector<Point> _contour;
		
		int _id;
		string matchId;
		string _type;

	private:
		double euclidean_distance(Point p1, Point p2);
		double p_distance(Point p1, vector<Point> curve);
		double curve_metrix(vector<Point> curve1, vector<Point> curve2);
		Point centroid(vector<Point> curve);
		vector<Point> recenter(vector<Point> curve);
		bool isFlat(vector<Point> contour);

};
