#include <iostream>
#include <vector>
#include <map>


#include "otherCommand.h"

OtherCommand::OtherCommand() : Command::Command(){};

int OtherCommand::execute()
{
	std::cerr << "Not implemented" << std::endl;
	return 0;
}
