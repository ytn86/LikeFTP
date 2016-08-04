
#ifndef PUTCOMMAND_H
#define PUTCOMMAND_H

#include "command.h"

class PutCommand : public Command {
public:
	
	PutCommand(FILE *in, FILE *out, std::vector<std::string>& files);
	int execute();
		
	
protected:
	int getFileSize(std::ifstream &ifs);
	
	void openFile(std::string& filename, std::ifstream& ifs);
	int sendHeader();
	int sendData(std::ifstream& ifs);
	
	
};

#endif
