#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#include "Utility.h"


class BMP_Image final
{
public:
	struct Pixel
	{
		unsigned char& red;
		unsigned char& green;
		unsigned char& blue;
		Pixel(unsigned char& _red, unsigned char& _green, unsigned char& _blue) : red(_red), green(_green), blue(_blue) { }
	};

public:
	enum Data_Positions
	{
		BMP_mark = 0,
		file_size = 2,
		pixel_array_offset = 10,
		header_size = 14,
		image_width = 18,
		image_height = 22,
		planes = 26,
		bits_per_pixel = 28,
		compression = 30,
		pixel_array_size = 34,
		pixels_per_meter_x = 38,
		pixels_per_meter_y = 42,
	};

private:
	unsigned char* m_raw_data = nullptr;
	unsigned int m_size = 0;

private:
	unsigned int m_pixel_array_offset = 0;
	unsigned int m_width = 0, m_height = 0;
	unsigned int m_pixel_array_size = 0;
	unsigned int m_padding_size = 0;

public:
	BMP_Image();
	~BMP_Image();

public:
	void use_data(unsigned char*& _raw_data, unsigned int& _size);
	void load_data(unsigned char* _raw_data, unsigned int _size);
	void generate(unsigned int _width, unsigned int _height);

public:
	Pixel pixel(unsigned int _x, unsigned int _y);
	unsigned int size() const;
	const unsigned char* raw_data() const;
	unsigned int width() const;
	unsigned int height() const;

private:
	unsigned int get_pixel_index_in_array(unsigned int _x, unsigned int _y) const;

};


#endif // BMP_IMAGE_H
