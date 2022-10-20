#include "Image_Manager.h"


BMP_Image* Image_Manager::load_bmp(const std::string &_path)
{
	std::ifstream input(_path, std::ios::in);
	if(!input.is_open())
		return nullptr;

	input.seekg(0, std::ios::end);
	unsigned int size = input.tellg();
	input.seekg(0, std::ios::beg);

	unsigned char* content = new unsigned char[size];

	for(unsigned int i=0; i<size; ++i)
		content[i] = input.get();

	input.close();

	BMP_Image* result = new BMP_Image;
	result->use_data(content, size);
	return result;
}

void Image_Manager::save_bmp(const BMP_Image *_img, const std::string &_path)
{
	std::ofstream output(_path, std::ios::trunc);
	for(unsigned int i=0; i<_img->size(); ++i)
		output << _img->raw_data()[i];
	output.close();
}
