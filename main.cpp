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
	Image_Manager im;

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

	unsigned int max_iterations = 0;

	it = args_parsed.find("-m");
	if(it == args_parsed.end())
	{
		it = args_parsed.find("--max-iter");
		if(it == args_parsed.end())
			max_iterations = -1;
		else
			max_iterations = std::stoi(it->second);
	}
	else
	{
		max_iterations = std::stoi(it->second);
	}

	if(max_iterations == 0)
		max_iterations = -1;

	//	frequency

	unsigned int frequency = 0;

	it = args_parsed.find("-f");
	if(it == args_parsed.end())
	{
		it = args_parsed.find("--freq");
		if(it == args_parsed.end())
			frequency = 1;
		else
			frequency = std::stoi(it->second);
	}
	else
	{
		frequency = std::stoi(it->second);
	}

	//


	std::string file_name = "sand_";

	Sand_Simulation ss(width, height);
	ss.setup_from_file(input_path);

	if(frequency == 0)
	{
		for(unsigned int i=0; i < max_iterations && !ss.stable(); ++i)
			ss.update();

		BMP_Image* ss_output = ss.state();

		im.save_bmp(ss_output, output_path + '/' + file_name + "final");

		delete ss_output;

		return 0;
	}

	for(unsigned int i=0; i < max_iterations && !ss.stable(); ++i)
	{
		if(i % frequency == 0)
		{
			BMP_Image* ss_output = ss.state();

			im.save_bmp(ss_output, output_path + '/' + file_name + std::to_string(i));

			delete ss_output;
		}

		ss.update();
	}

	return 0;
}
