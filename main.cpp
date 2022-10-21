#include <iostream>
#include <fstream>
#include <ctime>

#include "Utility.h"
#include "BMP_Image.h"
#include "Image_Manager.h"
#include "Sand_Simulation.h"


int main()
{
	srand(time(nullptr));

	Image_Manager im;

//	BMP_Image* image = im.load_bmp("input");
//	BMP_Image* image = im.load_bmp("test");
//	BMP_Image* image = im.load_bmp("100x100");
	BMP_Image* image = im.load_bmp("coffee");
//	BMP_Image* image = im.load_bmp("hotdog");


	if(image == nullptr)
	{
		std::cout << "error\n";
		return 1;
	}


	Sand_Simulation ss(image);

	std::string file_name = "test_";
	BMP_Image* scaled = im.scale_bmp(image, 1);
	im.save_bmp(scaled, "Simulation/" + file_name + std::to_string(0));
	delete image;
	delete scaled;

	unsigned int iteration = 0;
	while(!ss.stable())
	{
		ss.update();
		++iteration;

		BMP_Image* ss_output = ss.state();

		scaled = im.scale_bmp(ss_output, 1);
		im.save_bmp(scaled, "Simulation/" + file_name + std::to_string(iteration));

//		im.save_bmp(ss_output, "Simulation/" + file_name + std::to_string(iteration));

		delete ss_output;
		delete scaled;
	}




//	for(unsigned int j=0; j<image->height(); ++j)
//	{
//		for(unsigned int i=0; i<image->width(); ++i)
//		{
//			bool need_to_paint = Utility::limited_rand(0, 1);
//			if(!need_to_paint)
//				continue;

//			BMP_Image::Pixel pixel = image->pixel(i, j);

//			unsigned int darkness = Utility::limited_rand(0, 125);

//			pixel.red = Utility::limited_rand(250, 255) - darkness;
//			pixel.green = Utility::limited_rand(250, 255) - darkness;
//			pixel.blue = Utility::limited_rand(40, 60);
//		}
//	}

	return 0;
}
