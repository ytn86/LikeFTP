#ifndef GETCOMMAND_H
#define GETCOMMAND_H

#include "command.h"

class GetCommand : public Command {
public:
	
	GetCommand(FILE *in, FILE *out, std::vector<std::string>& files);
	int execute();
	
	
	
private:
	//std::vector<std::string> files;
	
	//int recvData(const std::string& name, const int size);
	int recvData(const std::string& name);
	void sendRequest(const char *filename);
	
	
};

#endif
