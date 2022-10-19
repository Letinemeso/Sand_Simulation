#include "BMP_Image.h"


BMP_Image::BMP_Image()
{

}

BMP_Image::~BMP_Image()
{
	delete[] m_data;
}



void BMP_Image::load_data(unsigned char* _data, unsigned int _size)
{
	delete[] m_data;

	m_size = _size;
	m_data = new unsigned char[m_size];
	for(unsigned int i=0; i<m_size; ++i)
		m_data[i] = _data[i];
}
