
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utils.h"
#include "putCommand.h"

/*

  Req:
  
  
  PUT
  filename: name
  size: size

  Body
  
*/


PutCommand::PutCommand(FILE *in, FILE *out) : Command::Command(in, out){};

int PutCommand::execute()
{
	Command::getHeader();
	this->recvData();
	return 0;
}
	
int PutCommand::recvData()
{

	//std::fstream fs(this->filename);
	//ファイルの存在の検証を追加すること

	char buf[256];
	uint size;
	int bsize;
	int size_recv = 0;
	
	std::ofstream ofs;



	size = stoi(this->header["size"]);
	
	ofs.open(this->header["filename"], std::ofstream::binary | std::ofstream::out | std::ofstream::trunc);

	if (ofs.fail() == true)
		return -1;

	
	while (size_recv < size) {

		bsize = size_recv + 256 > size ? size-size_recv : 256;
		fread(buf, 1, bsize, this->in);
		
		ofs.write(buf, bsize);
			
		size_recv += 256;

	}

	ofs.close();

	//end of req : \n
	fread(buf, 1, 1, this->in);
	
	return 0;
	
}
       
