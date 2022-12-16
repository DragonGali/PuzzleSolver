#include "PuzzlePiece.h"


PuzzlePiece::PuzzlePiece(vector<Point> contour, Point center, Mat pic)
{
	_pic = pic;
	_center = center;
	_contour = contour;

	findEdgePoints();
}

void PuzzlePiece::findEdgePoints()
{
	
	// Use a convex hull algorithm to approximate the shape of the contour
	vector<Point> hull;
	convexHull(_contour, hull);

	// Fit a minimum rectangle around the convex hull
	RotatedRect rect = minAreaRect(hull);

	// Calculate the corner points of the rectangle
	Point2f box[4];
	rect.points(box);

	// Draw the corner points on the original image
	for (int i = 0; i < 4; i++) {
		line(_pic, box[i], box[(i + 1) % 4], Scalar(0, 0, 255), 2);
	}

	
	Point P1;
	Point P2;
	Point P3;
	Point P4;

	// PART 1

	for (int i = 0; i < _pic.rows; i++)
	{
		int count1, count2, found2, found1, first, last;
		count1 = count2 = found2 = found1 = first = last = 0;
		for (int j = 0; j < _pic.cols; j++)
		{
			if (!(j == first + 10 && _pic.at<Vec3b>(i, j) == Vec3b(0, 0, 255)))
			{

				if (_pic.at<Vec3b>(i, j) == Vec3b(0, 0, 255) && found2 == 0)
				{

					if (found1 <= 0)
					{
						first = j;
						found1++;
					}

					else if (found1 >= 5)
					{
						found2++;
						last = j - 1;
					}

					else
					{
						found1++;
					}
				}



				if (found1 > 0 && found1 <= 10 && found2 == 0)
				{
					if (_pic.at<Vec3b>(i, j) != Vec3b(0, 0, 0))
					{
						count2++;
					}

					count1++;
				}


			}
		}

		if (count2 > (count1 / 2) && count1 > 10)
		{
			P1 = Point(i, first);
			P2 = Point(i, last);

			break;
		}
	}

	// Part 2

	for (int i = _pic.rows; i > 0; i--)
	{
		int count1, count2, found2, found1, first, last;
		count1 = count2 = found2 = found1 = first = last = 0;

		for (int j = 0; j < _pic.cols; j++)
		{
			if (!(j == first + 10 && _pic.at<Vec3b>(i, j) == Vec3b(0, 0, 255)))
			{

				if (_pic.at<Vec3b>(i, j) == Vec3b(0, 0, 255) && found2 == 0)
				{
					if (found1 <= 0)
					{
						first = j;
						found1++;
					}

					else if (found1 >= 5)
					{
						found2++;
						last = j - 1;
					}

					else
					{
						found1++;
					}
				}

				if (found1 > 0 && found1 <= 10 && found2 == 0)
				{
					if (_pic.at<Vec3b>(i, j) != Vec3b(0, 0, 0))
					{
						count2++;
					}

					count1++;
				}
			}
		}

		if (count2 > (count1 / 2) && count1 > 10)
		{
			P3 = Point(i, first);
			P4 = Point(i, last);

			break;
		}
	}

	imshow("pic", _pic);
	waitKey(0);



}

