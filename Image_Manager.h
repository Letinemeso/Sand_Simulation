#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include <string>
#include <fstream>

#include "BMP_Image.h"


class Image_Manager final
{
private:


public:
	Image_Manager(){ }
	~Image_Manager(){ }

public:
	BMP_Image* load_bmp(const std::string& _path);
	void save_bmp(const BMP_Image* _img, const std::string& _path);

};


#endif // IMAGE_MANAGER_H
