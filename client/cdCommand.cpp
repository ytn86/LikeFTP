
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

//#include "utils.h"
#include "cdCommand.h"

/*

  Req:
  
  CD
  path: <path>
  

*/


CdCommand::CdCommand(FILE *in, FILE *out, std::vector<std::string>& files) : Command::Command(in, out, files){};


int CdCommand::execute()
{
	std::string dir = this->files.at(0);
	
	CdCommand::sendRequest(dir);
	Command::getHeader();
	
	if (this->header["Status"].compare("404")) {
		std::cerr << "ok." << std::endl;
	} else {
		std::cerr << "failed." << std::endl;
	}
		

	return 0;
}


void CdCommand::sendRequest(const std::string& dir)
{
	fprintf(this->out, "CD\n");
	fprintf(this->out, "path: %s\n", dir.c_str()); 
	fprintf(this->out, "\n");
}
