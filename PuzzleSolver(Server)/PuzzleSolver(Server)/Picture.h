#include "PuzzlePiece.h"


class Picture
{
private:

	vector<PuzzlePiece> _pieces;
	Mat _image;
	Mat angleMap;

	Mat CreateGrayScale();
	Mat EdgeDetection();
	Mat sobelFilter(Mat grayImage);
	Mat applyNonMaxSupression(Mat& srcImage);
	Mat threshold(Mat imgin, int low, int high);
	vector<vector<Point>> findContours(Mat grid);
	Mat bitwise_and_255(Mat mask, int f);
	double getAreaBetweenPoints(vector<Point> contour, Point start, Point end);
	vector<Point> UpdateContour(PuzzlePiece piece, Point new_center);
	void makeTransparent(Mat image);

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
	void findMatches();
	void movePieces();


};
