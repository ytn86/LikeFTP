

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

//#include "utils.h"
#include "dirCommand.h"

/*

  Req:
  
  
  DIR

  
  
*/


DirCommand::DirCommand(FILE *in, FILE *out) : Command::Command(in, out){};


int DirCommand::execute()
{
	
	this->sendRequest();
	Command::getHeader();

	this->recvData();
	
	
		

	return 0;
}


void DirCommand::sendRequest()
{
	fprintf(this->out, "DIR\n");
	fprintf(this->out, "\n");
}

int DirCommand::recvData()
{

	//std::fstream fs(this->filename);
	//ファイルの存在の検証を追加すること
	int size = 512;
	
	char buf[size];

	for (int i = 0; i < stoi(this->header["num"]); i++) {
		fgets(buf, size, this->in);
		fprintf(stdout, "%s", buf);
	}
	
	// end of req : \n
	fread(buf, 1, 1, this->in);
		
	return 0;
	
}

       
