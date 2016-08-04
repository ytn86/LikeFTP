
#ifndef GET_COMMAND_H
#define GET_COMMAND_H

#include "command.h"

class GetCommand : public Command {
public:
	
	GetCommand(FILE *in, FILE *out);
	int execute();
	
	
	
protected:
	int getFileSize(std::ifstream &ifs);
	
	void openFile(std::ifstream& ifs);
	int sendHeader();
	int sendData();
	
	
};

#endif
