#include <iostream>
#include <fstream>

#include "Utility.h"
#include "BMP_Image.h"
#include "Image_Manager.h"

class BMP_Manager
{
private:


public:


};

int main()
{
	Image_Manager im;

//	BMP_Image* image = im.load_bmp("test_black_3x3.bmp");
	BMP_Image* image = im.load_bmp("output.bmp");
//	BMP_Image* image = new BMP_Image;
//	image->generate(3, 2);

	BMP_Image* real_image = im.load_bmp("test_wide.bmp");

	for(unsigned int i=0; i<image->size(); ++i)
	{
		std::cout << (unsigned int)image->raw_data()[i] << "\t" << (unsigned int)real_image->raw_data()[i] << "\n";
	}


	if(image == nullptr)
	{
		std::cout << "error\n";
		return 1;
	}

	for(unsigned int j=0; j<image->height(); ++j)
	{
		for(unsigned int i=0; i<image->width(); ++i)
		{
			BMP_Image::Pixel pixel = image->pixel(i, j);

			std::cout << "x: " << i << "\ty: " << j << "\n" << (unsigned int)pixel.red << " " << (unsigned int)pixel.green << " " << (unsigned int)pixel.blue << '\n';
		}
	}

	BMP_Image::Pixel pixel = image->pixel(0, 2);
	pixel.red = 128;
	pixel.green = 0;
	pixel.blue = 255;

	im.save_bmp(image, "output.bmp");

	delete image;

	return 0;
}
