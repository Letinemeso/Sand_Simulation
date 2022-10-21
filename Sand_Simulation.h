#ifndef SAND_SIMULATION_H
#define SAND_SIMULATION_H

#include "Image_Manager.h"
#include "BMP_Image.h"


struct Grain final
{
	unsigned char red = 255;
	unsigned char green = 255;
	unsigned char blue = 255;

	bool is_empty() const { return red == 255 && green == 255 && blue == 255; }
	void set_empty() { red = 255; green = 255; blue = 255; }
};

class Sand_Simulation final
{
private:
	Grain** m_grid = nullptr;
	unsigned int m_width = 0;
	unsigned int m_height = 0;

private:
	bool m_stable = false;

public:
	Sand_Simulation(const BMP_Image* _initial_state);
	~Sand_Simulation();

public:
	void update();

private:
	void remove_grain(int _fx, int _fy);
	void move_grain(int _fx, int _fy, int _tx, int _ty);
	void lower_grain_column(int _x, int _fy);
	bool is_stable_below(int _x, int _y) const;
	bool is_stable_left(int _x, int _y) const;
	bool is_stable_right(int _x, int _y) const;

public:
	bool stable() const;
	BMP_Image* state() const;

};

#endif // SAND_SIMULATION_H
