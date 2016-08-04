#include <iostream>
#include "myftpd.h"


int main(int argc, char **argv)
{
	
	if (argc != 2) {
		std::cerr << "Usage : " << argv[0] << " port_num\n"  << std::endl;;
		return -1;
	}
	MyFTPd server;

	return server.run(argv[1]);
		
}
