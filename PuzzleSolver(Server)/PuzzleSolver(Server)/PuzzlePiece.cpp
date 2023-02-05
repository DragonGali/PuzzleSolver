#include "PuzzlePiece.h"

PuzzlePiece::PuzzlePiece(vector<Point> contour, Point center, Mat pic, Mat mask, int id)
{
	double threshold = 3;
	_contour.push_back(contour[0]);
	contour.erase(contour.begin());

	while (!contour.empty()) {
		std::vector<double> distances;
		for (cv::Point b : contour) {
			distances.push_back(distance(_contour.back(), b));
		}
		int index = std::distance(distances.begin(), std::min_element(distances.begin(), distances.end()));
		cv::Point point = contour[index];
		contour.erase(contour.begin() + index);
		if (distances[index] < threshold) {
			_contour.push_back(point);
		}
	}


	_pic = pic;
	_center = center;
	_mask = mask;
	_id = id;
	_hasMoved = false;

	findEdgePoints();
	if (_points.size() != 0)
	{
		seperateSubContours();
	}
	//fixRotation();
}

int PuzzlePiece::getId()
{
	return _id;
}

Mat PuzzlePiece::getImage()
{
	return _pic;
}

vector<Point> PuzzlePiece::getContour()
{
	return _contour;
}

vector<Point> PuzzlePiece::getPoints()
{
	return _points;
}

Point PuzzlePiece::getCenter()
{
	return _center;
}

void PuzzlePiece::setContour(vector<Point> contour)
{
	_contour = contour;
}

bool PuzzlePiece::checkMovement()
{
	return _hasMoved;
}

void PuzzlePiece::Moved()
{
	_hasMoved = true;
}

/*

	This function uses opencv functio s in order to find the points on the mask that have the most
	edge in them, then the function filters out the points by finding a set of four points that have 90 degrees between
	them and have the most area.

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
	threshold(data, data, 0.5 * maxValue, 1, THRESH_TOZERO);
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
	vector<Point> maxPoints;

	double maxArea = 0;

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


					if ((Area(points) >= maxArea) && deg90_counter == 2) {
						maxArea = Area(points);
						maxPoints = points;
					}

				}
			}
		}
	}



	_points.insert(bestpoints.end(), maxPoints.begin(), maxPoints.end());
	
}

/*

	This function seperates the contour into "sub - contours" in order to aproximate the
	shape of the puzzle piece later, it forst finds the closest points on the contour to the points found priviously
	and then loops throgh all of them adding each subcontour into a seperate vector.

*/

void PuzzlePiece::seperateSubContours()
{
	Point A = Point(0, 0);
	Point B = Point(0, 0);
	Point C = Point(0, 0);
	Point D = Point(0, 0);

	for (int i = 0; i < _contour.size(); i++)
	{
		if (distance(_contour[i], _points[0]) < distance(A, _points[0]))
		{
			A = _contour[i];
		}

		else if (distance(_contour[i], _points[1]) < distance(B, _points[1]))
		{
			B = _contour[i];
		}

		else if (distance(_contour[i], _points[2]) < distance(C, _points[2]))
		{
			C = _contour[i];
		}

		else if (distance(_contour[i], _points[3]) < distance(D, _points[3]))
		{
			D = _contour[i];
		}
	}

	circle(_pic, A, 5, Scalar(255, 255, 0), -1);
	circle(_pic, B, 5, Scalar(255, 255, 0), -1);
	circle(_pic, C, 5, Scalar(255, 255, 0), -1);
	circle(_pic, D, 5, Scalar(255, 255, 0), -1);

	int start_stop = 0;
	int i = _contour.size() - 1;
	
	vector<Point> vec1;
	vector<Point> vec2;
	vector<Point> vec3;
	vector<Point> vec4;

	Point previousPoint;
	
	while(start_stop != 5)
	{
		if (_contour[i] == A || _contour[i] == B || _contour[i] == C || _contour[i] == D)
		{
			start_stop++;

			
		}


		else if (start_stop == 1)
		{
			vec1.push_back(_contour[i]);

			_pic.at<Vec3b>(_contour[i]) = Vec3b(0, 0, 255);
			previousPoint = _contour[i];

		}

		else if (start_stop == 2)
		{
			vec2.push_back(_contour[i]);
			_pic.at<Vec3b>(_contour[i]) = Vec3b(255, 0, 0);
		}

		else if (start_stop == 3)
		{
			vec3.push_back(_contour[i]);
			_pic.at<Vec3b>(_contour[i]) = Vec3b(0, 255, 255);
		}

		else if (start_stop == 4)
		{
			vec4.push_back(_contour[i]);
			_pic.at<Vec3b>(_contour[i]) = Vec3b(0, 255, 0);
		}

		
		i--;

		if (i == 0)
		{
			i = _contour.size() - 1;
		}
	}
	

	imshow("PIC", _pic);
	waitKey(0);

	sides.push_back(Side(vec1, vec1[0], vec1[vec1.size() - 1], 0));
	sides.push_back(Side(vec2, vec2[0], vec2[vec2.size() - 1], 1));
	sides.push_back(Side(vec3, vec3[0], vec3[vec3.size() - 1], 2));
	sides.push_back(Side(vec4, vec4[0], vec4[vec4.size() - 1], 3));


	
	
}

double PuzzlePiece::distance(Point A, Point B)// calculates the distance between two points
{
	return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

double PuzzlePiece::L(Point A, Point B) {//is used to calculate the angle between three points
	// Return length between A and B
	return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

double PuzzlePiece::angle(Point A, Point B, Point C) {// calculates the angle between three points
	// Return angle between the points A-B-C in degrees
	double num = (L(A, B) * L(A, B) + L(B, C) * L(B, C) - L(A, C) * L(A, C));
	double den = (2 * L(A, B) * L(B, C));
	return round(acos(num / den) * 180.0 / CV_PI);
}


double PuzzlePiece::Area(vector<Point> corners) {// calculates the area between the corners of the puzzle piece
	 // Create a convex hull from the corner points
	vector<Point> hull;
	convexHull(corners, hull);
	// Check if the convex hull has 4 points (a quadrilateral)
	if (hull.size() != 4) {
		// Return -1 if the convex hull does not have 4 points
		return -1;
	}
	// Calculate the area of the quadrilateral
	double area = contourArea(hull);
	return area;
}


/*

	This function calculates the angle of the puzzle piece with minAreaRect and rotates the image
	for it to be positioned streight, this is done inorder to fit the pieces together later.

*/
void PuzzlePiece::fixRotation()
{
	RotatedRect rect = minAreaRect(_points);
	float angle = rect.angle;
	if (rect.size.width < rect.size.height)
		angle += 90.0;

	cv::Point2f center = rect.center;
	cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, 1.0);
	cv::Mat rotated_image;
	cv::warpAffine(_pic, rotated_image, rot_mat, _pic.size());

	imshow("rotated", rotated_image);
	waitKey(0);

	_pic = rotated_image;
}


