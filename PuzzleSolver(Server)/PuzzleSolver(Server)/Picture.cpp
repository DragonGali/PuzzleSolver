#include "Picture.h"

Picture::Picture(string link)
{
	_image = imread(link);
}

