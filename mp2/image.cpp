#include "image.h"
#include "rgbapixel.h"
#include <cstdint>

void Image::flipleft()
{
	RGBAPixel* left;
	RGBAPixel* right;
	RGBAPixel* temp = new RGBAPixel();
	int width = (*this).width();
	int height = (*this).height();
	for(int i=0; i< (width/2);i++)
	{
		for(int j = 0; j< height;j++)
		{
			left = (*this).operator()(i,j);
			right = (*this).operator()(width-i-1,j);
			*temp = *left;
			*left = *right;
			*right = *temp;
		}
	}
	delete temp;
}


void Image:: adjustbrightness (int r, int g, int b)
{
	RGBAPixel* temp;
	int width = (*this).width();
	int height = (*this).height();
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			temp = (*this)(i,j);
			if(temp->red+r > 255)
			{
				temp->red = 255;
			}
			else if(temp->red+r < 0)
			{
				temp->red = 0;
			}
			else
			{
				temp->red += r;
			}

			if(temp->blue+b > 255)
			{
				temp->blue = 255;
			}
			else if (temp->blue+b < 0)
			{
				temp->blue = 0;
			}
			else
			{
				temp->blue += b;
			}

			if(temp->green+g > 255)
			{
				temp->green = 255;
			}
			else if (temp->green+g < 0)
			{
				temp->green = 0;
			}
			else
			{
				temp->green += g;
			}
		}
	}
}

void Image::invertcolors()
{
	RGBAPixel *temp;
	int width = (*this).width();
	int height = (*this).height();
	for(int i=0; i < width; i++)
	{
		for(int j=0; j < height; j++)
		{
			temp = (*this).operator()(i,j);
			temp->red = 255 - temp->red;
			temp->green = 255 - temp->green;
			temp->blue = 255 - temp->blue;
		}
	}
}
