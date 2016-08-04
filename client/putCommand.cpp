
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


PutCommand::PutCommand(FILE *in, FILE *out, std::vector<std::string>& files) : Command::Command(in, out, files){};

int PutCommand::execute()
{
	std::ifstream ifs;
		
	for (auto i : this->files)  {
		this->header["filename"] = i;
		this->openFile(i, ifs);
		if (!this->header["size"].compare("-1") || !this->header["size"].compare("")) {
			std::cerr << "Failed to open : " << this->header["filename"] << std::endl;
			continue;
		}
		this->sendHeader();
		this->sendData(ifs);
		ifs.close();
	}


	
	return 0;
}


void PutCommand::openFile(std::string& filename, std::ifstream &ifs)
{
	ifs.open(filename, std::ifstream::binary);
	if (ifs.fail() == true) {

		this->header["size"] = "-1";		
	} else {
		this->header["size"] = std::to_string(this->getFileSize(ifs));
	}	

}

int PutCommand::getFileSize(std::ifstream &ifs)
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

int PutCommand::sendHeader()
{
	fprintf(this->out, "PUT\n"); 
	fprintf(this->out, "filename: %s\n", this->header["filename"].c_str());
	fprintf(this->out, "size: %s\n", this->header["size"].c_str());
	fprintf(this->out, "\n");

	return 0;
}

int PutCommand::sendData(std::ifstream& ifs)
{
	
	//std::fstream fs(this->filename);
	//ファイルの存在の検証を追加すること

	char buf[256];
	int size;
	int bsize;
	int size_wrote = 0;

	
	size = stoi(this->header["size"]);
	while (size_wrote < size) {

		bsize = size_wrote + 256 > size ? size-size_wrote : 256;
		
		ifs.read (buf, bsize);

		fwrite(buf, 1, bsize, this->out);
		size_wrote += 256;
	}
	
	fwrite("\n", 1, 1, this->out);
	       
	return 0;
	
	
	
}

