#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include <string>
#include <map>


class Args_Parser
{
private:
	enum class Mode
	{
		none,
		arg,
		value
	};

public:
	Args_Parser();
	~Args_Parser();

public:
	std::map<std::string, std::string> parse(const std::string& _raw_data) const;

};


#endif // ARGS_PARSER_H
