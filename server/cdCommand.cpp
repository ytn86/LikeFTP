
#include <cstring>
#include <iostream>
#include <map>
#include <vector>

#include <unistd.h>

#include "cdCommand.h"

CdCommand::CdCommand(FILE *in, FILE *out) : Command::Command(in, out){};

int CdCommand::execute()
{
	int res;
	
	Command::getHeader();
	res = chdir(this->header["path"].c_str());
	this->sendHeader(res);

	return 0;
}


void CdCommand::sendHeader(int flag)
{
	if (flag < 0) {
		fprintf(this->out, "Status: 404\n");
		std::cout << "hoge" << std::endl;
	}else {
		fprintf(this->out, "Status: 200\n");
	}
	fprintf(this->out, "\n");
}
			
