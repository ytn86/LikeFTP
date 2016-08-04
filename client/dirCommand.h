#ifndef DIRCOMMAND_H
#define DIRCOMMAND_H

#include "command.h"

class DirCommand : public Command {
public:
	
	DirCommand(FILE *in, FILE *out);
	int execute();
	
	
	
private:
	//std::vector<std::string> files;
	
	//int recvData(const std::string& name, const int size);
	int recvData();
	void sendRequest();
};

#endif
