#include "rgbapixel.h"

#include <cstdint>

using std::uint8_t;


//RGBAPixel default constructor
RGBAPixel::RGBAPixel()
{
	red = 255;
	green = 255;
	blue = 255;
	alpha = 255;
}

//RGBAPixel rgb constructor
RGBAPixel::RGBAPixel(uint8_t r, uint8_t g, uint8_t b)
{
	red = r;
	blue = b;
	green = g;
	alpha = 255;
}