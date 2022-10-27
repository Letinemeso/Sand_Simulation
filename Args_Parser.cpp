#include "Args_Parser.h"


Args_Parser::Args_Parser()
{

}

Args_Parser::~Args_Parser()
{

}



std::map<std::string, std::string> Args_Parser::parse(const std::string& _raw_data) const
{
	std::map<std::string, std::string> result;

	std::string current_arg, current_value;

	Mode mode = Mode::none;

	for(unsigned int i=0; i<_raw_data.size(); ++i)
	{
		char c = _raw_data[i];

		if(c == ' ')
		{
			if(mode == Mode::value && current_arg.size() > 0 && current_value.size() > 0)
			{
				result.emplace(current_arg, current_value);

				current_arg.clear();
				current_value.clear();
			}

			mode = Mode::none;
			continue;
		}

		if(c == '-' && current_arg.size() == 0)
		{
			current_arg.clear();
			current_value.clear();

			mode = Mode::arg;
			current_arg += c;
			continue;
		}

		if(mode == Mode::arg)
		{
			current_arg += c;
			continue;
		}

		if(mode == Mode::value)
		{
			current_value += c;
			continue;
		}

		if(mode == Mode::none && c != ' ')
		{
			mode = Mode::value;
			current_value += c;
			continue;
		}
	}

	if(mode == Mode::value && current_arg.size() > 0 && current_value.size() > 0)
	{
		result.emplace(current_arg, current_value);

		current_arg.clear();
		current_value.clear();
	}

	return result;
}
