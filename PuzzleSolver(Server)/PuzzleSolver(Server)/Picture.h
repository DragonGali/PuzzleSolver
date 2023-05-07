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

	// *functions i ended up not using but spent a lot of time coding*
	Mat applyNonMaxSupression(Mat& srcImage);
	Mat threshold(Mat imgin, int low, int high);

	vector<vector<Point>> findContours(Mat grid);
	Mat bitwise_and_255(Mat mask, int f);
	Mat Transport(Mat src, Mat dst, Point point);

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
	void ResizeCanvas();
	void findMatches();
	void movePieces();


};
