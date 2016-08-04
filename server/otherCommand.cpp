
#include <cstring>
#include <iostream>
#include <map>
#include <vector>

#include <dirent.h>

#include "otherCommand.h"

OtherCommand::OtherCommand(FILE *in, FILE *out) : Command::Command(in, out){};

int OtherCommand::execute()
{
	this->sendHeader();
	return 0;
}

void OtherCommand::sendHeader()
{
	fprintf(this->out, "Status: 400");
	fprintf(this->out, "\n");
}
