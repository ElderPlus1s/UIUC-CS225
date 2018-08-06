#include "png.h"

int main()
{
	PNG input = PNG("in.png");
	int width = input.width();
	int height = input.height();
	PNG output = PNG(input.width(), input.height());
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			RGBAPixel i = *input(width-1-x,height-1-y);
			output(x,y)->red = i.red;
			output(x,y)->green = i.green;
			output(x,y)->blue = i.blue;
			output(x,y)->alpha = i.alpha;
		}
	}
	output.writeToFile("out.png");
	
	return 0;
}