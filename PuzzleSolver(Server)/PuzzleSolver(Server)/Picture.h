#include <iostream>
#define CV_IGNORE_DEBUG_BUILD_GUARD
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

#include <opencv2/opencv.hpp>
#include <stack>
using namespace std;
using namespace cv;

class Picture
{
private:

	//Dont think i need the size and type of the image for now
	int _numOfPuzPieces;
	Mat _image;

	void CreateGrayScale();

	void RemoveImageNoise();

public:
	Picture(string link);
	Mat CreateMask();
	stack<Mat> CutOutPuzzlePieces();
	void ShowPicture();
	void ResizeCanvas();

	


};
