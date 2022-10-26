#include "Sand_Simulation.h"


Sand_Simulation::Sand_Simulation(unsigned int _width, unsigned int _height)
{
	m_width = _width;
	m_height = _height;

	m_grid = new unsigned int * [m_width];
	for(unsigned int i = 0; i < m_width; ++i)
	{
		m_grid[i] = new unsigned int[m_height];
		for(unsigned int j=0; j< m_height; ++j)
			m_grid[i][j] = 0;
	}
}

Sand_Simulation::~Sand_Simulation()
{
	if(m_grid == nullptr)
		return;

	for(unsigned int i = 0; i < m_width; ++i)
		delete[] m_grid[i];
	delete[] m_grid;
}


void Sand_Simulation::set_grains_in_column(unsigned int _x, unsigned int _y, unsigned int _value)
{
	if(_x >= m_width || _y >= m_height)
		return;
	m_grid[_x][_y] = _value;
}

#include <iostream>

void Sand_Simulation::update()
{
	m_stable = true;

	unsigned int** temp_grid = new unsigned int * [m_width];
	for(unsigned int i = 0; i < m_width; ++i)
	{
		temp_grid[i] = new unsigned int[m_height];
		for(unsigned int j=0; j< m_height; ++j)
			temp_grid[i][j] = 0;
	}


	for(int y = 0; y < (int)m_height; ++y)
	{
		for(int x = 0; x < (int)m_width; ++x)
		{
			unsigned int current_count = m_grid[x][y];

			if(grain_can_slide_here(x - 1, y, current_count))
			{
				++temp_grid[x - 1][y];
				--current_count;
				m_stable = false;
			}
			if(grain_can_slide_here(x + 1, y, current_count))
			{
				++temp_grid[x + 1][y];
				--current_count;
				m_stable = false;
			}
			if(grain_can_slide_here(x, y - 1, current_count))
			{
				++temp_grid[x][y - 1];
				--current_count;
				m_stable = false;
			}
			if(grain_can_slide_here(x, y + 1, current_count))
			{
				++temp_grid[x][y + 1];
				--current_count;
				m_stable = false;
			}

			temp_grid[x][y] += current_count;
		}
	}

	for(unsigned int i = 0; i < m_width; ++i)
		delete[] m_grid[i];
	delete[] m_grid;

	m_grid = temp_grid;


	//	debug

	unsigned int total_count = 0;

	for(int y = (int)m_height - 1; y >= 0; --y)
	{
		for(int x = 0; x < (int)m_width; ++x)
		{
			unsigned int current_count = m_grid[x][y];

			std::cout << current_count << "\t";

			total_count += current_count;
		}

		std::cout << "\n\n";
	}

	std::cout << "\n\n";
}



bool Sand_Simulation::grain_can_slide_here(int _where_x, int _where_y, unsigned int _relative_to)
{
	if(_where_x < 0 || _where_y < 0 || _where_x >= (int)m_width || _where_y >= (int)m_height)
		return false;

	if(_relative_to < 4)
		return false;

	if(m_grid[_where_x][_where_y] <= _relative_to - 4)
		return true;

	return false;

//	return _relative_to >= 4;
}



bool Sand_Simulation::stable() const
{
	return m_stable;
}

BMP_Image* Sand_Simulation::state() const
{
	BMP_Image* img = new BMP_Image;
	img->generate(m_width, m_height);

	for(unsigned int x = 0; x < m_width; ++x)
	{
		for(unsigned int y = 0; y < m_height; ++y)
		{
			BMP_Image::Pixel px = img->pixel(x, y);

			if(m_grid[x][y] == 0)
			{
				px.red = 255;
				px.green = 255;
				px.blue = 255;
			}
			else if(m_grid[x][y] == 1)
			{
				px.red = 0;
				px.green = 255;
				px.blue = 0;
			}
			else if(m_grid[x][y] == 2)
			{
				px.red = 125;
				px.green = 0;
				px.blue = 255;
			}
			else if(m_grid[x][y] == 3)
			{
				px.red = 255;
				px.green = 255;
				px.blue = 0;
			}
			else
			{
				px.red = 0;
				px.green = 0;
				px.blue = 0;
			}
		}
	}

	return img;
}
