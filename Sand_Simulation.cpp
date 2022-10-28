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

void Sand_Simulation::setup_from_file(const std::string& _path)
{
	std::ifstream file(_path, std::ios::in);

	if(!file.is_open())
		return;

	unsigned int x = 0, y = 0, value = 0;

	while(!file.eof())
	{
		file >> x >> y >> value;
		set_grains_in_column(x, y, value);
	}

	file.close();
}



void Sand_Simulation::update()
{
	m_stable = true;

	unsigned int ng_width = m_width;
	unsigned int ng_height = m_height;

	unsigned int** ng_grid = new unsigned int * [m_width];
	for(unsigned int i = 0; i < m_width; ++i)
	{
		ng_grid[i] = new unsigned int[m_height];
		for(unsigned int j=0; j< m_height; ++j)
			ng_grid[i][j] = m_grid[i][j];
	}

	bool left_offset = false, right_offset = false, bottom_offset = false, top_offset = false;

	for(int y = 0; y < (int)m_height; ++y)
	{
		if(!left_offset)
		{
			if(grain_can_slide_here(-1, y, m_grid[0][y]))
			{
				expand_grid(ng_grid, ng_width, ng_height, -1, 0);
				left_offset = true;
			}
		}
		if(!right_offset)
		{
			if(grain_can_slide_here(m_width, y, m_grid[m_width - 1][y]))
			{
				expand_grid(ng_grid, ng_width, ng_height, 1, 0);
				right_offset = true;
			}
		}
	}
	for(int x = 0; x < (int)m_width; ++x)
	{
		if(!bottom_offset)
		{
			if(grain_can_slide_here(x, -1, m_grid[x][0]))
			{
				expand_grid(ng_grid, ng_width, ng_height, 0, -1);
				bottom_offset = true;
			}
		}
		if(!top_offset)
		{
			if(grain_can_slide_here(x, m_height, m_grid[x][m_height - 1]))
			{
				expand_grid(ng_grid, ng_width, ng_height, 0, 1);
				top_offset = true;
			}
		}
	}

	for(unsigned int i = 0; i < m_width; ++i)
		delete[] m_grid[i];
	delete[] m_grid;

	m_grid = ng_grid;

	m_height = ng_height;
	m_width = ng_width;

	ng_grid = new unsigned int * [m_width];
	for(unsigned int i = 0; i < m_width; ++i)
	{
		ng_grid[i] = new unsigned int[m_height];
		for(unsigned int j=0; j< m_height; ++j)
			ng_grid[i][j] = 0;
	}

	for(int y = 0; y < (int)m_height; ++y)
	{
		for(int x = 0; x < (int)m_width; ++x)
		{
			unsigned int current_count = m_grid[x][y];

			if(grain_can_slide_here(x - 1, y, current_count))
			{
				++ng_grid[x - 1][y];
				--current_count;

				m_stable = false;
			}
			if(grain_can_slide_here(x + 1, y, current_count))
			{
				++ng_grid[x + 1][y];
				--current_count;
				m_stable = false;
			}
			if(grain_can_slide_here(x, y - 1, current_count))
			{
				++ng_grid[x][y - 1];
				--current_count;
				m_stable = false;
			}
			if(grain_can_slide_here(x, y + 1, current_count))
			{
				++ng_grid[x][y + 1];
				--current_count;
				m_stable = false;
			}

			ng_grid[x][y] += current_count;
		}
	}

	for(unsigned int i = 0; i < m_width; ++i)
		delete[] m_grid[i];
	delete[] m_grid;

	m_grid = ng_grid;

	m_height = ng_height;
	m_width = ng_width;
}



bool Sand_Simulation::grain_can_slide_here(int _where_x, int _where_y, unsigned int _relative_to)
{
	if(_relative_to < 4)
		return false;

	if(_where_x < 0 || _where_y < 0 || _where_x >= (int)m_width || _where_y >= (int)m_height)
		return true;

	if(m_grid[_where_x][_where_y] <= _relative_to - 4)
		return true;

	return false;
}

void Sand_Simulation::expand_grid(unsigned int**& _grid, unsigned int& _width, unsigned int& _height, int _where_x, int _where_y) const
{
	unsigned int new_width = _width + abs(_where_x);
	unsigned int new_height = _height + abs(_where_y);

	unsigned int** new_grid = new unsigned int * [new_width];
	for(unsigned int i=0; i<new_width; ++i)
	{
		new_grid[i] = new unsigned int[new_height];
		for(unsigned int j = 0; j < new_height; ++j)
			new_grid[i][j] = 0;
	}

	unsigned int x_inc = 0;
	if(_where_x < 0)
		x_inc = abs(_where_x);
	unsigned int y_inc = 0;
	if(_where_y < 0)
		y_inc = abs(_where_y);

	for(unsigned int x = x_inc; x < _width + x_inc; ++x)
		for(unsigned int y = y_inc; y < _height + y_inc; ++y)
			new_grid[x][y] = _grid[x - x_inc][y - y_inc];

	for(unsigned int i = 0; i < _width; ++i)
		delete[] _grid[i];
	delete[] _grid;

	_grid = new_grid;
	_width = new_width;
	_height = new_height;
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
