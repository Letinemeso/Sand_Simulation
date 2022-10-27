#include <iostream>
#include <fstream>
#include <ctime>

#include "Utility.h"
#include "BMP_Image.h"
#include "Image_Manager.h"
#include "Sand_Simulation.h"

#include "Args_Parser.h"


int main(int args_count, char** args)
{
	srand(time(nullptr));

	Image_Manager im;

//	std::string args_test = "-v 12 --arg 123 --alalala lala -r 9";

	std::string args_test;
	for(int i=0; i<args_count; ++i)
	{
		args_test.append(args[i]);
		args_test += ' ';
	}

	Args_Parser ap;

	std::map<std::string, std::string> args_parsed = ap.parse(args_test);

	//	getting information

	//	width

	std::map<std::string, std::string>::iterator it = args_parsed.find("-l");
	if(it == args_parsed.end())
	{
		it = args_parsed.find("--length");
		if(it == args_parsed.end())
		{
			std::cout << "-l or --length is not found!\n";
			return 1;
		}
	}

	unsigned int width = std::stoi(it->second);

	//	height

	it = args_parsed.find("-w");
	if(it == args_parsed.end())
	{
		it = args_parsed.find("--width");
		if(it == args_parsed.end())
		{
			std::cout << "-w or --width is not found!\n";
			return 1;
		}
	}

	unsigned int height = std::stoi(it->second);

	//	input

	it = args_parsed.find("-i");
	if(it == args_parsed.end())
	{
		it = args_parsed.find("--input");
		if(it == args_parsed.end())
		{
			std::cout << "-i or --input is not found!\n";
			return 1;
		}
	}

	std::string input_path = it->second;

	//	output

	it = args_parsed.find("-o");
	if(it == args_parsed.end())
	{
		it = args_parsed.find("--output");
		if(it == args_parsed.end())
		{
			std::cout << "-o or --output is not found!\n";
			return 1;
		}
	}

	std::string output_path = it->second;

	//	max iterations

	it = args_parsed.find("-m");
	if(it == args_parsed.end())
	{
		it = args_parsed.find("--max-iter");
		if(it == args_parsed.end())
		{
			std::cout << "-m or --max-iter is not found!\n";
			return 1;
		}
	}

	unsigned int max_iterations = std::stoi(it->second);

	//	frequency

	it = args_parsed.find("-f");
	if(it == args_parsed.end())
	{
		it = args_parsed.find("--freq");
		if(it == args_parsed.end())
		{
			std::cout << "-f or --freq is not found!\n";
			return 1;
		}
	}

	unsigned int frequency = std::stoi(it->second);






	std::string file_name = "test_";


	Sand_Simulation ss(5, 5);
	ss.setup_from_file(input_path);

//	ss.set_grains_in_column(1, 2, 1);
//	ss.set_grains_in_column(2, 2, 100);
//	ss.set_grains_in_column(3, 2, 100);
//	ss.set_grains_in_column(2, 1, 1);
//	ss.set_grains_in_column(2, 3, 1);

	BMP_Image* ss_output = ss.state();

	BMP_Image* scaled = im.scale_bmp(ss_output, 50);
	im.save_bmp(scaled, "Simulation/" + file_name + std::to_string(0));

	delete ss_output;
	delete scaled;
//	BMP_Image* scaled = im.scale_bmp(image, 1);
//	im.save_bmp(scaled, "Simulation/" + file_name + std::to_string(0));
//	delete image;
//	delete scaled;

	unsigned int iteration = 0;
	while(!ss.stable())
	{
		ss.update();
		++iteration;

		ss_output = ss.state();

		scaled = im.scale_bmp(ss_output, 50);
		im.save_bmp(scaled, "Simulation/" + file_name + std::to_string(iteration));

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
