#include "Side.h";
class PuzzlePiece
{
private:
	Mat _pic;
	vector<Point> _contour;
	Point _center;
	string type;
	vector<Point> _points;
	int _id;

	double L(Point A, Point B);
	double angle(Point A, Point B, Point C);
	double Area(vector<Point> corners);

	bool _hasMoved;

public:
	void findEdgePoints();
	void seperateSubContours();
	void fixRotation();
	double distance(Point A, Point B);

	int getId();
	Mat getImage();
	vector<Point> getContour();
	vector<Point> getPoints();
	Point getCenter();
	Mat _mask;

	bool checkMovement();
	void Moved();

	void setContour(vector<Point> contour);

	vector<Side> sides;

	PuzzlePiece(vector<Point> contour, Point center, Mat pic, Mat mask, int id);
	PuzzlePiece()
	{
		//just to get distance function...
	}


};
