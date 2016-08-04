#ifndef COMMAND_H
#define COMMAND_H

class Command
{
public:
	Command(FILE *in, FILE *out);
	virtual int execute();

protected:
	FILE *in;
	FILE *out;
	std::vector<std::string> bufList;
	std::map<std::string, std::string> header;
	
	std::map<std::string, std::string> parseHeader(std::vector<std::string> &bufList);
	int getHeader();
	
	
};

#endif
