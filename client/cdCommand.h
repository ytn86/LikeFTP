#ifndef CDCOMMAND_H
#define CDCOMMAND_H

#include "command.h"

class CdCommand : public Command {
public:
	
	CdCommand(FILE *in, FILE *out, std::vector<std::string>& files);
	int execute();
	
	
	
private:
	void sendRequest(const std::string& dir);
	
	
};

#endif
