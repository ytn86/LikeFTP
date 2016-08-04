#ifndef INCLUDE_GURAD_PUTCOMMAND_H
#define INCLUDE_GUARD_PUTCOMMAND_H

#include "command.h"

class PutCommand : public Command {
public:
	
	PutCommand(FILE *in, FILE *out);
	int execute();
	
	
	
private:
	int recvData();
	
};

#endif
