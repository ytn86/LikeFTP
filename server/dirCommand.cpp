
#include <cstring>
#include <iostream>
#include <map>
#include <vector>

#include <dirent.h>

#include "dirCommand.h"

DirCommand::DirCommand(FILE *in, FILE *out) : Command::Command(in, out){};

int DirCommand::execute()
{
	Command::getHeader();
	this->getDir(this->fileList);
	this->sendHeader();
	this->sendDir();

	return 0;
}




int DirCommand::getDir(std::vector<std::string> &fileList)
{
	DIR *d;
	struct dirent *dir;

	d = opendir("./");

	if (d)
	{
		while ((dir = readdir(d)) != NULL)
			fileList.push_back(dir->d_name);
	}

	closedir(d);

	return 0;
}

void DirCommand::sendHeader()
{
	fprintf(this->out, "Status: 200\n");
	fprintf(this->out, "num: %d\n", this->fileList.size());
	fprintf(this->out, "\n");

#ifdef DEBUF
	fprintf(stdout, "Status: 200\n");
	fprintf(stdout, "num: %d\n", this->fileList.size());
	fprintf(stdout, "\n");
#endif
	
}
	

int DirCommand::sendDir()
{
	for (auto i : this->fileList) {
		
		fwrite(i.c_str(), 1, i.size(), this->out);
		fwrite("\n", 1, 1, this->out);
	}
	fwrite("\n", 1, 1, this->out);

	return 0;
}

