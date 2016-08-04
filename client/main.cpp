#include <iostream>
#include "myftp.h"

int main(int argc, char **argv)
{
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " host port" << std::endl;
		return -1;
	}

	MyFTP client;

	//argv[1] -> hot1s2	
	//argv[2] -> port
	return client.run(argv[1], argv[2]);
	
}
		
