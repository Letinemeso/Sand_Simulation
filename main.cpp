#include <iostream>
#include <fstream>

class BMP_Manager
{
private:


public:


};

int main()
{
	std::ifstream file("test.bmp", std::ios::in);

	if(!file.is_open())
	{
		std::cout << "error\n";
		return 1;
	}

	file.seekg(0, std::ios::end);
	unsigned int size = file.tellg();
	file.seekg(0, std::ios::beg);

	unsigned char* content = new unsigned char[size];

	for(unsigned int i=0; i<size; ++i)
		content[i] = file.get();

	file.close();

	unsigned int index = 0;
	for(unsigned int i=0; i<size; ++i)
	{
		if(content[i] == 255)
		{
			index = i;
			break;
		}
	}

	for(unsigned int i=0; i<size; ++i)
		std::cout << (unsigned int)content[i] << "\n";

	delete[] content;

	return 0;
}
