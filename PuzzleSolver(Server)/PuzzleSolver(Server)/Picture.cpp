#include "Picture.h"

Picture::Picture(string link)
{
	_image = imread(link);
	ResizeCanvas();
	CreateGrayScale();
}

void Picture::ShowPicture() // Function for chwecking how the image looks.
{
	imshow("image", _image);
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
void Picture::CreateGrayScale()
{
	for (int i = 0; i < _image.size().area() * 3; i += _image.channels())
	{
		int gray = 0.2126 * _image.data[i] + 0.7152 * _image.data[i + 1] + 0.0722 * _image.data[i + 2]; // Grayscale using the grayscale lum method.
		memset(_image.data + i, gray, 3);
	}
}

