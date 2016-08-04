
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

//#include "utils.h"
#include "getCommand.h"

/*

  Req:
  
  
  PUT
  filename: name
  size: size

  Body
  
*/


GetCommand::GetCommand(FILE *in, FILE *out, std::vector<std::string>& files) : Command::Command(in, out, files){};


int GetCommand::execute()
{

	for (auto i : this->files) {
		GetCommand::sendRequest(i.c_str());
		Command::getHeader();
				

		if (this->header["Status"].compare("404")) {
			this->recvData(i);
		} else {
			std::cerr << "Not Found : " << i << std::endl;
		}
	}
		

	return 0;
}


void GetCommand::sendRequest(const char *filename)
{
	fprintf(this->out, "GET\n");
	fprintf(this->out, "filename: %s\n", filename);
	fprintf(this->out, "\n");
}

int GetCommand::recvData(const std::string& filename)
{

	//std::fstream fs(this->filename);
	//ファイルの存在の検証を追加すること

	char buf[256];
	int bsize;
	int size_recv = 0;
	int size = stoi(this->header["size"]);
	
	std::ofstream ofs;

	

	ofs.open(filename, std::ofstream::binary | std::ofstream::in | std::ofstream::trunc);
	
	if (ofs.fail() == true) {
		std::cerr << "fail" << std::endl;
		return -1;
	}
	
	while (size_recv < size) {

		bsize = size_recv + 256 > size ? size-size_recv : 256;
		fread(buf, 1, bsize, this->in);
		buf[bsize] = '\0';
		
		ofs.write(buf, bsize);
		size_recv += 256;
	}

	ofs.close();

	//end of req : \n
	fread(buf, 1, 1, this->in);
	
	
	return 0;
	
}
       
