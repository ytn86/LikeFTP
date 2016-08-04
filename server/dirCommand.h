
#ifndef DIRCOMMAND_H
#define DIRCOMMAND_H


#include "command.h"

class DirCommand : public Command
{

public:
	DirCommand(FILE *in, FILE *out);
	int execute();

	
private:
	std::vector<std::string> fileList;

	int getDir(std::vector<std::string> &fileList);	
	int sendDir();
	void sendHeader();
};


#endif

