
#ifndef OTHERCOMMAND_H
#define OTHERCOMMAND_H


#include "command.h"

class OtherCommand : public Command
{

public:
	OtherCommand(FILE *in, FILE *out);
	int execute();

	
private:
	void sendHeader();
};


#endif

