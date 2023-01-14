#include "PuzzlePiece.h"


PuzzlePiece::PuzzlePiece(vector<Point> contour, Point center, Mat pic, Mat mask)
{
	_pic = pic;
	_center = center;
	_contour = contour;
	_mask = mask;

	findEdgePoints();
}

/*

	This function uses an algorithm invented by me and I shall dub it the "Gali algorithm".
	What this algorithm does is use the convexHull to mark the outer rectangle of the puzzle piece, 
	what we want is the inner rectangle, that why when we hit the first side of the red rectangle we start counting,
	we count until we see it again, we also cound the whie pixels in the line, if the line is an inner rectangle line
	then that means that the number of white pixels is supposed to be at least two thirds. This isnt the "Perfect" method
	but it works. This method works best for puzzle pieces that are standing upright.

*/

void PuzzlePiece::findEdgePoints()
{
	Mat dst = Mat(_mask.size(), _mask.type());

	cornerHarris(_mask, dst, 20, 31, 0.04);
	dilate(dst, dst, Mat());
	dst.mul(_mask);
	cv::Mat data = dst.clone();

	double minValue, maxValue;
	Point minLocation, maxLocation;
	minMaxLoc(data, &minValue, &maxValue, &minLocation, &maxLocation);
	threshold(data, data, 0.2 * maxValue, 1, THRESH_TOZERO);
	Mat blobs = data.clone();
	blobs.convertTo(blobs, CV_8UC1);
	vector<vector<Point>> contours0;
	vector<Vec4i> hierarchy;
	findContours(blobs, contours0, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<Moments> moments;
	for (auto& cnt : contours0) {
		moments.push_back(cv::moments(cnt));
	}
	vector<Point> centroids;
	for (auto& m : moments) {
		if (m.m00 != 0) {
			centroids.push_back(Point(m.m10 / m.m00, m.m01 / m.m00));
		}
	}
	Mat img2 = Mat::zeros(_pic.size(), _pic.type());
	Mat binary_channel;
	threshold(_mask, binary_channel, 1, 255, THRESH_BINARY);
	img2 = binary_channel;
	Mat image;


	int target = 90; //deg
	int delta = 5; //deg
	vector<Point> bestpoints;

	for (int i = 0; i < centroids.size(); i++) {
		for (int j = i + 1; j < centroids.size(); j++) {
			for (int k = j + 1; k < centroids.size(); k++) {
				for (int l = k + 1; l < centroids.size(); l++) {
					vector<Point> points = { centroids[i], centroids[j], centroids[k], centroids[l] };
					int deg90_counter = 0;
					if (abs(angle(points[0], points[1], points[2]) - target) < delta) {
						deg90_counter += 1;
					}
					if (abs(angle(points[0], points[1], points[3]) - target) < delta) {
						deg90_counter += 1;
					}
					if (abs(angle(points[0], points[2], points[3]) - target) < delta) {
						deg90_counter += 1;
					}
					if (abs(angle(points[1], points[2], points[3]) - target) < delta) {
						deg90_counter += 1;
					}
					if (deg90_counter >= 2) {
						bestpoints.insert(bestpoints.end(), points.begin(), points.end());
					}

				}
			}
		}
	}

	//for (int i = 0; i < 4; i++) {
	//	circle(_pic, bestpoints[i], 5, Scalar(255, 255, 0), -1);
	//}
	
	seperateSubContours(bestpoints);


	imshow("PIC", _pic);
	waitKey(0);
	
}

void PuzzlePiece::seperateSubContours(vector<Point> points)
{
	Point A = Point(0, 0);
	Point B = Point(0, 0);
	Point C = Point(0, 0);
	Point D = Point(0, 0);

	for (int i = 0; i < _contour.size(); i++)
	{
		if (distance(_contour[i], points[0]) < distance(A, points[0]))
		{
			A = _contour[i];
		}

		else if (distance(_contour[i], points[1]) < distance(B, points[1]))
		{
			B = _contour[i];
		}

		else if (distance(_contour[i], points[2]) < distance(C, points[2]))
		{
			C = _contour[i];
		}

		else if (distance(_contour[i], points[3]) < distance(D, points[3]))
		{
			D = _contour[i];
		}
	}

	circle(_pic, A, 5, Scalar(255, 255, 0), -1);
	circle(_pic, B, 5, Scalar(255, 255, 0), -1);
	circle(_pic, C, 5, Scalar(255, 255, 0), -1);
	circle(_pic, D, 5, Scalar(255, 255, 0), -1);

	int start_stop = 0;
	int i = 0;

	while(start_stop != 4)
	{
		if (_contour[i] == A)
		{
			start_stop++;
		}

		else if (_contour[i] == B)
		{
			start_stop++;
		}



		if (start_stop == 1)
		{
			_pic.at<Vec3b>(_contour[i]) = Vec3b(255, 0, 0);
		}

		
		i++;

		if (i == _contour.size() - 1)
		{
			i = 0;
		}
	}

	cv::imshow("PIC", _pic);
	cv::waitKey(0);

	
}

double PuzzlePiece::distance(Point A, Point B)
{
	return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

double PuzzlePiece::L(Point A, Point B) {
	// Return length between A and B
	return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

double PuzzlePiece::angle(Point A, Point B, Point C) {
	// Return angle between the points A-B-C in degrees
	double num = (L(A, B) * L(A, B) + L(B, C) * L(B, C) - L(A, C) * L(A, C));
	double den = (2 * L(A, B) * L(B, C));
	return round(acos(num / den) * 180.0 / CV_PI);
}


double PuzzlePiece::Area(vector<Point> corners) {
	//By means of "shoelace algorithm"
	int n = corners.size(); // of corners
	double area = 0.0;
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		area += corners[i].x * corners[j].y;
		area -= corners[j].x * corners[i].y;
	}
	area = abs(area) / 2.0;
	return area;
}


