#ifndef SAND_SIMULATION_H
#define SAND_SIMULATION_H

#include <cmath>

#include "Image_Manager.h"
#include "BMP_Image.h"


class Sand_Simulation final
{
private:
	unsigned int** m_grid = nullptr;

	unsigned int m_width = 0;
	unsigned int m_height = 0;

private:
	bool m_stable = false;

public:
	Sand_Simulation(unsigned int _width, unsigned int _height);
	~Sand_Simulation();

	void set_grains_in_column(unsigned int _x, unsigned int _y, unsigned int _value);
	void setup_from_file(const std::string& _path);

public:
	void update();

private:
	bool grain_can_slide_here(int _where_x, int _where_y, unsigned int _relative_to);

public:
	bool stable() const;
	BMP_Image state() const;

};

#endif // SAND_SIMULATION_H
