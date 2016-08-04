
#ifndef CDCOMMAND_H
#define CDCOMMAND_H


#include "command.h"

class CdCommand : public Command
{

public:
	CdCommand(FILE *in, FILE *out);
	int execute();

	
private:
	void sendHeader(int flag);
};


#endif

