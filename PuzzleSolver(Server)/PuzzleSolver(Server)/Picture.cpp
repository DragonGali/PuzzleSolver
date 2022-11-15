#include "Picture.h"

Picture::Picture(string link)
{
	_image = imread(link);
}

void Picture::ShowPicture()
{
	imshow("image", _image);
}

void Picture::ResizeCanvas()
{
	resize(_image, _image, cvSize(320, 200));
}

