#include "BMP_Image.h"


BMP_Image::BMP_Image()
{

}

BMP_Image::BMP_Image(const BMP_Image& _other)
{
	m_size = _other.m_size;
	m_raw_data = new unsigned char[m_size];
	for(unsigned int i = 0; i < m_size; ++i)
		m_raw_data[i] = _other.m_raw_data[i];

	m_pixel_array_offset = _other.m_pixel_array_offset;
	m_width = _other.m_width;
	m_height = _other.m_height;
	m_pixel_array_size = _other.m_pixel_array_size;
	m_padding_size = _other.m_padding_size;
}

BMP_Image::BMP_Image(BMP_Image&& _other)
{
	m_size = _other.m_size;
	_other.m_size = 0;
	m_raw_data = _other.m_raw_data;
	_other.m_raw_data = nullptr;

	m_pixel_array_offset = _other.m_pixel_array_offset;
	_other.m_pixel_array_offset = 0;
	m_width = _other.m_width;
	_other.m_width = 0;
	m_height = _other.m_height;
	_other.m_height = 0;
	m_pixel_array_size = _other.m_pixel_array_size;
	_other.m_pixel_array_size = 0;
	m_padding_size = _other.m_padding_size;
	_other.m_padding_size = 0;
}

BMP_Image::~BMP_Image()
{
	delete[] m_raw_data;
}

void BMP_Image::use_data(unsigned char*& _raw_data, unsigned int& _size)
{
	delete[] m_raw_data;

	m_size = _size;
	m_raw_data = new unsigned char[m_size];
	for(unsigned int i=0; i<m_size; ++i)
		m_raw_data[i] = _raw_data[i];

	_raw_data = nullptr;
	_size = 0;

	m_pixel_array_offset = Utility::get_int_from_char_array(&(m_raw_data[Data_Positions::pixel_array_offset]), 4);
	m_width = Utility::get_int_from_char_array(&(m_raw_data[Data_Positions::image_width]), 4);
	m_height = Utility::get_int_from_char_array(&(m_raw_data[Data_Positions::image_height]), 4);
	m_pixel_array_size = Utility::get_int_from_char_array(&(m_raw_data[Data_Positions::pixel_array_size]), 4);

	m_padding_size = (m_pixel_array_size - (m_width * m_height * 3)) / m_height;
}

void BMP_Image::load_data(unsigned char* _raw_data, unsigned int _size)
{
	delete[] m_raw_data;

	m_size = _size;
	m_raw_data = new unsigned char[m_size];
	for(unsigned int i=0; i<m_size; ++i)
		m_raw_data[i] = _raw_data[i];

	m_pixel_array_offset = Utility::get_int_from_char_array(&(m_raw_data[Data_Positions::pixel_array_offset]), 4);
	m_width = Utility::get_int_from_char_array(&(m_raw_data[Data_Positions::image_width]), 4);
	m_height = Utility::get_int_from_char_array(&(m_raw_data[Data_Positions::image_height]), 4);
	m_pixel_array_size = Utility::get_int_from_char_array(&(m_raw_data[Data_Positions::pixel_array_size]), 4);

	m_padding_size = 4 - (m_width % 3);
	if(m_padding_size == 4)
		m_padding_size = 0;
}

void BMP_Image::generate(unsigned int _width, unsigned int _height)
{
	delete[] m_raw_data;

	m_width = _width;
	m_height = _height;

	m_padding_size = /*4 - */(m_width % 4);
//	if(m_padding_size == 4)
//		m_padding_size = 0;

	m_pixel_array_size = ((3 * m_width) + m_padding_size) * m_height;
	m_pixel_array_offset = 122;
	m_size = m_pixel_array_size + m_pixel_array_offset;
	unsigned int header_size = m_pixel_array_offset - 14;

	m_raw_data = new unsigned char[m_size];
	for(unsigned int i=0; i<m_size; ++i)
		m_raw_data[i] = 0;

	m_raw_data[0] = 'B';
	m_raw_data[1] = 'M';

	Utility::set_char_array_from_int(&m_raw_data[Data_Positions::file_size], m_size, 4);
	Utility::set_char_array_from_int(&m_raw_data[Data_Positions::pixel_array_offset], m_pixel_array_offset, 4);
	Utility::set_char_array_from_int(&m_raw_data[Data_Positions::header_size], header_size, 4);
	Utility::set_char_array_from_int(&m_raw_data[Data_Positions::image_width], m_width, 4);
	Utility::set_char_array_from_int(&m_raw_data[Data_Positions::image_height], m_height, 4);
	Utility::set_char_array_from_int(&m_raw_data[Data_Positions::planes], 1, 2);
	Utility::set_char_array_from_int(&m_raw_data[Data_Positions::bits_per_pixel], 24, 2);
	Utility::set_char_array_from_int(&m_raw_data[Data_Positions::pixel_array_size], m_pixel_array_size, 4);
	Utility::set_char_array_from_int(&m_raw_data[Data_Positions::pixels_per_meter_x], 11811, 4);
	Utility::set_char_array_from_int(&m_raw_data[Data_Positions::pixels_per_meter_y], 11811, 4);

	for(unsigned int x = 0; x < m_width; ++x)
	{
		for(unsigned int y = 0; y < m_height; ++y)
		{
			Pixel px = pixel(x, y);
			px.red = 255;
			px.blue = 255;
			px.green = 255;
		}
	}
}



BMP_Image::Pixel BMP_Image::pixel(unsigned int _x, unsigned int _y)
{
	unsigned int offset = get_pixel_index_in_array(_x, _y);

	return Pixel(m_raw_data[offset + 2], m_raw_data[offset + 1], m_raw_data[offset + 0]);
}

BMP_Image::Const_Pixel BMP_Image::pixel(unsigned int _x, unsigned int _y) const
{
	unsigned int offset = get_pixel_index_in_array(_x, _y);

	return Const_Pixel(m_raw_data[offset + 2], m_raw_data[offset + 1], m_raw_data[offset + 0]);
}

unsigned int BMP_Image::size() const
{
	return m_size;
}

const unsigned char* BMP_Image::raw_data() const
{
	return m_raw_data;
}

unsigned int BMP_Image::width() const
{
	return m_width;
}

unsigned int BMP_Image::height() const
{
	return m_height;
}



unsigned int BMP_Image::get_pixel_index_in_array(unsigned int _x, unsigned int _y) const
{
	return (_y * (m_width * 3 + m_padding_size)) + (_x * 3) + m_pixel_array_offset;
}
