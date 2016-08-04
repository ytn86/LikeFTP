#include <iostream>
#include <map>
#include <cstring>
#include <vector>

#include "command.h"
#include "utils.h"


Command::Command(FILE *in, FILE *out) {

	this->in = in;
	this->out = out;
}

int Command::execute(){};



int Command::getHeader()
{
	// Max Number of headers

	
	char buf[512];
	std::vector<std::string> bufList;
	
	for (int i = 0; i < 32; i++)
	{

		fgets(buf, 512, this->in);

		if (!strcmp(buf, "\n")) {
			//end of header
			break;
		}
		bufList.push_back(char2str(buf));
	}

	
	
	this->header = this->parseHeader(bufList);
	
	return 0;
	
}
	
std::map<std::string, std::string> Command::parseHeader(std::vector<std::string> &bufList)
{
	std::string line, key, value;
	int pos;
	
	std::map<std::string, std::string> header;


	for (auto line : bufList) {
		
		//line = header.back();
		pos = line.find(": ");

		if (pos == -1)
			continue;

		key  = line.substr(0, pos);
		value = line.substr(pos+2);
		
		//末端の改行を除去
		value.resize(value.length()-1);

		header.insert(std::pair<std::string, std::string>(key, value));
				
		//header[key] = value;
	}

	#ifdef DEBUG
	for (std::map<std::string, std::string>::iterator it=header.begin(); it != header.end(); it++) {
		std::cout << it->first << "=>" << it->second << std::endl;
	}
	#endif
	
	return header;
}



       
