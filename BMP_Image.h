#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H


class BMP_Image final
{
public:
	enum Data_Positions
	{
		BMP_mark = 0,
		file_size = 2,
		pixel_map_offset = 10
	};

private:
	unsigned char* m_data = nullptr;
	unsigned int m_size = 0;

public:
	BMP_Image();
	~BMP_Image();

public:
	void load_data(unsigned char* m_data)

};


#endif // BMP_IMAGE_H
