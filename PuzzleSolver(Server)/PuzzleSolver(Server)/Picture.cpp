#include "Picture.h"

Picture::Picture(string link)
{
	_image = imread(link);
	ResizeCanvas();
	ShowPicture(_image);
	CreateMask();


}

void Picture::ShowPicture(Mat image) // Function for chwecking how the image looks.
{
	imshow("image", image);
	waitKey(0);
}

/*

	This function resizes the image in order for it to not be too big.
	For now its using am open cv function but i might change it later.

*/

void Picture::ResizeCanvas()
{
	resize(_image, _image, cvSize(320, 200));
}

/*
   Applies the Sobel operator to an image to highlight its edges.
 
   The Sobel operator uses two 3x3 convolution kernels, one for detecting
   horizontal edges and one for detecting vertical edges. These kernels are
   applied to the image separately, and the resulting output images are then
   combined to produce the final edge-detected image.
*/

Mat Picture::sobelFilter(Mat grayImage)
{
	//Sobel X Filter
	double x1[] = { -1.0, 0, 1.0 };
	double x2[] = { -2.0, 0, 2.0 };
	double x3[] = { -1.0, 0, 1.0 };

	vector<vector<double>> xFilter(3);

	xFilter[0].assign(x1, x1 + 3);
	xFilter[1].assign(x2, x2 + 3);
	xFilter[2].assign(x3, x3 + 3);

	//Sobel Y Filter
	double y1[] = { 1.0, 2.0, 1.0 };
	double y2[] = { 0, 0, 0 };
	double y3[] = { -1.0, -2.0, -1.0 };

	vector<vector<double>> yFilter(3);
	yFilter[0].assign(y1, y1 + 3);
	yFilter[1].assign(y2, y2 + 3);
	yFilter[2].assign(y3, y3  + 3);

	//Limit Size
	int size = (int)xFilter.size() / 2;

	Mat filteredImg = Mat((grayImage.rows - 2) * size, (grayImage.cols - 2) * size, CV_8UC1);

	angleMap = Mat((grayImage.rows - 2) * size, (grayImage.cols - 2) * size, CV_32FC1); //AngleMap

	for (int i = size;i < grayImage.rows - size; i++)
	{
		for (int j = size; j < grayImage.cols - size; j++)
		{
			double sumx = 0;
			double sumy = 0;

			for (int x = 0; x < xFilter.size(); x++)
				for (int y = 0; y < yFilter.size(); y++)
				{
					sumx += xFilter[x][y] * (double)(grayImage.at<uchar>(i + x - size, j + y - size)); //Sobel_X Filter Value
					sumy += yFilter[x][y] * (double)(grayImage.at<uchar>(i + x - size, j + y - size)); //Sobel_Y Filter Value
				}
			double sumxsq = sumx * sumx;
			double sumysq = sumy * sumy;

			double sq2 = sqrt(sumxsq + sumysq);

			if (sq2 > 255) //Unsigned Char Fix
				sq2 = 255;
			filteredImg.at<uchar>(i - size, j - size) = sq2;

			if (sumx == 0) //Arctan Fix
				angleMap.at<float>(i - size, j - size) = 90;
			else
				angleMap.at<float>(i - size, j - size) = atan(sumy / sumx);

		}
	}


	return filteredImg;
}

/*
 Applies non-maximum suppression to an image to thin its edges.
 
  Non-maximum suppression is a technique that is commonly used in edge detection algorithms
  to thin the edges in an image. It works by comparing the intensity values of each pixel
  with its neighbors, and suppressing (setting to zero) those pixels that are not local
  maxima along the edge direction. This helps to produce a thin, crisp edge in the output image.
*/

Mat Picture::applyNonMaxSupression(Mat& srcImage)
{
	Mat nonMaxSupped = Mat(srcImage.rows - 2, srcImage.cols - 2, CV_8UC1);
	for (int i = 1; i < angleMap.rows - 1; i++) {
		for (int j = 1; j < angleMap.cols - 1; j++) {
			float Tangent = angleMap.at<float>(i, j);

			nonMaxSupped.at<uchar>(i - 1, j - 1) = srcImage.at<uchar>(i, j);
			//Horizontal Edge
			if (((-22.5 < Tangent) && (Tangent <= 22.5)) || ((157.5 < Tangent) && (Tangent <= -157.5)))
			{
				if ((srcImage.at<uchar>(i, j) <srcImage.at<uchar>(i, j + 1)) || (srcImage.at<uchar>(i, j) < srcImage.at<uchar>(i, j - 1)))
					nonMaxSupped.at<uchar>(i - 1, j - 1) = 0;
			}
			//Vertical Edge
			if (((-112.5 < Tangent) && (Tangent <= -67.5)) || ((67.5 < Tangent) && (Tangent <= 112.5)))
			{
				if ((srcImage.at<uchar>(i, j) < srcImage.at<uchar>(i + 1, j)) || (srcImage.at<uchar>(i, j) < srcImage.at<uchar>(i - 1, j)))
					nonMaxSupped.at<uchar>(i - 1, j - 1) = 0;
			}

			//-45 Degree Edge
			if (((-67.5 < Tangent) && (Tangent <= -22.5)) || ((112.5 < Tangent) && (Tangent <= 157.5)))
			{
				if ((srcImage.at<uchar>(i, j) < srcImage.at<uchar>(i - 1, j + 1)) || (srcImage.at<uchar>(i, j) < srcImage.at<uchar>(i + 1, j - 1)))
					nonMaxSupped.at<uchar>(i - 1, j - 1) = 0;
			}

			//45 Degree Edge
			if (((-157.5 < Tangent) && (Tangent <= -112.5)) || ((22.5 < Tangent) && (Tangent <= 67.5)))
			{
				if ((srcImage.at<uchar>(i, j) < srcImage.at<uchar>(i + 1, j + 1)) || (srcImage.at<uchar>(i, j) < srcImage.at<uchar>(i - 1, j - 1)))
					nonMaxSupped.at<uchar>(i - 1, j - 1) = 0;
			}
		}
	}
	return nonMaxSupped;
}

/*
 
 Applies thresholding to an image to convert it to a binary image.
 
 Thresholding is a process that converts an image into a binary image,
 where each pixel is either black or white, depending on whether it meets
 a certain criterion. This criterion can be based on the intensity value of the pixel,
 or on other properties of the image, such as its gradient or texture.
*/

Mat Picture::threshold(Mat imgin, int low, int high)
{
	if (low > 255)
		low = 255;
	if (high > 255)
		high = 255;

	Mat EdgeMat = Mat(imgin.rows, imgin.cols, imgin.type());

	for (int i = 0; i < imgin.rows; i++)
	{
		for (int j = 0; j < imgin.cols; j++)
		{
			EdgeMat.at<uchar>(i, j) = imgin.at<uchar>(i, j);
			if (EdgeMat.at<uchar>(i, j) > high)
				EdgeMat.at<uchar>(i, j) = 255;
			else if (EdgeMat.at<uchar>(i, j) < low)
				EdgeMat.at<uchar>(i, j) = 0;
			else
			{
				bool anyHigh = false;
				bool anyBetween = false;
				for (int x = i - 1; x < i + 2; x++)
				{
					for (int y = j - 1; y < j + 2; y++)
					{
						if (x <= 0 || y <= 0 || EdgeMat.rows || y > EdgeMat.cols) //Out of bounds
							continue;
						else
						{
							if (EdgeMat.at<uchar>(x, y) > high)
							{
								EdgeMat.at<uchar>(i, j) = 255;
								anyHigh = true;
								break;
							}
							else if (EdgeMat.at<uchar>(x, y) <= high && EdgeMat.at<uchar>(x, y) >= low)
								anyBetween = true;
						}
					}
					if (anyHigh)
						break;
				}
				if (!anyHigh && anyBetween)
					for (int x = i - 2; x < i + 3; x++)
					{
						for (int y = j - 1; y < j + 3; y++)
						{
							if (x < 0 || y < 0 || x > EdgeMat.rows || y > EdgeMat.cols) //Out of bounds
								continue;
							else
							{
								if (EdgeMat.at<uchar>(x, y) > high)
								{
									EdgeMat.at<uchar>(i, j) = 255;
									anyHigh = true;
									break;
								}
							}
						}
						if (anyHigh)
							break;
					}
				if (!anyHigh)
					EdgeMat.at<uchar>(i, j) = 0;
			}
		}
	}
	return EdgeMat;
}

/*
  This function calls out the functions needed to create a perfect edge detected image and 
  returns it for the createMask() function.
*/
Mat Picture::EdgeDetection()
{
	Mat grayscale = CreateGrayScale();
	ShowPicture(_image);

	Mat sFiltered = Mat(sobelFilter(grayscale)); //Sobel Filter

	Mat non = Mat(applyNonMaxSupression(sFiltered));//Non-Maxima Suppression
	Mat final = Mat(threshold(non, 20, 40)); //Double Threshold and Finalize

	ShowPicture(sFiltered);

	ShowPicture(final);

	Mat edges = Mat(final);
	return edges;


}

/*
	Uses various build in or custom made functions in order to produce a mask and cut out the\
	puzzle pieces out of it.
*/
void Picture::CreateMask()
{
	Mat edgeDetection = EdgeDetection();

	int mode = CV_RETR_EXTERNAL;
	int method = CV_CHAIN_APPROX_SIMPLE;

	vector<vector<Point>> BoundaryPoints = findContours(edgeDetection);
	vector<vector<Point>> temp;
	Mat mask = Mat(edgeDetection.size(), edgeDetection.type());

	for (int i = 0; i < BoundaryPoints.size(); i++) {
		mask = 0;
		vector<vector<Point>> temp;
		temp.push_back(BoundaryPoints[i]);
		fillPoly(mask, temp, Scalar(255, 255, 255));
		Scalar Mean = mean(temp[0]);
		Point Center(Point(Mean[0], Mean[1]));

		floodFill(mask, Center, Scalar(255, 255, 255));
		ShowPicture(mask);
		Mat Piece = Mat(bitwise_and_255(mask, i));
		ShowPicture(Piece);

		_pieces.push_back(PuzzlePiece(BoundaryPoints[i], Center, Piece, mask));
	}


}

/*
	Applies bitwise

	I created this custom bitwise function, because topencv built in function only works if the 
	mask has either 0 or one but in my case its 0 and 255. In order for the image to not get its color maximied
	I instead made an empty image and I fill the pixels that are white in the mask into the original image pixels.
*/
Mat Picture::bitwise_and_255(Mat mask, int f)
{

	// create the output Mat object with the same size and data type as the image and the mask
	Mat output = Mat(mask.size(), _image.type());

	// iterate over the pixels in the image and the mask
	for (int i = 0; i < mask.rows; i++)
	{
		for (int j = 0; j < mask.cols; j++)
		{



			if (mask.at<uchar>(i, j) == 255)
			{
				output.at<Vec3b>(i, j) = _image.at<Vec3b>(i + 2, j + 2);// I add two pixels because the sobel filter decreases 2.
			}

		}
	}


	return output;
}



/*
	
	This function converts the image into a grayscale.

	Im using a method that's called "lum grayscale". I could have just averaged the RGB in the image
	but this grayscale looks better, and I gotta take any kind of improvement.

	This method uses three main equations the first one is called "gamma-expansion".
	basically it converts from a non linear form that image files are often stored in to the linear form, 
	which is what we wanna work with because thats just the linear(RED, GREEN, BLUE) channel values.
	But we dont ectually need to use it cause theres a much easier one that works about the same way.

	Y = 0.2126R + 0.7152G  + 0.0722B

	We dont need to use the last equation because STB images already support convertion to non linear images.

*/
Mat Picture::CreateGrayScale()
{
	Mat grayscaled = Mat(_image.rows, _image.cols, CV_8UC1); //To one channel
	for (int i = 0; i < _image.rows; i++)
		for (int j = 0; j < _image.cols; j++)
		{
			int b = _image.at<Vec3b>(i, j)[0];
			int g = _image.at<Vec3b>(i, j)[1];
			int r = _image.at<Vec3b>(i, j)[2];

			double newValue = (r * 0.2126 + g * 0.7152 + b * 0.0722);
			grayscaled.at<uchar>(i, j) = newValue;

		}
	return grayscaled;
}




/*
	returns a vector of contours in the image.

	This function works by the moore tracing algorithm.
	It searches for neighbour pixels that are also white and adds them
	to the contour. The only problem with this is that the contour has to be connected 
	so if its a bad image this wont work.

*/
vector<vector<Point>> Picture::findContours(Mat grid)
{

	// Keep track of the visited pixels to avoid processing them multiple times.
	vector<vector<bool>> visited(grid.rows, vector<bool>(grid.cols));

	// Keep track of the filled contours.
	vector<vector<Point>> contours;

	// Iterate over all the pixels in the image.
	for (int y = 0; y < grid.rows; ++y) {
		for (int x = 0; x < (grid.cols); ++x) {
			if (visited[y][x] || grid.at<uchar>(y, x) == 0) continue;  // Skip visited pixels or background pixels.

			// Start a new contour. This is the moment we found a seed point
			vector<Point> contour;
			stack<Point> stack;

			// Push the seed point onto the stack and mark it as visited.
			Point seed = { x, y };
			stack.push(seed);
			visited[y][x] = true;

			// Flood fill the contour.
			while (!stack.empty()) {
				Point p = stack.top();
				stack.pop();

				// Add the current point to the contour.
				contour.push_back(p);

				// Check the neighbors of the current point.
				for (const Point& neighbor : neighbors(p)) {
					if (neighbor.x < 0 || neighbor.x >= grid.cols ||  // Skip out-of-bounds pixels.
						neighbor.y < 0 || neighbor.y >= grid.rows ||
						visited[neighbor.y][neighbor.x] ||  // Skip visited pixels.
						grid.at<uchar>(neighbor.y,neighbor.x) == 0)
						continue; // Skip background pixels.

					stack.push(neighbor);
					visited[neighbor.y][neighbor.x] = true;
				}
			}
			if (contour.front() != contour.back() && contour.size() > 50)// getting rid of bad contours
			{

				// Add the filled contour to the output.
				contours.push_back(contour);
			}
		}
	}
	return contours;
	
}










