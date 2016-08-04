
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utils.h"
#include "getCommand.h"

/*

  Req:
  
  
  GET 
  name: name
  size: size
  start: 
  end: 
  
  Body
  
*/


GetCommand::GetCommand(FILE *in, FILE *out) : Command::Command(in, out){};

int GetCommand::execute()
{
	std::ifstream ifs;
		
	Command::getHeader();

#ifdef DEBUG
	std::cout << this->header["filename"] << std::endl;
#endif
	
	this->openFile(ifs);
	this->sendHeader();
	
	if (this->header["size"].compare("-1")) {
		std::cerr << "Send : " << this->header["filename"] << std::endl;
		this->sendData();
	}
	return 0;
}


void GetCommand::openFile(std::ifstream &ifs)
{
	ifs.open(this->header["filename"], std::ifstream::binary);
	if (ifs.fail() == true) {
		std::cerr << "Failed to open : " << this->header["filename"] << std::endl;
		this->header["size"] = "-1";		
	} else {
		this->header["size"] = std::to_string(this->getFileSize(ifs));
	}	

}

int GetCommand::getFileSize(std::ifstream &ifs)
{

       	//http://washieagle.blogspot.jp/2010/01/stdfstream.html
	int eofPos;
	int begPos;
	
	//末尾
	ifs.seekg(0, std::ifstream::end);
	eofPos = ifs.tellg();
		
	ifs.clear();
	
	//先頭
	ifs.seekg(0, std::ifstream::beg);
	begPos = ifs.tellg();

	return eofPos - begPos;
}

int GetCommand::sendHeader()
{
	if (!this->header["size"].compare("-1") || !this->header["size"].compare("") ) {
		fprintf(this->out, "Status: 404\n\n");

	} else {
		fprintf(this->out, "Status: 200\n");
		fprintf(this->out, "filename: %s\n", this->header["filename"].c_str());
		fprintf(this->out, "size: %s\n", this->header["size"].c_str());
		fprintf(this->out, "\n");
	}

}

int GetCommand::sendData()
{

	//std::fstream fs(this->filename);
	//ファイルの存在の検証を追加すること

	char buf[256];
	uint size;
	int bsize;
	int size_wrote = 0;
	
	std::ifstream ifs;

#ifdef DEBUG
	std::cerr << "open : " <<  this->header["filename"].length() << std::endl;
#endif
	
	ifs.open(this->header["filename"], std::ifstream::binary);

	if (ifs.fail() == true) {
		fprintf(this->out, "Not found.\n");
		return -1;
	}
	
	size = this->getFileSize(ifs);

	
	while (size_wrote < size) {

		bsize = size_wrote + 256 > size ? size-size_wrote : 256;
		
		ifs.read (buf, bsize);

		fwrite(buf, 1, bsize, this->out);
		size_wrote += 256;
	}
	
	fwrite("\n", 1, 1, this->out);
	return 0;
	
	
	
}

