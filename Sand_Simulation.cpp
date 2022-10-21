#include "Sand_Simulation.h"


Sand_Simulation::Sand_Simulation(const BMP_Image* _initial_state)
{
	m_width = _initial_state->width();
	m_height = _initial_state->height();

	m_grid = new Grain * [m_width];
	for(unsigned int i = 0; i < m_width; ++i)
		m_grid[i] = new Grain[m_height];

	for(unsigned int x = 0; x < m_width; ++x)
	{
		for(unsigned int y = 0; y < m_height; ++y)
		{
			BMP_Image::Const_Pixel px = _initial_state->pixel(x, y);

			m_grid[x][y].red = px.red;
			m_grid[x][y].green = px.green;
			m_grid[x][y].blue = px.blue;
		}
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



void Sand_Simulation::update()
{
	m_stable = true;

	for(unsigned int y = 0; y < m_height; ++y)
	{
		for(unsigned int x = 0; x < m_width; ++x)
		{
			if(m_grid[x][y].is_empty())
				continue;

			if(!is_stable_below(x, y))
			{
				move_grain(x, y, x, y - 1);
				continue;
			}

			bool sleft = is_stable_left(x, y);
			bool sright = is_stable_right(x, y);

			if(sleft && sright)
				continue;

			if(!sleft && !sright)
			{
				bool move_left = Utility::limited_rand(0, 1);
				if(move_left)
					move_grain(x, y, x - 1, y - 1);
				else
					move_grain(x, y, x + 1, y - 1);
			}
			else if(sleft && !sright)
			{
				move_grain(x, y, x + 1, y - 1);
			}
			else if(!sleft && sright)
			{
				move_grain(x, y, x - 1, y - 1);
			}

			lower_grain_column(x, y + 1);
		}
	}
}



void Sand_Simulation::remove_grain(int _fx, int _fy)
{
	m_stable = false;

	m_grid[_fx][_fy].set_empty();
}

void Sand_Simulation::move_grain(int _fx, int _fy, int _tx, int _ty)
{
	if(_tx >= 0 && _tx < (int)m_width && _ty >= 0 && _ty < (int)m_height)
		m_grid[_tx][_ty] = m_grid[_fx][_fy];
	remove_grain(_fx, _fy);
}

void Sand_Simulation::lower_grain_column(int _x, int _fy)
{
	int y = _fy;
	while(!m_grid[_x][y].is_empty() && y < (int)m_height)
	{
		bool sleft = is_stable_left(_x, y);
		bool sright = is_stable_right(_x, y);

		if(sleft && sright)
		{
			++y;
			continue;
		}

		if(!sleft && !sright)
		{
			bool move_left = Utility::limited_rand(0, 1);
			if(move_left)
				move_grain(_x, y, _x - 1, y - 1);
			else
				move_grain(_x, y, _x + 1, y - 1);
		}
		else if(sleft && !sright)
		{
			move_grain(_x, y, _x + 1, y - 1);
		}
		else if(!sleft && sright)
		{
			move_grain(_x, y, _x - 1, y - 1);
		}

		++y;
	}
	remove_grain(_x, y - 1);
}

bool Sand_Simulation::is_stable_below(int _x, int _y) const
{
	if(_y == 0)
		return true;

	if(!m_grid[_x][_y - 1].is_empty())
		return true;

	return false;
}

bool Sand_Simulation::is_stable_left(int _x, int _y) const
{
	if(_y == 0)
		return true;

	if(_x == 0)
		return false;

	if(!m_grid[_x - 1][_y].is_empty())
		return true;

	if(!m_grid[_x - 1][_y - 1].is_empty())
		return true;

	return false;
}

bool Sand_Simulation::is_stable_right(int _x, int _y) const
{
	if(_y == 0)
		return true;

	if(_x == (int)m_width - 1)
		return false;

	if(!m_grid[_x + 1][_y].is_empty())
		return true;

	if(!m_grid[_x + 1][_y - 1].is_empty())
		return true;

	return false;
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

			px.red = m_grid[x][y].red;
			px.green = m_grid[x][y].green;
			px.blue = m_grid[x][y].blue;
		}
	}

	return img;
}
