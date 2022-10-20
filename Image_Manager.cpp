#include "Image_Manager.h"


BMP_Image* Image_Manager::load_bmp(const std::string &_path)
{
	std::ifstream input(_path + ".bmp", std::ios::in);
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
	std::ofstream output(_path + ".bmp", std::ios::trunc);
	for(unsigned int i=0; i<_img->size(); ++i)
		output << _img->raw_data()[i];
	output.close();
}



BMP_Image* Image_Manager::scale_bmp(const BMP_Image *_img, unsigned int _scale)
{
	if(_scale == 0)
		return nullptr;

	if(_scale == 1)
		return new BMP_Image(*_img);

	BMP_Image* result = new BMP_Image;
	result->generate(_img->width() * _scale, _img->height() * _scale);

	for(unsigned int x = 0; x < _img->width(); ++x)
	{
		for(unsigned int y = 0; y < _img->height(); ++y)
		{
			BMP_Image::Const_Pixel px = _img->pixel(x, y);

			for(unsigned int xscaled = x * _scale; xscaled < (x + 1) * _scale; ++xscaled)
			{
				for(unsigned int yscaled = y * _scale; yscaled < (y + 1) * _scale; ++yscaled)
				{
					BMP_Image::Pixel px_scaled = result->pixel(xscaled, yscaled);

					px_scaled.red = px.red;
					px_scaled.green = px.green;
					px_scaled.blue = px.blue;
				}
			}
		}
	}

	return result;
}
